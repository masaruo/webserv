#pragma once
#include <string>


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
	//todo recvBody
};
