/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHolder.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:36:58 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/12 05:30:43 by mogawa           ###   ########.fr       */
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

// void	SocketHolder::markInactieSocketsDelete(void)
// {
// 	time_t	now = time(NULL);
// 	if (now == -1)
// 		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

// 	iterator	iter = vec_sockets_.begin();
// 	while (iter != vec_sockets_.end())
// 	{
// 		ASocket *socket = *iter;
// 		time_t	lastActive = socket->getLastActiveTime();
// 		if (lastActive != 0 && now > lastActive + ft::TIMEOUT)
// 		{
// 			// socket->setSocketClose();
// 			Response	res = HttpException(HttpCode::REQUEST_TIMEOUT).generateResponse();
			
// 		}
// 		iter++;
// 	}
// }

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
