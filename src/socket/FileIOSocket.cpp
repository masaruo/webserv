#include "FileIOSocket.hpp"
#include "SocketHolder.class.hpp"
#include "ASocket.class.hpp"
#include "Fcntl.class.hpp"
#include "unistd.h"

FileIOSocket::FileIOSocket()
:ASocket(ASocket::IDLE)
,buffer_()
{
	pair_fd_[0] = -1;
	pair_fd_[1] = -1;
	return ;
}

FileIOSocket::~FileIOSocket()
{
	if (pair_fd_[0] != -1)
		close (pair_fd_[0]);
	if (pair_fd_[1] != -1)
		close (pair_fd_[1]);
}

void	FileIOSocket::setSockaddr(void)
{
	
}

void	FileIOSocket::init(void)
{
	if (pair_fd_[0] != -1)
		close (pair_fd_[0]);
	if (pair_fd_[1] != -1)
		close (pair_fd_[1]);

	int	tmp[2];
	int	res = socketpair(AF_UNIX, SOCK_STREAM, 0, tmp);
	if (res == -1)
	{
		//todo error
	}

	ft::Fcntl::setNonBlock(tmp[ft::READFD]);
	ft::Fcntl::setNonBlock(tmp[ft::WRITEFD]);

	pair_fd_[ft::READFD] = tmp[ft::READFD];
	pair_fd_[ft::WRITEFD] = tmp[ft::WRITEFD];
}

ssize_t	FileIOSocket::readFile(std::string const &data)
{
	// if (getSocketType() == IDLE)
	// 	return (-1);

	init();
	// int bytes = writeFile(pair_fd_[ft::WRITEFD], data);
	int bytes = ::send(pair_fd_[ft::WRITEFD], &data[0], data.size(), MSG_NOSIGNAL);
	if (bytes == -1)
	//todo error
		;

	std::string	tmp(ft::READ_BUF_SIZE, '\0');
	bytes = ::recv(pair_fd_[ft::READFD], &buffer_[0], ft::READ_BUF_SIZE, MSG_DONTWAIT | MSG_NOSIGNAL);
	if (bytes == -1)
		//todo error
		;
	else if (bytes > 0)
	{
		setSocketType(RECV);
		tmp.resize(bytes);
		buffer_.append(tmp);
	}
	else if (bytes == 0)
	{
		setSocketType(IDLE);
	}
	return (bytes);
}

ssize_t	FileIOSocket::writeFile(int writeto, std::string const &data)
{
	if (getSocketType() != IDLE)
		return (-1);

	init();
	
	ssize_t sent = ::send(pair_fd_[ft::WRITEFD], data.c_str(), data.length(), MSG_NOSIGNAL);
	if (sent == -1)
		return (-1);

	std::string	tmp(ft::WRITE_BUF_SIZE, '\0');
	ssize_t bytes = ::recv(pair_fd_[ft::READFD], &tmp[0], sizeof(tmp), MSG_DONTWAIT | MSG_NOSIGNAL);
	if (bytes == -1)
		return (-1);
	tmp.resize(bytes);
	ssize_t written = ::send(writeto, tmp.c_str(), sizeof(tmp), MSG_NOSIGNAL);
	if (written > 0)
	{
		setSocketType(SEND);
	}
	else if (written == 0)
	{
		setSocketType(IDLE);
	}

	return written;
}



std::string	FileIOSocket::getBufferData(void) const
{
	return (buffer_);
}

// std::string	FileIOSocket::read(int fd)
// {
// 	// ::read(target_fd_, &buffer_[0], sizeof(buffer_));
// 	init();
// 	setSocketType(WRITE);
// 	ssize_t	bytes = ::send(pair_fd_[ft::WRITEFD], )
// }

std::string FileIOSocket::read(std::string const &target_path)
{
	init();
}
