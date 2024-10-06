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
int const	CgiRequest::INTERNAL_SERVER_ERROR = 50;

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

void	CgiRequest::exec_child(int pipefd[2]) const
{
	if (dup2ThenClose(pipefd[READ_FD], STDIN_FILENO) == ft::err)
	{
		std::exit(INTERNAL_SERVER_ERROR);
	}
	if (dup2ThenClose(pipefd[WRITE_FD], STDOUT_FILENO) == ft::err)
	{
		std::exit(INTERNAL_SERVER_ERROR);
	}
	char	**argv = NULL;
	try
	{
		argv = generateArgv(getLocalPath());
	}
	catch(std::bad_alloc const &e)
	{
		std::exit(INTERNAL_SERVER_ERROR);
	}

	//todo move to exec dir?
	//! relative path
	execve(argv[0], argv, env_.c_env());
	std::exit(INTERNAL_SERVER_ERROR);
}

std::string	CgiRequest::exec_parent(int pipefd[2], int child_pid) const
{
	std::string const	&body = getBody().to_string();
	ssize_t		total_written = 0;
	std::size_t	remaining = getBody().getSize();

	while (remaining > 0)
	{
		ssize_t	bytesWritten = write(pipefd[WRITE_FD], body.c_str() + total_written, remaining);
		if (bytesWritten == ft::err)
		{
			if (errno == EINTR)
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
	assertClose(pipefd[WRITE_FD]);

	std::string	result = "";
	try
	{
		result = FileReader::readFdFile(pipefd[READ_FD]);
	}
	catch(...)
	{
		assertClose(pipefd[READ_FD]);
		throw;
	}
	
	assertClose(pipefd[READ_FD]);

	int			status = 0;
	pid_t		pid = 0;
	while (pid == 0)
	{
		pid = waitpid(child_pid, &status, WNOHANG);
		// if (pid == 0)
			// usleep(10000);
	}
	if (WIFEXITED(status))
	{
		int	exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
		{
			if (exit_status == INTERNAL_SERVER_ERROR)
				throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
			else
				throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));//todo amend error
		}
	}
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
		close(pipefd[WRITE_FD]);
		close(pipefd[READ_FD]);
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
	std::string const	resBody = execute();

	if (resBody.empty())
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

	HttpBody	body(resBody);

	HttpStatus	status(HttpCode::OK);

	HttpHeader	header;
	header.setHeader("content-type", "text/html");
	header.setHeader("content-length", body.getSizeStr());

	Response	r(status, header, body);
	return (r);
}
