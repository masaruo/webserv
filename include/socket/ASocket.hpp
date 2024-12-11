/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 06:59:43 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/11 05:42:45 by mogawa           ###   ########.fr       */
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
	// int				fd_;
	mutable bool	to_delete_;
	time_t			last_active_time_;
protected:
	Server		&server_;
	void		setFd(int fd);
	void		setAddr(sockaddr_in const &addr);
	time_t		getLastActiveTime(void) const;
public:
	explicit	ASocket(int fd, Server &server);
	explicit	ASocket(sockaddr_in const &addr, int fd, Server &server);
	virtual		~ASocket();

	void				setSocketClose(void) const;
	sockaddr_in const	&getAddr(void) const;
	int					getFd(void) const;
	bool				isDelete(void) const;
	void				updateLastActiveTime(void);
	virtual void		assertTimeout(void) = 0;
	virtual void		handleEvent(uint32_t event) = 0;
private:
	ASocket(ASocket const &rhs);
	ASocket &operator=(ASocket const &rhs);
};
