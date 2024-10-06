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

void	CgiRequest::exec_child(int pipe_in[2], int pipe_out[2]) const
{
	if (close(pipe_in[WRITE_FD]) == ft::err)
		std::exit(INTERNAL_SERVER_ERROR);
	if (close(pipe_out[READ_FD]) == ft::err)
		std::exit(INTERNAL_SERVER_ERROR);

	if (dup2ThenClose(pipe_in[READ_FD], STDIN_FILENO) == ft::err)
	{
		std::exit(INTERNAL_SERVER_ERROR);
	}
	if (dup2ThenClose(pipe_out[WRITE_FD], STDOUT_FILENO) == ft::err)
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

std::string	CgiRequest::exec_parent(int pipe_in[2], int pipe_out[2], int child_pid) const
{
	if (close(pipe_in[READ_FD]))
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	if (close(pipe_out[WRITE_FD]))
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

	std::string const	&body = getBody().to_string();
	ssize_t		total_written = 0;
	std::size_t	remaining = getBody().getSize();

	while (remaining > 0)
	{
		ssize_t	bytesWritten = write(pipe_in[WRITE_FD], body.c_str() + total_written, remaining);
		if (bytesWritten == ft::err)
		{
			// if (errno == EINTR)
				// continue ;
			// else
			// {
				close(pipe_in[WRITE_FD]);
				close(pipe_out[READ_FD]);
				throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
			// }
		}
		total_written += bytesWritten;
		remaining -= bytesWritten;
	}
	assertClose(pipe_in[WRITE_FD]);

	std::string	result = "";
	try
	{
		result = FileReader::readFdFile(pipe_out[READ_FD]);
	}
	catch(...)
	{
		assertClose(pipe_out[READ_FD]);
		throw;
	}
	
	assertClose(pipe_out[READ_FD]);

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
	int			pipe_in[2];
	int			pipe_out[2];
	pid_t		child_pid = 0;
	std::string	bodyStr = "";

	if (pipe(pipe_in) == ft::err || pipe(pipe_out) == ft::err)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	child_pid = fork();
	if (child_pid == ft::err)
	{
		close(pipe_in[WRITE_FD]);
		close(pipe_in[READ_FD]);
		close(pipe_out[WRITE_FD]);
		close(pipe_out[READ_FD]);
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	else if (child_pid == CHILD_PID)
	{
		exec_child(pipe_in, pipe_out);
	}
	else
	{
		usleep(50000);//todo need to change, without this, pipe clogging happens (ie. .py failed to read).
		bodyStr = exec_parent(pipe_in, pipe_out, child_pid);
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
	header.setElem("content-type", "text/html");
	header.setElem("content-length", body.getSizeStr());

	Response	r(status, header, body);
	return (r);
}
