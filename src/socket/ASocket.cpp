/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:24:44 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/11 00:32:01 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASocket.hpp"
#include "Server.hpp"
#include <unistd.h>

ASocket::ASocket(int fd, Server &server)
:addr_()
,fd_(fd)
,to_delete_(false)
,last_active_time_(0)
,server_(server)
{
	return ;
}

ASocket::ASocket(sockaddr_in const &addr, int fd, Server &server)
:addr_(addr)
,fd_(fd)
,to_delete_(false)
,last_active_time_(0)
,server_(server)
{
	return ;
}

ASocket::~ASocket()
{
	if (fd_ > 2)
		close (fd_);
	return ;
}

void	ASocket::setFd(int fd)
{
	fd_ = fd;
}

void	ASocket::setAddr(sockaddr_in const &addr)
{
	addr_ = addr;
}

void ASocket::setSocketClose(void) const
{
	to_delete_ = true;
}

time_t	ASocket::getLastActiveTime(void) const
{
	return (last_active_time_);
}

void	ASocket::updateLastActiveTime(void)
{
	time_t	now = time(NULL);
	if (now == -1)
	{
		setSocketClose();
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	last_active_time_ = now;
}

sockaddr_in const &ASocket::getAddr(void) const
{
	return (addr_);
}

int	ASocket::getFd(void) const
{
	return (fd_);
}

bool	ASocket::isDelete(void) const
{
	return (to_delete_);
}
