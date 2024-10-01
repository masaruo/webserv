#include "CgiRequest.hpp"
#include "Response.hpp"
#include "unistd.h"

int const	CgiRequest::READ_FD = 0;
int const	CgiRequest::WRITE_FD = 1;
int const	CgiRequest::CHILD_PID = 0;


CgiRequest::CgiRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config)
:ARequest(line, header, body, config)
,env_(getLine(), getHeader(), getBody())
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

void	CgiRequest::exec_child(int pipefd[2]) const
{
	bool	is_error = false;
	if (dup2(pipefd[READ_FD], STDIN_FILENO) == ft::err)
	{
		is_error = true;
	}
	if (close(pipefd[READ_FD]) == ft::err)
	{
		is_error = true;
	}
	if (dup2(pipefd[WRITE_FD], STDOUT_FILENO) == ft::err)
	{
		is_error = true;
	}
	if (close(pipefd[WRITE_FD]) == ft::err)
	{
		is_error = true;
	}
	if (is_error)
		throw (HttpStatus::HttpStatusException(HttpCode::INTERNAL_SERVER_ERROR));


}

void	CgiRequest::exec_parent(int pipefd[2], int child_pid) const
{

}

void	CgiRequest::execute(void) const
{
	int		pipefd[2];
	pid_t	child_pid = 0;

	if (pipe(pipefd) == ft::err)
	{
		throw (HttpStatus::HttpStatusException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	child_pid = fork();
	if (child_pid == ft::err)
	{
		throw (HttpStatus::HttpStatusException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	else if (child_pid == CHILD_PID)
	{
		exec_child(pipefd);
	}
	else
	{
		exec_parent(pipefd, child_pid);
	}
}

Response	CgiRequest::generateResponse(void) const
{
	execute();
	//todo
}
