/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 06:59:43 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/28 04:54:08 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "define.hpp"
#include <netinet/in.h>

class Server;

class ASocket
{
private:
	int			fd_;
	sockaddr_in	addr_;
	// IO			io_;

	ASocket(ASocket const &rhs);
	ASocket &operator=(ASocket const &rhs);
protected:
	Server		&server_;

public:
	explicit	ASocket(int fd, Server &server);
	virtual		~ASocket();

	int				getFd(void) const;
	virtual void	handleEvent(uint32_t event) = 0;
};
