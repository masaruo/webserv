/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenImpl.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:44:51 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/31 05:02:12 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListenImpl.hpp"
#include <fcntl.h>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

static sockaddr_in	getSockAddr_(int port)
{
	sockaddr_in addr;

	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(static_cast<uint16_t>(port));
	addr.sin_addr.s_addr = INADDR_ANY;
	return (addr);
}

static int	getListenSocket_(int port)
{
	sockaddr_in	const &addr = getSockAddr_(port);
	int	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		throw (std::runtime_error("Socket failed"));
	int	optval = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
		throw (std::runtime_error("Socket failed"));
	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		throw (std::runtime_error("Socket failed"));
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		throw (std::runtime_error("Socket failed"));
	if (listen(fd, SOMAXCONN) == -1)
		throw (std::runtime_error("Socket failed"));
	return (fd);
}

ListenImpl::ListenImpl(int port)
:port_(port)
,fd_(getListenSocket_(port))
{
	return ;
}

ListenImpl::ListenImpl(int port, int fd)
:port_(port)
,fd_(fd)
{
	return ;
}

ListenImpl::~ListenImpl()
{
	close();
	return ;
}

int	ListenImpl::getFd(void) const
{
	return (fd_.getFd());
}

void	ListenImpl::close(void)
{
	fd_.close();
}

// ISocket	*ListenImpl::clone(void)
// {
// 	ListenImpl	*copy = new ListenImpl(port_, fd_.transfer());
// 	return (copy);
// }
