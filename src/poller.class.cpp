/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poller.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:32:40 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/19 18:52:41 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "poller.class.hpp"
#include "socket.class.hpp"
#include "port.class.hpp"
#include <iterator>

Poller::Poller()
{
    return ;
}

Poller::~Poller()
{
    return ;
}

// void    Poller::addSocket(Socket &socket)
// {
//     Sockets_.push_back(socket);
//     pollfds_.push_back(socket.getPollfd());
// }

void	Poller::addSocket(Port const &port)
{
	Socket	sock(port);

	Sockets_.push_back(sock);
	pollfds_.push_back(sock.getPollfd());
}

int	Poller::poll(void)
{
	int	res = ::poll(&pollfds_[0], pollfds_.size(), 3000);
	if (res == -1)
	{
		//todo error
	}
	else if (res == 0)
	{
		//todo timeout
	}
	else
	{
		loopSockets();
	}
	return (res);
}

void	Poller::loopSockets(void) const
{
	const_iterator	it = pollfds_.begin();
	const_iterator	end = pollfds_.end();

	while (it != end)
	{
		short	revents = it->revents;
		difference_type idx = std::distance(pollfds_.begin(), it);
		if (revents & POLLIN)
		{
			const_cast<Socket&>(Sockets_.at(idx)).recv();
			// it->recv();
		}
		else if (revents & POLLOUT)
		{
			Sockets_.at(idx).send();
			// it->send();
		}
		else if (revents & POLLHUP)
		{
			Sockets_.at(idx).close();
			// it->close();
		}
		else if (revents & POLLPRI)
		{
			//todo ???
		}
		it++;
	}
}
