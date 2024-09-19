#pragma once
#include "AResponse.hpp"
#include "unique_ptr.hpp"
#include "env.hpp"

//todo environ
class CgiResponse : public AResponse
{
private:
	Env				env_;
	void	execute(void);
	void	exec_child(int pipefd[2]) const;
	void	exec_parent(int pipefd[2], pid_t child_pid);
	static int const	READ_FD;
	static int const	WRITE_FD;
	static int const	CHILD_PID;
	CgiResponse();// = delete
public:
	explicit CgiResponse(ft::unique_ptr<ARequest>request);
	// explicit CgiResponse(std::string const &uri, HttpHeader const &req_header, HttpBody const &req_body);
	~CgiResponse();
	CgiResponse(CgiResponse const &rhs);
	CgiResponse &operator=(CgiResponse const &rhs);
	void	generateResponse(void);
};
