/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:10:36 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/28 14:18:54 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ClientSocket.class.hpp>
#include "define.hpp"
#include "Fcntl.class.hpp"
#include "unistd.h"

ClientSocket::ClientSocket(int listen_fd)
:ASocket(ASocket::accepted)
{
	fd_ = acceptHandler(listen_fd);
	return ;
}

ClientSocket::~ClientSocket()
{
	close (fd_);
}

int	ClientSocket::acceptHandler(int listen_fd)
{
	int	fd = 0;

	fd = accept(listen_fd, NULL, NULL);//todo sockaddr_t
	if (fd == ft::err)
	{
		//todo error
	}
	ft::Fcntl::setNonBlock(fd);
	return (fd);
}

void	ClientSocket::setSockaddr(void)
{
	//todo
}

#include <iostream>
ssize_t	ClientSocket::recv_handler(void)//! create request class and return response class?
{
	std::string	buf;
	buf.resize(1000);
	// char * buf[1000];
	int n = recv(fd_, (void *)buf.data(), sizeof(buf), MSG_DONTWAIT);
	std::cout << "received: " << buf << std::endl;
	if (n < 0)
		return (-1) ;
	else
	{
		std::string ret = "sent back by server: " + buf;
		send(fd_, ret.data(), ret.size(), MSG_DONTWAIT);
	}
	return (0);
}

ssize_t	ClientSocket::send_hander(void) const
{
	std::cout << "send hander" << std::endl;
	return (0);
}
