#pragma once
#include "ARequest.hpp"
#include "env.hpp"

class CgiRequest : public ARequest
{
public:
	static int	const	READ_FD;
	static int	const	WRITE_FD;
	static int	const	CHILD_PID;
private:
	Env	env_;

	void	execute(void) const;
	void	exec_child(int pipefd[2]) const;
	void	exec_parent(int pipefd[2], pid_t child_pid) const; 
	CgiRequest();//=delete
public:
	explicit CgiRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config);
	~CgiRequest();
	CgiRequest(CgiRequest const &rhs);
	CgiRequest &operator=(CgiRequest const &rhs);

	Response	generateResponse(void) const;
};
