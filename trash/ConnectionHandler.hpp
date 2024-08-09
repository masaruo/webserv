#pragma once
#include "string.hpp"


class ConnectionHandler
{
private:
	ConnectionHandler(){};
	~ConnectionHandler(){};
	ConnectionHandler(ConnectionHandler const &rhs);
	ConnectionHandler &operator=(ConnectionHandler const &rhs);
public:
	static	ft::string	recvData(int sock_fd, std::size_t buf_size);
	static	bool		sendData(int sock_fd, ft::string const &data);
};
