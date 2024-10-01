#pragma once
#include <string>
#include <sys/types.h>
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
};
