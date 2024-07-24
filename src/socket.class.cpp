/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 07:34:34 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/24 16:36:53 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.class.hpp"
#include "port.class.hpp"
#include "string.hpp"
#include "Fcntl.class.hpp"
#include "define.hpp"
#include <unistd.h>
#include <cstring>

#include <iostream>

Socket::Socket()
:fd_(0)
,length_(sizeof(buffer_))
,flags_(0)
,is_listening(false)
,to_delete(false)
{
	return ;
}

Socket::Socket(Port const &port)
:fd_(port.getFd())
,length_(sizeof(buffer_))
,flags_(0)
,is_listening(true)
,to_delete(false)
{
	ft::Fcntl::setNonBlock(fd_);
	return ;
}

Socket::Socket(Socket const &rhs)
{
	*this = rhs;
}

Socket &Socket::operator=(Socket const &rhs)
{
	if (this != &rhs)
	{
		fd_ = rhs.fd_;
		length_ = rhs.length_;
		flags_ = rhs.flags_;
		is_listening = rhs.is_listening;
	}
	return (*this);
}

Socket::~Socket(void)
{
	close (fd_);
}

Socket	Socket::accept(void) const
{
	Socket	client;
	int const	listening_fd = this->fd_;
	int	accepted = 0;
	// accepted = ::accept(listening_fd, &client.client_addr_, &client.addrlen_);
	accepted = ::accept(listening_fd, NULL, NULL);
	//todo error
	ft::Fcntl::setNonBlock(accepted);
	client.fd_ = accepted;
	return (client);
}

ssize_t    Socket::recv(void)
{
	ssize_t	readBytes = 0;
	readBytes = ::recv(fd_, buffer_, length_, flags_);
	if (readBytes == ft::err)
	{
		//todo error
	}
	else if (readBytes == ft::eof)
	{
		//todo eof
	}
	else
	{
		ft::string	str(buffer_);
		bufStr_ = str;
		#ifdef DEBUG
			std::cout << "read buf:" << buffer_ << std::endl;
		#endif
	}
	return (readBytes);
}

ssize_t    Socket::send(void) const
{
	ssize_t	sendBytes = 0;
	sendBytes = ::send(fd_, buffer_, length_, flags_);
	if (sendBytes == ft::err)
	{
		//todo err
	}
	else if (sendBytes == ft::eof)
	{
		//todo eof
	}
	else
	{
		#ifdef DEBUG
			std::cout << "send buf:" << bufStr_ << std::endl;
		#endif
	}
	return (sendBytes);
}

void	Socket::updateBuf(ft::string out)
{
	bufStr_ = out;
	std::strncpy(buffer_, bufStr_.c_str(), BUFSIZE - 1);
	buffer_[BUFSIZE - 1] = '\0'; 
	// buffer_ = bufStr_.c_str();
	return ;
}

int	Socket::getFd(void) const
{
	return (fd_);
}

bool	Socket::getSocketType(void) const
{
	return (is_listening);
}

bool	Socket::getToDelete(void) const
{
	return (to_delete);
}

void	Socket::makeToDelete(void)
{
	to_delete = true;
}

void	Socket::makeNoListening(void)
{
	is_listening = false;
}
