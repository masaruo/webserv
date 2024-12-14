/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHolder.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:36:58 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/14 01:20:35 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketHolder.hpp"
#include "define.hpp"
#include "HttpException.hpp"
#include "ASocket.hpp"
#include "ClientSocket.hpp"
#include "CgiSocket.hpp"
#include "Response.hpp"

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

void	SocketHolder::deleteMarkedSockets(int epollfd)
{
	iterator		it = vec_sockets_.begin();

	while (it != vec_sockets_.end())
	{
		if ((*it)->isDelete())
		{
			int	res = epoll_ctl(epollfd, EPOLL_CTL_DEL, (*it)->getFd(), NULL);
			if (res == -1)
			{
				throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
			}
			delete *it;
			it = vec_sockets_.erase(it);
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
