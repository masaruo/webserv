/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:10:36 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/28 13:06:16 by mogawa           ###   ########.fr       */
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
ssize_t	ClientSocket::recv_handler(void)
{
	char * buf[10];
	int n = recv(fd_, buf, sizeof(buf), MSG_DONTWAIT);
	if (n < 0)
		return (-1) ;
	else
	{
		std::cout << "recv handler" << std::endl;
		send(fd_, buf, sizeof(buf), MSG_DONTWAIT);
	}
	return (0);
}

ssize_t	ClientSocket::send_hander(void) const
{
	std::cout << "send hander" << std::endl;
	return (0);
}
