/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:40:19 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/15 02:54:43 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListenSocket.hpp"
#include "Server.hpp"
#include "ClientSocket.hpp"
#include <cstring>
#include <stdexcept>
#include <fcntl.h>
#include <sys/epoll.h>
#include <unistd.h>

static sockaddr_in	getPassiveSockAddr_(int port)
{
	sockaddr_in addr;

	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(static_cast<uint16_t>(port));
	addr.sin_addr.s_addr = INADDR_ANY;
	return (addr);
}

static int	getListenFd_(int port)
{
	sockaddr_in	const &addr = getPassiveSockAddr_(port);
	int	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		throw (std::runtime_error("Listen Socket failed"));
	int	optval = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
		throw (std::runtime_error("Listen Socket failed"));
	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		throw (std::runtime_error("Listen Socket failed"));
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		throw (std::runtime_error("Listen Socket failed"));
	if (listen(fd, SOMAXCONN) == -1)
		throw (std::runtime_error("Listen Socket failed"));
	return (fd);
}

ListenSocket::ListenSocket(int port, Server &server)
:ASocket(getListenFd_(port), server)
{
	return ;
}

ListenSocket::~ListenSocket()
{
	return ;
}

void	ListenSocket::assertTimeout(void)
{
	return ;
}

void	ListenSocket::handleEvent(uint32_t event)
{
	if (server_.getSocketHolderSize() > ft::MAX_SOCKET_NUM)
		return ;

	if (event != EPOLLIN)
		return ;
	sockaddr_in	addr;
	socklen_t	addrlen = sizeof(addr);

	int clientFd = accept(getFd(), (struct sockaddr*)&addr, &addrlen);
	if (clientFd == -1)
		return ;
	if (fcntl(clientFd, F_SETFL, O_NONBLOCK) == -1)
	{
		close (clientFd);
		return ;
	}
	ClientSocket	*client = new ClientSocket(addr, clientFd, server_);
	server_.add(client, EPOLLIN);
}

time_t	ListenSocket::getLastActiveTime(void) const
{
	return (0);
}
