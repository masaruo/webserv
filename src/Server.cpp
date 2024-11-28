/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 04:15:11 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/28 05:45:13 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ASocket.hpp"
#include "ListenSocket.hpp"
#include <sys/epoll.h>
#include <unistd.h>

Server::Server(std::string const &config_path)
:config_factory_(config_path)
,epollFd_(-1)
,eventQueue_()
,holder_()
{
	epollFd_ = epoll_create(1);
	if (epollFd_ == -1)
	{
		throw (std::runtime_error("epoll_create failed"));
	}
	std::vector<std::size_t>	ports = config_factory_.getAcceptedPorts();
	std::vector<std::size_t>::const_iterator	it = ports.begin();
	std::vector<std::size_t>::const_iterator	ite = ports.end();
	while (it != ite)
	{
		ASocket	*soc = new ListenSocket(*it, *this);
		// soc->setState(ft::PASSIVE);
		add(soc, EPOLLIN);
		it++;
	}
	return ;
}

Server::~Server()
{
	close (epollFd_);
}

int	Server::epollWait(void)
{
	int	const	size = holder_.getSize();
	eventQueue_.resize(size);
	int	ev_num = epoll_wait(epollFd_, eventQueue_.data(), size, ft::TIMEOUT);//todo timeout
	if (ev_num == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	return (ev_num);
}

config::ConfigFactory const	&Server::getConfigFactory(void) const
{
	return (config_factory_);
}

void	Server::add(ASocket *socket, uint32_t event)
{
	if (holder_.getSize() > ft::MAX_SOCKET_NUM)
		throw (HttpException(HttpCode::SERVICE_UNAVAILABLE));

	epoll_event	ev;
	ev.events = event;
	ev.data.ptr = socket;

	int	res = epoll_ctl(epollFd_, EPOLL_CTL_ADD, socket->getFd(), &ev);
	if (res == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	holder_.addSocket(socket);
}

void	Server::mod(ASocket *socket, uint32_t event)
{
	epoll_event	ev;
	ev.events = event;
	ev.data.ptr = socket;

	int	res = epoll_ctl(epollFd_, EPOLL_CTL_MOD, socket->getFd(), &ev);
	if (res == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
}

void	Server::del(ASocket *socket)
{
	int	res = epoll_ctl(epollFd_, EPOLL_CTL_DEL, socket->getFd(), NULL);
	if (res == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	//todo delete socket from holder
}

void	Server::run(void)
{
	while (true)
	{
		int	event_num = epollWait();
		for (int i = 0; i < event_num; i++)
		{
			uint32_t	ev = eventQueue_[i].events;
			ASocket		*socket = static_cast<ASocket*>(eventQueue_[i].data.ptr);
			socket->handleEvent(ev);
		}
	}


	// while (true)
	// {
	// 	holder_.deleteMarkedSocket();
	// 	int	event_num = epollWait();
	// 	for (int i = 0; i < event_num; i++)
	// 	{
	// 		uint32_t	ev = eventQueue_[i].events;
	// 		ASocket		*socket = static_cast<ASocket*>(eventQueue_[i].data.ptr);
	// 		if (ev & EPOLLERR)
	// 		{
	// 			deleteSocket(socket);
	// 		}
	// 		else if (ev & EPOLLHUP)
	// 		{
	// 			if (socket->getState() == ft::CGI_COMPLETE)
	// 			{
	// 				socket->execute();
	// 			}
	// 			deleteSocket(socket);
	// 		}
	// 		else
	// 		{
	// 			try
	// 			{
	// 				socket->execute();
	// 			}
	// 			catch(const std::exception& e)
	// 			{
	// 				deleteSocket(socket);
	// 				continue ;
	// 			}
	// 		}
	// 	}
	// }
}
