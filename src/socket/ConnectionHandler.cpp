#include "ConnectionHandler.hpp"
#include <sys/socket.h>
#include <cerrno>//todo delete
#include "define.hpp"

std::string	ConnectionHandler::recvData(int sock_fd, std::size_t buffer_size)
{
	std::string	buffer(buffer_size, '\0');
	std::string	received_data;
	ssize_t		bytes_received;

	while (true)
	{
		bytes_received = recv(sock_fd, &buffer[0], buffer_size, 0);

		if (bytes_received == ft::err)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)//todo change
			{
				break ;
			}
			else
			{
				//todo error handle
			}
		}
		else if (bytes_received == ft::eof)
		{
			break ;
		}
		else
		{
			received_data.append(buffer, 0, bytes_received);

			if(received_data.find("\r\n\r\n") != std::string::npos)
			{
				break ;
			}
		}
	}
	return (received_data);
}

bool	ConnectionHandler::sendData(int sock_fd, std::string const &data)
{
	std::size_t				total_sent = 0;
	ssize_t					bytes_sent;

	while (total_sent < data.length())
	{
		bytes_sent = send(sock_fd, data.c_str() + total_sent, data.length() - total_sent, 0);
		if (bytes_sent == ft::err)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				continue ;
			}
			else
			{
				//todo error
				return (false);
			}
		}
		total_sent += bytes_sent;
	}
	return (true);
}
