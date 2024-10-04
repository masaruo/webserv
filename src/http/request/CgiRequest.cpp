#include "CgiRequest.hpp"
#include "Response.hpp"
#include "HttpException.hpp"
#include "FileHandler.hpp"
#include <unistd.h>// execve
#include <cstdlib>// std::exit
#include <cstring>// std::strcpy
#include <cerrno>
#include <sys/wait.h>// waitpid

int const	CgiRequest::READ_FD = 0;
int const	CgiRequest::WRITE_FD = 1;
int const	CgiRequest::CHILD_PID = 0;

CgiRequest::CgiRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:ARequest(line, header, config)
,env_(getLine(), getHeader(), getLocalPath())
{
	return ;
}

CgiRequest::CgiRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config)
:ARequest(line, header, body, config)
,env_(getLine(), getHeader(), getBody(), getLocalPath())
{
	return ;
}

CgiRequest::~CgiRequest()
{
	return ;
}

CgiRequest::CgiRequest(CgiRequest const &rhs)
:ARequest(rhs)
,env_(rhs.env_)
{
	return ;
}

CgiRequest &CgiRequest::operator=(CgiRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator=(rhs);
		env_ = rhs.env_;
	}
	return (*this);
}

static int	closeWithException(int fd1)
{
	int	res = close(fd1);
	if (res == ft::err)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	else
		return (res);
}

static int	dup2nClose(int fd1, int fd2)
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

	argv = new char*[2]();
	argv[1] = NULL;

	argv[0] = new char[uri.size() + 1]();
	// std::strcpy(argv[0], uri.c_str());
	std::strcpy(argv[0], "/webserv/cgi-bin/echo.py");//! mock

	return (argv);
}

void	CgiRequest::exec_child(int pipefd[2]) const
{
	if (dup2nClose(pipefd[READ_FD], STDIN_FILENO) == ft::err)
	{
		std::exit(50);
	}
	if (dup2nClose(pipefd[WRITE_FD], STDOUT_FILENO) == ft::err)
	{
		std::exit(50);
	}

	char	**argv = NULL;
	try
	{
		argv = generateArgv(getLocalPath());
	}
	catch(std::bad_alloc const &e)
	{
		std::exit(50);
	}

	//todo move to exec dir?
	//! relative path

	execve(argv[0], argv, env_.c_env());

	std::exit(51);
}

std::string	CgiRequest::exec_parent(int pipefd[2], int child_pid) const
{
	ssize_t		total_written = 0;
	std::size_t	remaining = getBody().getSize();

	while (remaining > 0)
	{
		ssize_t	bytesWritten = write(pipefd[WRITE_FD], getBody().c_str() + total_written, remaining);
		if (bytesWritten == ft::err)
		{
			if (errno = EINTR)
				continue ;
			else
			{
				close(pipefd[WRITE_FD]);
				close(pipefd[READ_FD]);
				throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
			}
		}
		total_written += bytesWritten;
		remaining -= bytesWritten;
	}
	closeWithException(pipefd[WRITE_FD]);

	std::string	result = "";
	result = FileReader::readFdFile(pipefd[READ_FD]);
	// close (pipefd[READ_FD]);
	closeWithException(pipefd[READ_FD]);

	int			status = 0;
	pid_t		pid = 0;
	int const	NOHANG = 0;
	while (pid == NOHANG)
	{
		pid = waitpid(child_pid, &status, WNOHANG);
	}
	if (WIFEXITED(status))
	{
		int	exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
		{
			// close (pipefd[READ_FD]);
			throw (HttpException(static_cast<HttpCode::code_e>(exit_status)));
		}
		// std::string	result = FileReader::readFdFile(pipefd[READ_FD]);
		// close (pipefd[READ_FD]);
		// return (result);
	}
	// else
	// {
	// 	close (pipefd[READ_FD]);
	// 	throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	// }

	return (result);
}

std::string	CgiRequest::execute(void) const
{
	int			pipefd[2];
	pid_t		child_pid = 0;
	std::string	bodyStr = "";

	if (pipe(pipefd) == ft::err)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	child_pid = fork();
	if (child_pid == ft::err)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	else if (child_pid == CHILD_PID)
	{
		exec_child(pipefd);
	}
	else
	{
		bodyStr = exec_parent(pipefd, child_pid);
	}
	return (bodyStr);
}

Response	CgiRequest::generateResponse(void) const
{
	std::string const	bodyStr = execute();

	if (bodyStr.empty())
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

	HttpBody	body(bodyStr);

	HttpStatus	status(HttpCode::OK);

	HttpHeader	header;
	header.setHeader("content-type", "text/html");
	header.setHeader("content-length", body.getSizeStr());

	Response	r(status, header, body);
	return (r);
}
