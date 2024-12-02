/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHolder.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:36:58 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/29 09:55:40 by mogawa           ###   ########.fr       */
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

void	SocketHolder::del(ASocket *socket)
{
	iterator		it = vec_sockets_.begin();
	const_iterator	end = vec_sockets_.end();

	while (it != end)
	{
		if (*it == socket)
		{
			delete *it;
			vec_sockets_.erase(it);//? do i have to keep in tmp?
			return ;
		}
		it++;
	}
	throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
}

void	SocketHolder::deleteMarkedSockets(void)
{
	iterator		it = vec_sockets_.begin();
	const_iterator	end = vec_sockets_.end();

	while (it != end)
	{
		if ((*it)->toDelete())
		{
			delete *it;
			vec_sockets_.erase(it);
		}
		it++;
	}
}

// void	SocketHolder::checkTimeout(void)
// {
// 	if (vec_sockets_.empty())
// 		return ;
// 	iterator		it = vec_sockets_.begin();
// 	const_iterator	end = vec_sockets_.end();

// 	while (it != end)
// 	{
// 		if ((*it)->getSocketType() == ASocket::ACCEPTED)
// 		{
// 			ClientSocket *client = dynamic_cast<ClientSocket*>(*it);
// 			client->check_timeouts();
// 		}
// 		it++;
// 	}
// }

int	SocketHolder::getSize() const
{
	return (static_cast<int>(vec_sockets_.size()));
}
