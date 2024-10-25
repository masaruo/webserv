/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:45:55 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/25 06:53:14 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListenSocket.class.hpp"
#include "define.hpp"
#include "Fcntl.class.hpp"
#include <unistd.h>

ListenSocket::ListenSocket(int port)
:ASocket(ASocket::LISTEN)
,listening_port_(port)
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
	addr_.addr.sin_family = AF_INET;
	addr_.addr.sin_port = htons(static_cast<uint16_t>(listening_port_));
	addr_.addr.sin_addr.s_addr = INADDR_ANY;
	addr_.addrlen = sizeof(addr_.addr);
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
	if (bind(fd, (struct sockaddr *)&addr_.addr, addr_.addrlen) == ft::err)
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
