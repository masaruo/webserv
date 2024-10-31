/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientImpl.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 02:34:26 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/31 03:04:24 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientImpl.hpp"
#include "Fcntl.class.hpp"
#include <sys/socket.h>
#include <stdexcept>
#include <cstring>
#include <unistd.h>

ClientImpl::ClientImpl(int listening_fd)
{
	std::memset(&addr_, 0, sizeof(addr_));
	int	fd = accept(listening_fd, (struct sockaddr *)&addr_, &addrlen_);
	if (fd == -1)
		throw (std::runtime_error("clientimpl"));
	ft::Fcntl::setNonBlock(fd);
	fd_ = fd;
}

ClientImpl::~ClientImpl()
{
	close();
	return ;
}

void	ClientImpl::close(void)
{
	if (fd_ > 3)
	{
		::close(fd_);
		fd_ = -1;
	}
}

int	ClientImpl::getFd(void) const
{
	return (fd_);
}
