/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHolder.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:36:58 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/25 05:48:18 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketHolder.class.hpp"
#include "ClientSocket.class.hpp"
#include "ListenSocket.class.hpp"
#include "define.hpp"
#include "HttpException.hpp"

SocketHolder::vec_socket	SocketHolder::vec_sockets_;
Epoller						*SocketHolder::poller_ = NULL;

void	SocketHolder::init(Epoller *poller)
{
	if (poller_ == NULL)
		poller_ = poller;
}

void	SocketHolder::addSocket(ASocket *socket)
{
	if (vec_sockets_.size() > ft::MAX_SOCKET_NUM)
		throw (HttpException(HttpCode::SERVICE_UNAVAILABLE));
	vec_sockets_.push_back(socket);
}

// void	SocketHolder::checkTimeout(void)
// {
// 	if (vec_sockets_.empty())
// 		return ;
// 	iterator		it = vec_sockets_.begin();
// 	const_iterator	end = vec_sockets_.end();

// 	while (it != end)
// 	{
// 		if ((*it)->getSocketType() == ASocket::accepted)
// 		{
// 			ClientSocket *client = dynamic_cast<ClientSocket*>(*it);
// 			client->check_timeouts();
// 		}
// 		it++;
// 	}
// }

void	SocketHolder::markSocketDelete(ASocket *socket)
{
	socket->markSocketDelete();
}

int	SocketHolder::getSize()
{
	return (static_cast<int>(vec_sockets_.size()));
}

void	SocketHolder::destructor(void)
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
