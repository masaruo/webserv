#include "CgiRequest.hpp"
#include "HttpException.hpp"
#include "FileHandler.hpp"
#include "UriNormalizer.hpp"
#include <unistd.h>// execve & chdir
#include <cstdlib>// std::exit
#include <cstring>// std::strcpy
#include <cerrno>
#include <sys/wait.h>// waitpid
#include <sys/socket.h>// socket pair
#include "define.hpp"
#include "Fcntl.class.hpp"
#include "sys/epoll.h"
#include "Server.hpp"

int const	CgiRequest::READ_FD = 0;
int const	CgiRequest::WRITE_FD = 1;
int const	CgiRequest::CHILD_PID = 0;
int const	CgiRequest::INTERNAL_SERVER_ERROR = 50;

CgiRequest::CgiRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config, Server &server)
:ARequest(line, header, config, server)
,cgi_socket_(NULL)
,child_pid_(-1)
,is_response_ready_(false)
{
	generateResponseData();
	return ;
}

CgiRequest::CgiRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config, Server &server)
:ARequest(line, header, body, config, server)
,cgi_socket_(NULL)
,child_pid_(-1)
,is_response_ready_(false)
{
	generateResponseData();
	return ;
}

CgiRequest::~CgiRequest()
{
	return ;
}

CgiRequest::CgiRequest(CgiRequest const &rhs)
:ARequest(rhs)
,cgi_socket_(rhs.cgi_socket_)
,child_pid_(rhs.child_pid_)
,is_response_ready_(rhs.is_response_ready_)
{
	return ;
}

CgiRequest &CgiRequest::operator=(CgiRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator=(rhs);
		cgi_socket_ = rhs.cgi_socket_;
		child_pid_ = rhs.child_pid_;
		is_response_ready_ = rhs.is_response_ready_;
	}
	return (*this);
}

static int	assertClose(int fd)
{
	int	res = close(fd);
	if (res == ft::err)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	else
		return (res);
}

static int	dup2ThenClose(int fd1, int fd2)
{
	int const	newfd = dup2(fd1, fd2);

	if (newfd == ft::err)
		return (ft::err);
	if (close(fd1) == ft::err)
		return (ft::err);
	else
		return (newfd);
}

static char	**generateArgv(std::string const &uri)
{
	char	**argv = NULL;
	std::string	cgiPath;

	argv = new char*[2]();
	argv[1] = NULL;

	argv[0] = new char[uri.size() + 1]();
	std::strcpy(argv[0], uri.c_str());
	return (argv);
}

void	CgiRequest::exec_child(int sockfd[2], std::string const &abspath) const
{
	if (close(sockfd[ft::PARENTFD]) == -1)
		std::exit(INTERNAL_SERVER_ERROR);
	if (dup2(sockfd[ft::CHILDFD], STDIN_FILENO) == -1)
		std::exit(INTERNAL_SERVER_ERROR);
	if (dup2(sockfd[ft::CHILDFD], STDOUT_FILENO) == -1)
		std::exit(INTERNAL_SERVER_ERROR);
	if (close(sockfd[ft::CHILDFD]) == -1)
		std::exit(INTERNAL_SERVER_ERROR);


	std::string const 						&path = getLine().getUri().getPath();
	config::Config::LocationConfig	const	&loc = getConfig().getConfigLocation(path);
	std::string	chdir_target = loc.directive_.getFirstValue(config::Config::CGI_ROOT);
	if (chdir(chdir_target.c_str()) == -1)
	{
		std::exit(INTERNAL_SERVER_ERROR);
	}

	//generate ENV with chdir dir
	// Env env(getLine(), getHeader(), getBody(), abspath);

	std::string const &file = getLine().getUri().getPathInfo().fileName_;

	char	**argv = NULL;
	try
	{
		argv = generateArgv(file);
	}
	catch(std::bad_alloc const &e)
	{
		std::exit(INTERNAL_SERVER_ERROR);
	}

	// execve(argv[0], argv, env.c_env());
	std::exit(INTERNAL_SERVER_ERROR);
}

void	CgiRequest::exec_parent(int sockfds[2])
{
	if (close(sockfds[ft::CHILDFD]) == -1)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

	// Server		&server = getServerReference();
	// cgi_socket_->setData(getBody().to_string());
	// ft::Fcntl::setNonBlock(sockfds[ft::PARENTFD]);
	// server.addSocket(cgi_socket_);

	// shutdown(sockfds[ft::PARENTFD], SHUT_WR);

}

void	CgiRequest::execute(std::string const &abspath)
{
	int			sockfds[2];
	pid_t		child_pid = 0;
	std::string	bodyStr = "";

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockfds) == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}

	sockaddr_in	dummy_sockaddr = {};
	std::memset(&dummy_sockaddr, 0, sizeof(sockaddr));
	ASocket::Addr dummy;
	dummy.addrin_ = dummy_sockaddr;
	dummy.addrlen_ = sizeof(dummy);
	cgi_socket_ = new ActiveSocket(0, sockfds[ft::PARENTFD], ft::CGISEND, EPOLLOUT, getServerReference(), dummy);
	if (cgi_socket_ == NULL)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

	child_pid = fork();
	if (child_pid == ft::err)
	{
		close(sockfds[ft::PARENTFD]);
		close(sockfds[ft::CHILDFD]);
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	else if (child_pid == CHILD_PID)
	{
		exec_child(sockfds, abspath);
	}
	else
	{
		child_pid_ = child_pid;
		exec_parent(sockfds);
	}
}

std::string	CgiRequest::setLocalPath(void) const
{
	std::string			finalPath;
	HttpUri const		&uri = getLine().getUri();
	std::string const	&path = UriNormalizer::decodeDots(uri.getPath());
	std::string const	&root = getConfig().getRoot(path);
	std::string const	&file = UriNormalizer::decodeDots(uri.getPathInfo().fileName_);
	std::string const	&pathWithRoot = root + "/" + file;

	if (!FileHandler::checkPathExist(root))
		throw (HttpException(HttpCode::NOT_FOUND));
	if (!FileHandler::checkIfFile(pathWithRoot))
		throw (HttpException(HttpCode::CONFLICT));
	if (access(pathWithRoot.c_str(), X_OK) == ft::err)
		throw (HttpException(HttpCode::FORBIDDEN));
	return (pathWithRoot);
}

void	CgiRequest::engageWithChild(void)
{
	std::string const	abspath = setLocalPath();
	execute(abspath);
}

void	CgiRequest::wait(void)
{
	int	status;
	pid_t res = waitpid(child_pid_, &status, WNOHANG);
	if (res == child_pid_)
	{
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		{
			throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
		}
		child_pid_ = -1;
	}
}

void	CgiRequest::generateResponseData(void)
{
	if (!is_response_ready_)
	{
		engageWithChild();
		return ;
	}
	std::string const	resBody = cgi_socket_->getData();
	HttpBody	body(resBody);

	HttpStatus	status(HttpCode::OK);

	HttpHeader	header;
	header.addValue(HttpHeader::CONTENT_TYPE, "text/html");
	header.addValue(HttpHeader::CONTENT_LENGTH, body.getSizeStr());

	setResponseStatus(status);
	setResponseHeader(header);
	setResponseBody(body);
	setResponseHasBody(true);
	return ;
}
