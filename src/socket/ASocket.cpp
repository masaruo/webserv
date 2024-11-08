/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:24:44 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/08 06:37:42 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASocket.hpp"
#include "Server.hpp"

ASocket::ASocket(int port, int fd, ft::State state, uint32_t event, Server &server)
:port_(port)
,fd_(fd)
,state_(state)
,events_(event)
,addr_()
,server_(server)
{
	return ;
}

ASocket::ASocket(int port, int fd, ft::State state, uint32_t event, Server &server, Addr addr)
:port_(port)
,fd_(fd)
,state_(state)
,events_(event)
,addr_(addr)
,server_(server)
{
	return ;
}

ASocket::~ASocket()
{
	fd_.close();
	return ;
}

void	ASocket::updateEventsWithState(void)
{
	switch (state_)
	{
	case (ft::RECV_REQUESTLINE):
	case (ft::RECV_HEADER):
	case (ft::RECV_BODY):
	case (ft::CGIRECV):
	case (ft::PASSIVE):
		events_ = EPOLLIN;
		break;
	case (ft::SEND):
	case (ft::CGISEND):
		events_ = EPOLLOUT;
		break;
	case (ft::IDLE):
	case (ft::DELETE):
		events_ = 0;
		break ;
	default:
		break;
	}
	server_.modSocket(this, events_);
}

void	ASocket::setSockAddr(Addr addr)
{
	addr_ = addr;
}

Server	&ASocket::getServer(void)
{
	return (server_);
}

int	ASocket::getPort(void) const
{
	return (port_);
}

int	ASocket::getFd(void) const
{
	return (fd_.getFd());
}

void	ASocket::setState(ft::State state)
{
	state_ = state;
}

ft::State	&ASocket::getRefState(void)
{
	return (state_);
}

ft::State	ASocket::getState(void) const
{
	return (state_);
}

uint32_t	ASocket::getEvents(void) const
{
	return (events_);
}

ASocket::Addr	ASocket::getSockAddr(void) const
{
	return (addr_);
}
