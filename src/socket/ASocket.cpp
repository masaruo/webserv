/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:24:44 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/03 06:06:56 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASocket.hpp"
#include "Server.hpp"
#include <unistd.h>

ASocket::ASocket(int fd, Server &server)
:fd_(fd)
,server_(server)
,to_delete_(false)
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

void ASocket::setSocketAsClose(void)
{
	to_delete_ = true;
}

sockaddr_in const &ASocket::getAddr(void) const
{
	return (addr_);
}

int	ASocket::getFd(void) const
{
	return (fd_);
}

bool	ASocket::toDelete(void) const
{
	return (to_delete_);
}
