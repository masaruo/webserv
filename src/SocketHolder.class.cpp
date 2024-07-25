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

void	SocketHolder::markDeleteSocket(iterator iter)
{
	(*iter)->markSocketDelete();
}

void	SocketHolder::deleteSockets(void)
{
	if ((*iter)->getSocketType() == ASocket::to_delete)
		vec_.erase(iter);
}
