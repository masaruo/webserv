/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoller.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:24:00 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/24 15:28:14 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "epoller.class.hpp"
#include "unique_ptr.hpp"
#include "define.hpp"
#include <unistd.h>// close()
#include <cerrno>//todo delete
#include <iostream>

Epoller::Epoller(int size, int timeout)
:epfd_(epoll_create(size))
,evlist_(epoll_vector())
,maxevents_(0)
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
	if (epfd_ != 0)
	{
		close (epfd_);
	}
	return ;
}

#include <utility>
void	Epoller::epollAdd(Socket const &socket)
{
	sockets_.push_back(socket);
	epoll_event	ev;
	ev.events = EPOLLIN | EPOLLRDHUP | EPOLLHUP;
	ev.data.ptr = &sockets_.back();
	int	res = 0;
	res = epoll_ctl(epfd_, EPOLL_CTL_ADD, sockets_.back().getFd(), &ev);
	if (res == ft::err)
	{
		std::cout << "epolladd" << std::endl;
		sockets_.pop_back();
		//todo error
		//todo delete sockets
	}
	else
	{
		std::cout << "max + 1" << std::endl;
		maxevents_++;
	}
}

void	Epoller::epollClose(Socket &socket)
{
	int res = 0;
	// res = epoll_ctl(epfd_, EPOLL_CTL_DEL, socket.getFd(), socket.getEpollEv());
	if (res == ft::err)
	{
		//todo error
	}
	std::cout << "epoll close" << std::endl;
	// maxevents_--;
}

int	Epoller::epollWait(void)
{
	int	res = 0;
	evlist_.resize(sockets_.size());
	res = epoll_wait(epfd_, evlist_.data(), sockets_.size(), timeout_);
	// res = epoll_wait(epfd_, evlist, maxevents_, timeout_);
	if (res == ft::err)
	{
		if (errno == EINTR)
			return (epollWait());
		else
			std::cout << "epoll wait failed" << std::endl;
	}
	return (res);
}

void	Epoller::epollLoop(void)
{
	// int	nfds = epollWait();

	while (true)
	{
		int res = 0;
		while (res == 0)
			res = epollWait();
		const_iterator	it = evlist_.begin();
		const_iterator	end = evlist_.end();

		while (it != end)
		{
			uint32_t	ev = it->events;
			Socket		*socket = static_cast<Socket*>(it->data.ptr);
			if (socket->getSocketType() == true)//* refactor
			{
				std::cout << "accept" << std::endl;
				Socket	client = socket->accept();
				client.makeNoListening();
				epollAdd(client);
				std::cout << "accept 2" << std::endl;
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
				// epollClose(*socket);
			}
			it++;
		}
	}
}
