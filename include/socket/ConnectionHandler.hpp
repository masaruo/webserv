#pragma once
#include <string>
#include <sys/types.h>
#include <stdexcept>
#include <string>
#include "define.hpp"

class ConnectionHandler
{
public:
	const ssize_t	NOLIMIT = 0;
private:
	ConnectionHandler(){};
	~ConnectionHandler(){};
	ConnectionHandler(ConnectionHandler const &rhs);
	ConnectionHandler &operator=(ConnectionHandler const &rhs);
public:
	static	std::string	recvData(int sock_fd, std::size_t buf_size);
	static	std::string	recvData(int sock_fd, std::size_t buf_size, ssize_t max_read);
	static	void		sendData(int sock_fd, std::string const &data);
	// static	void		sendData(int sock_fd, ft::bytes_vec const &data);
	class ConnectionHandlerException : public std::runtime_error
	{
	public:
		ConnectionHandlerException(std::string const &msg);
	};
};
