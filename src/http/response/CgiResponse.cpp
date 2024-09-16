#include "CgiResponse.hpp"
#include <unistd.h>
#include <string.h>
#include "FileHandler.hpp"
#include <sys/wait.h>
#include <cstring>

int const	CgiResponse::READ_FD = 0;
int const	CgiResponse::WRITE_FD = 1;
int const	CgiResponse::CHILD_PID = 0;

CgiResponse::CgiResponse(std::string const &uri, HttpHeader const &req_header, HttpBody const &req_body)
:AResponse(uri, req_header)
,request_body_(req_body)
,env_(uri, req_header, req_body)
{
	return ;
}

CgiResponse::~CgiResponse()
{
	return ;
}

CgiResponse::CgiResponse(CgiResponse const &rhs)//todo
:AResponse(rhs)
,request_body_(rhs.request_body_)
,env_(rhs.env_)
{
	return ;
}

CgiResponse &CgiResponse::operator=(CgiResponse const &rhs)
{
	if (this != &rhs)
	{
		AResponse::operator=(rhs);
		request_body_ = rhs.request_body_;
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
void	CgiResponse::exec_child(int pipefd[2]) const
{
	if (close(pipefd[READ_FD]) == ft::err)
	{
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
	MockPath mock;
	char **argv = create_argv(mock.getPath(getUri()));
	// char **argv = create_argv("/webserv/cgi-bin/process.cgi");
	char **env = env_.to_cenv();
	execve(argv[0], argv, env);
	delete_argv(argv);
	//todo delelete env?
	//todo error
}

void	CgiResponse::exec_parent(int pipefd[2], pid_t child_pid)
{
	close(pipefd[WRITE_FD]);

	int status = 0;
	pid_t	wpid = waitpid(child_pid, &status, 0);//todo refactor
	//todo while loop?
	if (wpid == ft::err)
	{
		//todo error
	}
	else if (WIFEXITED(status))
	{
		ft::bytes_vec	result = FileReader::readFdFile(pipefd[READ_FD]);
		Binary	bin(result);
		HttpBody body(bin);
		setBody(body);
	}
	close(pipefd[READ_FD]);
}

void	CgiResponse::generateResponse(void)
{
	execute();
	StatusCode status(StatusCode::OK_NOCONTENT);
	setCode(status);
	return ;
}
