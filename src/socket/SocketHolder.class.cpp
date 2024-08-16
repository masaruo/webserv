/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHolder.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:36:58 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/28 14:00:05 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketHolder.class.hpp"
#include "ClientSocket.class.hpp"
#include "ListenSocket.class.hpp"

SocketHolder::SocketHolder()
{
	return ;
}

SocketHolder::~SocketHolder()
{
	deleteSocketHolder();
	return ;
}

void	SocketHolder::addSocket(ASocket *socket)
{
	vec_sockets_.push_back(socket);
}

void	SocketHolder::checkTimeout(void)
{
	if (vec_sockets_.empty())
		return ;
	iterator		it = vec_sockets_.begin();
	const_iterator	end = vec_sockets_.end();

	while (it != end)
	{
		if ((*it)->getSocketType() == ASocket::accepted)
		{
			ClientSocket *client = dynamic_cast<ClientSocket*>(*it);
			client->check_timeouts();
		}
		it++;
	}
}

void	SocketHolder::markSocketDelete(ASocket *socket)
{
	socket->markSocketDelete();
}

static void	clearVecSocket__(SocketHolder::iterator iter)
{
	delete *iter;
}

int	SocketHolder::getSize() const
{
	return (vec_sockets_.size());
}

void	SocketHolder::deleteSocketHolder(void)
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

void	SocketHolder::deleteMarkedSocket(void)
{
	iterator		it = vec_sockets_.begin();
	const_iterator	end = vec_sockets_.end();

	while (it != end)
	{
		if ((*it)->getSocketType() == ASocket::to_delete)
		{
			iterator tmp = it;
			it++;
			delete *tmp;
			vec_sockets_.erase(tmp);
		}
		else
			it++;
	}
}
