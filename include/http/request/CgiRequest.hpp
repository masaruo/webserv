#pragma once
#include "ARequest.hpp"
#include "Env.hpp"

class CgiRequest : public ARequest
{
public:
	static int	const	READ_FD;
	static int	const	WRITE_FD;
	static int	const	CHILD_PID;
	static int	const	INTERNAL_SERVER_ERROR;
private:
	//! add client sock adder? so that can be passed onto env?
	std::string	setLocalPath(void) const;
	std::string	execute(std::string const &path) const;
	void		exec_child(int pipe_in[2], int pipe_out[2], std::string const &path) const;
	std::string	exec_parent(int pipe_in[2], int pipe_out[2], pid_t child_pid) const; 
	CgiRequest();//=delete
public:
	explicit CgiRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config);
	explicit CgiRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config);
	~CgiRequest();
	CgiRequest(CgiRequest const &rhs);
	CgiRequest &operator=(CgiRequest const &rhs);

	void	generateResponseData(void);
};
