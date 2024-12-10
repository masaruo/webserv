/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:24:44 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/29 09:55:30 by mogawa           ###   ########.fr       */
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

int	ASocket::getFd(void) const
{
	return (fd_);
}

bool	ASocket::toDelete(void) const
{
	return (to_delete_);
}
