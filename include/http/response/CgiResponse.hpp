#pragma once
#include "AResponse.hpp"
#include "unique_ptr.hpp"
#include "env.hpp"

//todo environ
class CgiResponse : public AResponse
{
private:
	Env				env_;
	ft::bytes_vec	body_;
	void	execute(void);
	void	exec_child(int pipefd[2]) const;
	void	exec_parent(int pipefd[2], pid_t child_pid);
	static int const	READ_FD;
	static int const	WRITE_FD;
	static int const	CHILD_PID;
	CgiResponse();// = delete
public:
	explicit CgiResponse(std::string const &uri, HttpHeader const &req_header);
	~CgiResponse();
	CgiResponse(CgiResponse const &rhs);
	CgiResponse &operator=(CgiResponse const &rhs);
	ft::bytes_vec	generateResponse(void);
};
