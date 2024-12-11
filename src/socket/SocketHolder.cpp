/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHolder.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:36:58 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/11 00:26:44 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketHolder.hpp"
#include "define.hpp"
#include "HttpException.hpp"
#include "ASocket.hpp"

SocketHolder::SocketHolder()
:vec_sockets_()
{
	return ;
}

SocketHolder::~SocketHolder()
{
	iterator		it = vec_sockets_.begin();
	const_iterator	end = vec_sockets_.end();

	while (it != end)
	{
		delete *it;
		it++;
	}
	vec_sockets_.clear();
}

void	SocketHolder::add(ASocket *socket)
{
	vec_sockets_.push_back(socket);
}

#include <iostream>
void	SocketHolder::deleteMarkedSockets(int epollfd)
{
	iterator		it = vec_sockets_.begin();
	const_iterator	end = vec_sockets_.end();

	while (it != end)
	{
		if ((*it)->isDelete())
		{
			iterator tmp = it;
			it++;
			int	res = epoll_ctl(epollfd, EPOLL_CTL_DEL, (*tmp)->getFd(), NULL);
			if (res == -1)
			{
				throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
			}
			delete *tmp;
			vec_sockets_.erase(tmp);
		}
		else
		{
			it++;
		}
	}
}

int	SocketHolder::getSize() const
{
	return (static_cast<int>(vec_sockets_.size()));
}
