#pragma once
#include "ARequest.hpp"
#include "Env.hpp"

class ActiveSocket;

class CgiRequest : public ARequest
{
public:
	static int	const	READ_FD;
	static int	const	WRITE_FD;
	static int	const	CHILD_PID;
	static int	const	INTERNAL_SERVER_ERROR;
private:
	//! add client sock adder? so that can be passed onto env?
	ActiveSocket	*cgi_socket_;
	pid_t			child_pid_;
	std::string	setLocalPath(void) const;
	void		execute(std::string const &path);
	void		exec_child(int sockfds[2], std::string const &path) const;
	void		exec_parent(int sockfds[2]); 
	CgiRequest();//=delete
public:
	explicit CgiRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config, Server &server);
	explicit CgiRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config, Server &server);
	~CgiRequest();
	CgiRequest(CgiRequest const &rhs);
	CgiRequest &operator=(CgiRequest const &rhs);

	void	waitForCompletion(void);
	void	generateResponseData(void);
};
