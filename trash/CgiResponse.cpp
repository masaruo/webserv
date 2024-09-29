#include "CgiResponse.hpp"
#include <unistd.h>
#include <string.h>
#include "FileHandler.hpp"
#include <sys/wait.h>
#include <cstring>

int const	CgiResponse::READ_FD = 0;
int const	CgiResponse::WRITE_FD = 1;
int const	CgiResponse::CHILD_PID = 0;

CgiResponse::CgiResponse(ft::unique_ptr<ARequest>request)
:Response(request)
,env_(getRequestLine(), getRequestHeader(), getRequestBody())
{
	return ;
}

CgiResponse::~CgiResponse()
{
	return ;
}

CgiResponse::CgiResponse(CgiResponse const &rhs)//todo
:Response(rhs)
,env_(rhs.env_)
{
	return ;
}

CgiResponse &CgiResponse::operator=(CgiResponse const &rhs)
{
	if (this != &rhs)
	{
		Response::operator=(rhs);
		env_ = rhs.env_;
	}
	return (*this);
}

void	CgiResponse::execute(void)
{
	int		pipefd[2];
	pid_t	pid = 0;

	if (pipe(pipefd) == ft::err)
	{
		//todo error
	}
	pid = fork();
	if (pid == ft::err)
	{
		//todo error
	}
	else if (pid == CHILD_PID)
	{
		exec_child(pipefd);
	}
	else
	{
		exec_parent(pipefd, pid);
	}

}

static void	delete_argv(char **argv)
{
	std::size_t i = 0;

	while (argv[i] != NULL)
	{
		delete[] argv[i];
		argv[i] = NULL;
		i++;
	}
	delete[] argv;
	argv = NULL;
}

static char **create_argv(std::string const &uri)
{
	char** argv = NULL;

	argv = new char*[2]();
	//todo exceptions - bad alloc
	argv[0] = new char[uri.size() + 1]();
	if (argv[0] == NULL)
	{
		delete_argv(argv);
		//todo exception
	}
	//todo exceptions - bad alloc
	std::strcpy(argv[0], uri.c_str());
	if (argv[0] == NULL)
	{
		delete_argv(argv);
		//todo exception
	}
	argv[1]	= NULL;
	return (argv);
}

#include "mockpath.hpp"//todo delete
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cerrno>
void	CgiResponse::exec_child(int pipefd[2]) const
{
	if (dup2(pipefd[READ_FD], STDIN_FILENO) == ft::err)
	{
		std::cerr << "error" << std::endl;
		//todo error
	}
	if (dup2(pipefd[WRITE_FD], STDOUT_FILENO) == ft::err)
	{
		//todo error
	}
	if (close(pipefd[WRITE_FD]) == ft::err)
	{
		//todo error
	}
	if (close(pipefd[READ_FD]) == ft::err)
	{
		//todo error
	}
	MockPath mock;
	char **argv = create_argv(mock.getPath(getUri()));
	char **env = env_.to_cenv();
	execve(argv[0], argv, env);
	delete_argv(argv);
	//todo delelete env?
	//todo error
}

void	CgiResponse::exec_parent(int pipefd[2], pid_t child_pid)
{
	ssize_t		total_written = 0;
	std::size_t	remaining = getRequestBody().getSize();

	while (remaining > 0)
	{
		ssize_t	bytesWritten = write(pipefd[WRITE_FD], getRequestBody().data().c_str() + total_written, remaining);
		if (bytesWritten == ft::err)
		{
			if (errno == EINTR)
				continue;
			//todo error
		}
		total_written += bytesWritten;
		remaining -= bytesWritten;
	}
	close(pipefd[WRITE_FD]);
	int status = 0;
	while (true)
	{
		pid_t	wpid = waitpid(child_pid, &status, 0);//todo refactor
		if (wpid != ft::err)
			break ;
	}
	if (WIFEXITED(status))
	{
		int exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
		{
			//todo error
		}
		std::string	result = FileReader::readFdFile(pipefd[READ_FD]);
		HttpBody body(result);
		setBody(body);
	}
	else if (WIFSIGNALED(status))
	{
		//todo error child process terminated by signal
	}
	else
	{
		//todo error child processs terminated abnormally
	}
	close(pipefd[READ_FD]);
}

void	CgiResponse::generateResponse(void)
{
	execute();

	setStatus(HttpCode::OK);
	HttpHeader	header;
	header.setHeader("Content-Type", " text/html\r\n");
	std::string size_str = ft::to_string<std::size_t>(getBody().getSize());
	header.setHeader("Content-Length", size_str + "\r\n");
	setHeader(header);
	return ;
}
