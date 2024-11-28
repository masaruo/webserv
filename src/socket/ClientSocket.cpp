/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:52:30 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/28 04:03:56 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"
#include "define.hpp"
#include "Server.hpp"

#include <sys/epoll.h>

ClientSocket::ClientSocket(int fd, Server &server)
:ASocket(fd, server)
{
	return ;
}

ClientSocket::~ClientSocket()
{
	// delete request_;
}



void	ClientSocket::handleEvent(uint32_t event)
{
	if (event == EPOLLIN)
	{
		std::string buf(ft::READ_BUF_SIZE, 0);
		ssize_t	bytes = ::recv(getFd(), &buf[0], buf.size(), 0);
		factory_.parse(buf, bytes);
		if (factory_.isParseCompleted())
		{
			server_.mod(this, 0);
			// todo process request
		}
	}
	else if (event == EPOLLOUT)
	{
		// execute();
	}
	else
	{
		throw (std::runtime_error("Socket failed"));
	}
}
