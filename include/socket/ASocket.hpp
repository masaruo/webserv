/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 06:59:43 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/02 07:06:34 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "define.hpp"
#include "Fd.hpp"
#include "netinet/in.h"

class Server;

class ASocket
{
public:
	struct Addr
	{
		sockaddr_in	addrin_;
		socklen_t	addrlen_;
	};
private:
	int			port_;
	Fd			fd_;
	ft::State	state_;
	uint32_t	events_;
	Addr		addr_;
	Server		&server_;

protected:
	void			setSockAddr(Addr addr);
	Server			&getServer(void);

public:
	explicit	ASocket(int port, int fd, ft::State state, uint32_t event, Server &server);
	explicit	ASocket(int port, int fd, ft::State state, uint32_t event, Server &server, Addr addr);
	virtual		~ASocket();

	int				getPort(void) const;
	int				getFd(void) const;
	void			setState(ft::State state);
	ft::State		getState(void) const;
	void			setEvents(uint32_t events);
	uint32_t		getEvents(void) const;
	Addr			getSockAddr(void) const;

	virtual void	execute(void) = 0;
};
