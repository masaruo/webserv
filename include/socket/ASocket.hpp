/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 06:59:43 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/29 09:55:20 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "define.hpp"
#include <netinet/in.h>

class Server;

class ASocket
{
private:
	sockaddr_in	addr_;
	ASocket(ASocket const &rhs);
	ASocket &operator=(ASocket const &rhs);
protected:
	int			fd_;
	Server		&server_;
	bool		to_delete_;
public:
	explicit	ASocket(int fd, Server &server);
	virtual		~ASocket();

	int				getFd(void) const;
	bool			toDelete(void) const;
	virtual void	handleEvent(uint32_t event) = 0;
};
