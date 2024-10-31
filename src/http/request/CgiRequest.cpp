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
#include "CgiSocket.hpp"
#include "SocketHolder.class.hpp"

int const	CgiRequest::READ_FD = 0;
int const	CgiRequest::WRITE_FD = 1;
int const	CgiRequest::CHILD_PID = 0;
int const	CgiRequest::INTERNAL_SERVER_ERROR = 50;

CgiRequest::CgiRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:ARequest(line, header, config)
{
	generateResponseData();
	return ;
}

CgiRequest::CgiRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config)
:ARequest(line, header, body, config)
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
{
	return ;
}

CgiRequest &CgiRequest::operator=(CgiRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator=(rhs);
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
	Env env(getLine(), getHeader(), getBody(), abspath);

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

	execve(argv[0], argv, env.c_env());
	std::exit(INTERNAL_SERVER_ERROR);
}

std::string	CgiRequest::exec_parent(int sockfds[2], int child_pid) const
{
	if (close(sockfds[ft::CHILDFD]) == -1)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

	CgiSocket *cgisock = new CgiSocket(sockfds[ft::PARENTFD]);
	cgisock->request_body_ = getBody().to_string();
	cgisock->setSocketType(ASocket::CGISEND);

std::cerr << "Creating CGI socket FD:" << sockfds[ft::PARENTFD] 
              << " body:" << cgisock->request_body_.size() 
              << " bytes" << std::endl;


	SocketHolder::addSocket(cgisock);

	while (cgisock->getSocketType() == ASocket::CGISEND)
		usleep(1000);

	while (cgisock->getSocketType() != ASocket::IDLE)
	{
		int	status = 0;
		pid_t pid = waitpid(child_pid, &status, WNOHANG);
		if (pid == -1)
			throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
		if (pid > 0 && WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);
			if (exit_status != 0)
				throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
			break ;
		}
	}
	std::string	result = cgisock->response_body_;
	SocketHolder::markSocketDelete(cgisock);
	// delete cgisock;
	return (result);
}

std::string	CgiRequest::execute(std::string const &abspath) const
{
	// int			pipe_in[2];
	// int			pipe_out[2];
	int			sockfds[2];
	pid_t		child_pid = 0;
	std::string	bodyStr = "";

	// if (pipe(pipe_in) == ft::err || pipe(pipe_out) == ft::err)
	// {
	// 	throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	// }

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockfds) == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	// ft::Fcntl::setNonBlock(sockfds, 2);//? do i have to make nonblock on child sock fd?
	ft::Fcntl::setNonBlock(sockfds[ft::PARENTFD]);
	// ft::Fcntl::setNonBlock(sockfds[1]);
	child_pid = fork();
	if (child_pid == ft::err)
	{
		// close(pipe_in[WRITE_FD]);
		// close(pipe_in[READ_FD]);
		// close(pipe_out[WRITE_FD]);
		// close(pipe_out[READ_FD]);
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
		bodyStr = exec_parent(sockfds, child_pid);
	}
	return (bodyStr);
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

void	CgiRequest::generateResponseData(void)
{
	std::string const	abspath = setLocalPath();
	std::string const	resBody = execute(abspath);

	if (resBody.empty())
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

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
