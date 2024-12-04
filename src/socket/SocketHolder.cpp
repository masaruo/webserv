/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHolder.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:36:58 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/04 08:49:50 by mogawa           ###   ########.fr       */
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

void	SocketHolder::cleanUpSockets(void)
{
	iterator		it = vec_sockets_.begin();
	const_iterator	end = vec_sockets_.end();

	while (it != end)
	{
		ASocket *socket = *it;
		if (socket->toDelete() || socket->isObsolete())
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

int	SocketHolder::getSize() const
{
	return (static_cast<int>(vec_sockets_.size()));
}
