/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoller.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:24:00 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/28 13:43:58 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "epoller.class.hpp"
#include "SocketHolder.class.hpp"
#include "ASocket.class.hpp"
#include "ClientSocket.class.hpp"
#include "define.hpp"
#include <sys/epoll.h>
#include <unistd.h>
// #include <iostream>

Epoller::Epoller(int size, int timeout)
:epfd_(epoll_create(size))
,timeout_(timeout)
{
	if (epfd_ == ft::err)
	{
		throw(EpollerException("epoll class initialization failed at 28."));
	}
	return ;
}

Epoller::~Epoller()
{
	if (epfd_ != ft::err)
		close (epfd_);
}

void	Epoller::epollAdd(ASocket *socket)
{
	epoll_event	ev;
	// ev.events = EPOLLIN | EPOLLRDHUP | EPOLLHUP | EPOLLET;//!
	ev.events = EPOLLIN | EPOLLRDHUP | EPOLLHUP | EPOLLERR | EPOLLOUT;
	ev.data.ptr = socket;
	int	res = 0;
	res = epoll_ctl(epfd_, EPOLL_CTL_ADD, socket->getFd(), &ev);
	if (res == ft::err)
	{
		throw (EpollerException("epoll add failed at 49."));
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
		throw (EpollerException("epoll close failed at 61."));
	}
	socket->markSocketDelete();
}

#include <cerrno>
int	Epoller::epollWait(void)
{
	int	size = SocketHolder_.getSize();
	res_evlist_.resize(size);
	int	numEvents = 0;
	numEvents = epoll_wait(epfd_, res_evlist_.data(), size, timeout_);
	if (numEvents == ft::err)
	{
		//? if (errno == EINTR)//forbidden
		throw (EpollerException("epoll wait failed at 79."));
	}
	SocketHolder_.checkTimeout();
	SocketHolder_.deleteMarkedSocket();
	return (numEvents);
}

void	Epoller::epollLoop(void)
{
	while (true)
	{
		int numEvents = 0;
		while (numEvents == 0)
			numEvents = epollWait();

		const_iterator	it = res_evlist_.begin();
		const_iterator	end = res_evlist_.begin();
		std::advance(end, numEvents);

		while (it != end)
		{
			uint32_t	ev = it->events;
			ASocket		*socket = static_cast<ASocket*>(it->data.ptr);
			if (socket->getSocketType() == ASocket::listening)
			{
				ASocket *new_socket = new ClientSocket(socket->getFd());
				epollAdd(new_socket);
			}
			else if (ev & EPOLLIN)
			{
				ClientSocket *client;
				client = dynamic_cast<ClientSocket*>(socket);
				if (client == NULL)
				{
					throw (EpollerException("epoll to get client socket failed at 111."));
				}
				client->recv_handler();
				epollClose(socket);
			}
			else
			{
				throw (EpollerException("epoll with unknown error at 118."));
			}
			if (ev & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
			{
				epollClose(socket);
			}
			it++;
		}
		SocketHolder_.deleteMarkedSocket();
	}
}

//exception
Epoller::EpollerException::EpollerException(std::string const &msg)
:std::runtime_error(msg)
{
	return ;
}
