/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoller.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:24:00 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/26 16:44:28 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "epoller.class.hpp"
#include "SocketHolder.class.hpp"
#include "ASocket.class.hpp"
#include "ClientSocket.class.hpp"
#include "define.hpp"
#include <sys/epoll.h>
#include <unistd.h>// close()
#include <iostream>

Epoller::Epoller(int size, int timeout)
:epfd_(epoll_create(size))
,timeout_(timeout)
{
	if (epfd_ == ft::err)//todo timeout minus
	{
		//todo erro
	}
	return ;
}

Epoller::~Epoller()
{
	close (epfd_);
}

void	Epoller::epollAdd(ASocket *socket)
{
	epoll_event	ev;
	ev.events = EPOLLIN | EPOLLRDHUP | EPOLLHUP;
	ev.data.ptr = socket;
	int	res = 0;
	res = epoll_ctl(epfd_, EPOLL_CTL_ADD, socket->getFd(), &ev);
	if (res == ft::err)
	{
		//todo error
	}
	SocketHolder_.addSocket(socket);
	return ;
}

void	Epoller::epollClose(ASocket *socket)
{
	int res = 0;
	res = epoll_ctl(epfd_, EPOLL_CTL_DEL, socket->getFd(), NULL);
	if (res == ft::err)
	{
		//todo error
	}
	socket->markSocketDelete();
}

#include <cerrno>
int	Epoller::epollWait(void)
{
	int	size = SocketHolder_.getSize();
	res_evlist_.resize(size);
	int	res = 0;
	res = epoll_wait(epfd_, res_evlist_.data(), size, timeout_);
	if (res == ft::err)
	{
		if (errno == EINTR)//forbidden
			return (epollWait());
		else
			std::cout << "epoll wait failed" << std::endl;
	}
	return (res);
}

void	Epoller::epollLoop(void)
{
	while (true)
	{
		int res = 0;
		while (res == 0)
			res = epollWait();
		const_iterator	it = res_evlist_.begin();
		const_iterator	end = res_evlist_.end();

		while (it != end)
		{
			uint32_t	ev = it->events;
			ASocket		*socket = static_cast<ASocket*>(it->data.ptr);
			// if (socket->getSocketType() == true)//* refactor
			if (socket->getSocketType() == ASocket::listening)
			{
				ASocket *new_socket = new ClientSocket(socket->getFd());
				epollAdd(new_socket);
				std::cout << "accept" << std::endl;
			}
			else if (ev & EPOLLIN)
			{
				std::cout << "EPOLLIN" << std::endl;
				// socket->recv();
				continue ;
			}
			else
			{
				//todo error
			}
			if (ev & (EPOLLRDHUP | EPOLLHUP))
			{
				// break ;
				std::cout << "HUP" << std::endl;
				socket->markSocketDelete();
				// epollClose(*socket);
			}
			it++;
			SocketHolder_.deleteMarkedSocket();
		}
	}
}
