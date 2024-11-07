/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassiveSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:40:19 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/02 06:58:49 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PassiveSocket.hpp"
#include "ActiveSocket.hpp"
#include "Server.hpp"
#include <cstring>
#include <stdexcept>
#include <fcntl.h>
#include <sys/epoll.h>

static sockaddr_in	getPassiveSockAddr_(int port)
{
	sockaddr_in addr;

	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(static_cast<uint16_t>(port));
	addr.sin_addr.s_addr = INADDR_ANY;
	return (addr);
}

static int	getPassiveFd_(int port)
{
	sockaddr_in	const &addr = getPassiveSockAddr_(port);
	int	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		throw (std::runtime_error("Socket failed"));
	int	optval = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
		throw (std::runtime_error("Socket failed"));
	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		throw (std::runtime_error("Socket failed"));
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		throw (std::runtime_error("Socket failed"));
	if (listen(fd, SOMAXCONN) == -1)
		throw (std::runtime_error("Socket failed"));
	return (fd);
}

PassiveSocket::PassiveSocket(int port, Server &server)
:ASocket(port, getPassiveFd_(port), ft::PASSIVE, EPOLLIN, server)
{
	return ;
}

PassiveSocket::~PassiveSocket()
{
	return ;
}

void	PassiveSocket::execute(void)
{
	Addr	addr;
	int		fd = 0;

	fd = accept(getFd(),(struct sockaddr*)&addr.addrin_, &addr.addrlen_);
	if (fd == -1)
	{
		throw (std::runtime_error("Socket failed"));
	}
	getServer().addSocket(new ActiveSocket(getPort(), fd, ft::RECV_REQUESTLINE, EPOLLIN, getServer(),addr));
	// SocketHolder::addSocket(new ActiveSocket(getPort(), fd, ft::RECV_REQUESTLINE, EPOLLIN, addr));
}
