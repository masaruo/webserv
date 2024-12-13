/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 04:15:11 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/13 23:11:55 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ASocket.hpp"
#include "ListenSocket.hpp"
#include "AResponseException.hpp"
#include "Response.hpp"
#include "ClientSocket.hpp"
#include "CgiSocket.hpp"
#include "define.hpp"
#include <sys/epoll.h>
#include <unistd.h>
#include <signal.h>

volatile	sig_atomic_t	g_server_running = true;

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
	int	ev_num = epoll_wait(epollFd_, eventQueue_.data(), size, 0);
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
	ev.events = event | EPOLLRDHUP;
	ev.data.ptr = socket;

	int	res = epoll_ctl(epollFd_, EPOLL_CTL_ADD, socket->getFd(), &ev);
	if (res == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	holder_.add(socket);
}

void	Server::mod(ASocket *socket, uint32_t event)
{
	epoll_event	ev;
	ev.events = event | EPOLLRDHUP;
	ev.data.ptr = socket;

	int	res = epoll_ctl(epollFd_, EPOLL_CTL_MOD, socket->getFd(), &ev);
	if (res == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
}

void	Server::del(ASocket *socket)
{
	int res = epoll_ctl(epollFd_, EPOLL_CTL_DEL, socket->getFd(), NULL);
	if (res == -1)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
}

static void	signal_handler(int signum)
{
	if (signum == SIGINT || signum == SIGTERM)
		g_server_running = false;
}

static void	init_signal_handling_(void)
{
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		throw (std::runtime_error("Signal Setup Failed"));
	if (signal(SIGINT,  signal_handler) == SIG_ERR)
		throw (std::runtime_error("Signal Setup Failed"));
	if (signal(SIGTERM, signal_handler) == SIG_ERR)
		throw (std::runtime_error("Signal Setup Failed"));
}

void	Server::run(void)
{
	init_signal_handling_();
	while (g_server_running == true)
	{
		int	event_num = epollWait();
		for (int i = 0; i < event_num; i++)
		{
			uint32_t	ev = eventQueue_[i].events;
			ASocket		*socket = static_cast<ASocket*>(eventQueue_[i].data.ptr);
			try
			{
				if (socket->isDelete())
					continue ;
				socket->handleEvent(ev);
			}
			catch (AResponseException const &e)
			{
				Response res = e.generateResponse();
				ClientSocket *client = dynamic_cast<ClientSocket*>(socket);
				if (client == NULL)
					continue ;
				client->setData(res.to_string());
				this->mod(socket, EPOLLOUT);
			}
			catch (HttpException const &e)
			{
				Response	res = e.generateResponse();
				if (CgiSocket *cgi = dynamic_cast<CgiSocket*>(socket))
				{
					ClientSocket *parent = cgi->getParentSocket();
					parent->setData(res.to_string());
					this->mod(parent, EPOLLOUT);
					// cgi->setSocketClose();
					continue ;
				}
				else if (ClientSocket *client = dynamic_cast<ClientSocket*>(socket))
				{
					client->setData(res.to_string());
					this->mod(client, EPOLLOUT);
				}
			}
			catch (std::exception const &e)
			{
				std::cerr << "Server.cpp:144" << e.what() << std::endl;
				socket->setSocketClose();
			}
			catch (...)
			{
				std::cerr << "Server.cpp:148 Non Standard Error detected." << std::endl;
				socket->setSocketClose();
			}
		}
		holder_.deleteMarkedSockets(epollFd_);
	}
}
