#pragma once
#include <string>
#include "define.hpp"

class ConnectionHandler
{
private:
	ConnectionHandler(){};
	~ConnectionHandler(){};
	ConnectionHandler(ConnectionHandler const &rhs);
	ConnectionHandler &operator=(ConnectionHandler const &rhs);
public:
	static	std::string	recvData(int sock_fd, std::size_t buf_size);
	static	bool		sendData(int sock_fd, std::string const &data);
	static	bool		sendData(int sock_fd, ft::bytes_vec const &data);
	//todo recvBody
};
