/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 06:59:43 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/12 05:32:26 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "define.hpp"
#include "Fd.hpp"
#include <netinet/in.h>

class Server;

class ASocket
{
private:
	sockaddr_in		addr_;
	Fd				fd_;
	mutable bool	to_delete_;
protected:
	time_t		last_active_time_;
	Server		&server_;
	void		setFd(int fd);
	void		setAddr(sockaddr_in const &addr);
public:
	explicit	ASocket(int fd, Server &server);
	explicit	ASocket(sockaddr_in const &addr, int fd, Server &server);
	virtual		~ASocket();

	virtual time_t		getLastActiveTime(void) const = 0;
	void				setSocketClose(void) const;
	sockaddr_in const	&getAddr(void) const;
	int					getFd(void) const;
	bool				isDelete(void) const;
	void				updateLastActiveTime(void);
	virtual	void		assertTimeout(void) = 0;
	virtual void		handleEvent(uint32_t event) = 0;
private:
	ASocket(ASocket const &rhs);
	ASocket &operator=(ASocket const &rhs);
};
