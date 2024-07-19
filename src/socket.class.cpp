/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 07:34:34 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/19 19:08:15 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.class.hpp"
#include "port.class.hpp"
#include "string.hpp"
#include <unistd.h>
#include <cstring>
#include <fcntl.h>

#ifdef DEBUG
#include <iostream>
#endif

static void  flagNonblock(int fd)
{
    int flag = 0;

    flag = fcntl(fd, F_GETFL);
    if (flag == -1)
    {
        //todo error
    }
    flag |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flag) == -1)
    {
        //todo error
    }
}

Socket::Socket(Port const &port)
:port_(port)
,accepted_fd_(Socket::accept(port.getFd(), &client_addr_, &addrlen_))
,length_(sizeof(buffer_))
,flags_(0)//? MSG_DONOTWAIT
{
	flagNonblock(accepted_fd_);
	return ;
}

Socket::~Socket(void)
{
#ifdef DEBUG
	std::cout << "fd destructor" << std::endl;
#endif
	close (accepted_fd_);
}

int	Socket::accept(int sockfd, struct sockaddr *addr_, socklen_t *addrlen_)
{
	int	accepted_fd = 0;

	accepted_fd = ::accept(sockfd, addr_, addrlen_);
	if (accepted_fd == ERR)
	{
		//todo error
	}	
	return (accepted_fd);
}

ssize_t    Socket::recv(void)
{
	ssize_t	readBytes = 0;
	readBytes = ::recv(accepted_fd_, buffer_, length_, flags_);
	if (readBytes == ERR)
	{
		//todo error
	}
	else if (readBytes == END_OF_FILE)
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
	sendBytes = ::send(accepted_fd_, buffer_, length_, flags_);
	if (sendBytes == ERR)
	{
		//todo err
	}
	else if (sendBytes == END_OF_FILE)
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
