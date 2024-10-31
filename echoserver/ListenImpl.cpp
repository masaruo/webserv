/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenImpl.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:44:51 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/31 03:02:32 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListenImpl.hpp"
#include "Fcntl.class.hpp"
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

sockaddr_in	getSockAddr_(int port)
{
	sockaddr_in addr;

	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(static_cast<uint16_t>(port));
	addr.sin_addr.s_addr = INADDR_ANY;
	return (addr);
}

ListenImpl::ListenImpl(int port)
:port_(port)
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
	ft::Fcntl::setNonBlock(fd);
	if (listen(fd, SOMAXCONN) == -1)
		throw (std::runtime_error("Socket failed"));

	fd_ = fd;
	return ;
}

ListenImpl::~ListenImpl()
{
	close();
	return ;
}

void	ListenImpl::close(void)
{
	if (fd_ >= 3)
	{
		::close(fd_);
		fd_ = -1;
	}
}

int	ListenImpl::getFd(void) const
{
	return (fd_);
}
