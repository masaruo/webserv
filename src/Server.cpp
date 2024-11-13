/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 04:15:11 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/12 04:11:53 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ASocket.hpp"
#include "ActiveSocket.hpp"
#include "PassiveSocket.hpp"
#include <sys/epoll.h>
#include "unistd.h"

Server::Server(std::string const &config_path)
:config_factory_(config_path)
,epollFd_(epoll_create(1))
,polls_()
,holder_()
{
	std::vector<std::size_t>	ports = config_factory_.getAcceptedPorts();
	std::vector<std::size_t>::const_iterator it = ports.begin();
	std::vector<std::size_t>::const_iterator end = ports.end();
	while (it != end)
	{
		ASocket	*soc = new PassiveSocket(*it, *this);
		// soc->setState(ft::PASSIVE);
		addSocket(soc);
		it++;
	}
	return ;
}

Server::~Server()
{
	if (epollFd_ > 2)
		close (epollFd_);
	return ;
}

int	Server::epollWait(void)
{
	int	const	size = holder_.getSize();
	polls_.resize(size);
	int	ev_num = epoll_wait(epollFd_, polls_.data(), size, ft::TIMEOUT);//todo timeout?
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

void	Server::addSocket(ASocket *socket)
{
	if (holder_.getSize() > ft::MAX_SOCKET_NUM)
		throw (HttpException(HttpCode::SERVICE_UNAVAILABLE));

	epoll_event	ev;
	ev.events = socket->getEvents();
	ev.data.ptr = socket;

	int	res = epoll_ctl(epollFd_, EPOLL_CTL_ADD, socket->getFd(), &ev);
	if (res == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	holder_.addSocket(socket);
}

void	Server::modSocket(ASocket *socket, uint32_t event)
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

void	Server::deleteSocket(ASocket *socket)
{
	int	res = epoll_ctl(epollFd_, EPOLL_CTL_DEL, socket->getFd(), NULL);
	if (res == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	socket->setState(ft::DELETE);
}

void	Server::run(void)
{
	while (true)
	{
		holder_.deleteMarkedSocket();
		int	event_num = epollWait();
		for (int i = 0; i < event_num; i++)
		{
			uint32_t	ev = polls_[i].events;
			ASocket		*socket = static_cast<ASocket*>(polls_[i].data.ptr);
			if (ev & EPOLLERR)
			{
				deleteSocket(socket);
			}
			else if (ev & EPOLLHUP)
			{
				if (socket->getState() == ft::CGIEND)
				{
					socket->execute();
				}
				deleteSocket(socket);
			}
			else
			{
				try
				{
					socket->execute();
				}
				catch(const std::exception& e)
				{
					deleteSocket(socket);
					continue ;
				}
			}
		}
	}
}
