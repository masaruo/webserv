/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:47:23 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/23 11:53:38 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "port.class.hpp"
#include <unistd.h>
#include "Fcntl.class.hpp"
#include "define.hpp"

static struct sockaddr_in   setSockaddr(int port)
{
	struct sockaddr_in  addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	return (addr);
}

Port::Port(int port)
:port_(port)
,addr_(setSockaddr(port))
{
	fd_ = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_ == ft::err)
	{
		//todo error
	}
	int optval = 1;
	if (setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == ft::err)
	{
		//todo error
	}
	if (bind(fd_, (struct sockaddr *)&addr_, sizeof(addr_)) == ft::err)//? static_cast?
	{
		//todo error
	}
	ft::Fcntl::setNonBlock(fd_);
	if (listen(fd_, SOMAXCONN))
	{
		//todo error
	}
	return ;   
}

Port::~Port()
{
	::close (fd_);
	return ;

}

int	Port::getFd(void) const
{
	return (fd_);
}
