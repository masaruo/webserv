#include "ConnectionHandler.hpp"
#include <sys/socket.h>
#include <cerrno>
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
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				break ;
			}
			else
			{
				throw (ConnectionHandlerException("ConnectionHandlerException at 24"));
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

std::string	ConnectionHandler::recvData(int sock_fd, std::size_t buffer_size, ssize_t max_read)
{
	std::string	buffer(buffer_size, '\0');
	std::string	received_data;
	ssize_t		bytes_received;

	while (true)
	{
		bytes_received = recv(sock_fd, &buffer[0], buffer_size, 0);

		if (bytes_received == ft::err)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				break ;
			}
			else
			{
				throw (ConnectionHandlerException("ConnectionHandlerException at 61."));
			}
		}
		else if (bytes_received == ft::eof)
		{
			break ;
		}
		else
		{
			std::string::value_type	readSize = received_data.size() + bytes_received;
			if (readSize > max_read)
			{
				ssize_t appendSize = max_read - received_data.size();
				received_data.append(buffer, 0, appendSize);
				break ;
			}
			else
				received_data.append(buffer, 0, bytes_received);
		}
	}
	return (received_data);
}

void	ConnectionHandler::sendData(int sock_fd, std::string const &data)
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
				throw(ConnectionHandlerException("ConnectionHandlerException at 100."));
			}
		}
		total_sent += bytes_sent;
	}
}

void	ConnectionHandler::sendData(int sock_fd, ft::bytes_vec const &data)
{
	std::size_t				total_sent = 0;
	ssize_t					bytes_sent;

	while (total_sent < data.size())
	{
		bytes_sent = send(sock_fd, data.data() + total_sent, data.size() - total_sent, 0);
		if (bytes_sent == ft::err)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				continue ;
			}
			else
			{
				throw(ConnectionHandlerException("ConnectionHandlerException at 123."));
			}
		}
		total_sent += bytes_sent;
	}
}

ConnectionHandler::ConnectionHandlerException::ConnectionHandlerException(std::string const &msg)
:std::runtime_error(msg)
{
	return ;
}
