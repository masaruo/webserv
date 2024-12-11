/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 03:52:05 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/11 00:20:12 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <string>
#include "ConfigFactory.hpp"
#include "SocketHolder.hpp"

class ASocket;

class Server
{
public:
	typedef std::vector<struct epoll_event>	event_vec;

private:
	config::ConfigFactory	config_factory_;
	int						epollFd_;
	event_vec				eventQueue_;
	SocketHolder			holder_;

	int	epollWait(void);

	Server();
	Server(Server const &rhs);
	Server &operator=(Server const &rhs);
public:
	Server(std::string const &config_path);
	~Server();

	config::ConfigFactory const	&getConfigFactory(void) const;
	void						add(ASocket *socket, uint32_t event);
	void						del(ASocket *socket);
	void						mod(ASocket *socket, uint32_t event);
	void						run(void);
};
