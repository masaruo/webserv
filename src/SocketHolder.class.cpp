/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHolder.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:36:58 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/26 16:25:32 by mogawa           ###   ########.fr       */
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
	allDeleteSocketHolder();
	return ;
}

// void	SocketHolder::addSocket(ClientSocket *socket)
// {
// 	vec_sockets_.push_back(socket);
// }

void	SocketHolder::addSocket(ASocket *socket)
{
	vec_sockets_.push_back(socket);
}

void	SocketHolder::markSocketDelete(ASocket *socket)
{
	socket->markSocketDelete();
}

// void	SocketHolder::markSocketDelete(iterator iter)
// {
// 	(*iter)->markSocketDelete();
// }

static void	clearVecSocket__(SocketHolder::iterator iter)
{
	delete *iter;
}

static void	deleteSocket__(SocketHolder::iterator iter)
{
	if ((*iter)->getSocketType() == ASocket::to_delete)
	{
		delete *iter;
	}

}

template <typename F>
void	SocketHolder::foreach(F func)
{
	iterator	it = vec_sockets_.begin();
	const_iterator end = vec_sockets_.end();

	while (it != end)
	{
		func(it);
	}
}

void	SocketHolder::allDeleteSocketHolder(void)
{
	foreach(clearVecSocket__);
	vec_sockets_.clear();
}

void	SocketHolder::deleteMarkedSocket(void)
{
	foreach(deleteSocket__);
}

int	SocketHolder::getSize() const
{
	return (vec_sockets_.size());
}
