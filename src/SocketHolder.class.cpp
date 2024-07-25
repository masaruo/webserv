/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHolder.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:36:58 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/24 23:47:33 by mogawa           ###   ########.fr       */
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
	return ;
}

void	SocketHolder::addSocket(ClientSocket *socket)
{
	vec_.push_back(socket);
}

void	SocketHolder::addSocket(ListenSocket *socket)
{
	vec_.push_back(socket);
}

void	SocketHolder::markSocketDelete(iterator iter)
{
	(*iter)->markSocketDelete();
}

static void	clearVecSocket(SocketHolder::iterator iter)
{
	delete *iter;
}

static void	deleteSocket(SocketHolder::iterator iter)
{
	if ((*iter)->getSocketType() == ASocket::to_delete)
	{
		delete *iter;
	}

}

template <typename F>
void	SocketHolder::foreach(F func)
{
	iterator	it = vec_.begin();
	const_iterator end = vec_.end();

	while (it != end)
	{
		func(it);
	}
}

void	SocketHolder::clearSocketVec(void)
{
	foreach(clearVecSocket);
	vec_.clear();
}

// void	SocketHolder::deleteSockets(void)
// {
// 	if ((*iter)->getSocketType() == ASocket::to_delete)
// 		vec_.erase(iter);
// }
