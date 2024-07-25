/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:45:55 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/24 22:09:39 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListenSocket.class.hpp"
#include "define.hpp"
#include "Fcntl.class.hpp"
#include <unistd.h>

ListenSocket::ListenSocket(int port)
:listening_port_(port)
{
	setSockaddr();
	fd_ = makeListenSocket();
}

ListenSocket::~ListenSocket(void)
{
	close (fd_);
}

void	ListenSocket::setSockaddr(void)
{
	sockaddr_t	ad = sockaddr_;
	ad.addr.sin_family = AF_INET;
	// ad.addr.sin_port = htons(listening_port_);
	ad.addr.sin_port = listening_port_;
	ad.addr.sin_addr.s_addr = INADDR_ANY;
	ad.addrlen = sizeof(ad.addr);
}

int	ListenSocket::makeListenSocket(void)
{
	int	fd = 0;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == ft::err)
	{
		//todo error
	}
	int	optval = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == ft::err)
	{
		//todo error
	}
	if (bind(fd, (struct sockaddr *)&sockaddr_.addr, sockaddr_.addrlen) == ft::err)
	{
		//todo error
	}
	ft::Fcntl::setNonBlock(fd);
	if (listen(fd, SOMAXCONN) == ft::err)
	{
		//todo error
	}
	return (fd);
}
