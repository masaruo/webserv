/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 06:59:43 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/04 08:06:42 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "define.hpp"
#include <netinet/in.h>

class Server;

class ASocket
{
private:
	ASocket(ASocket const &rhs);
	ASocket &operator=(ASocket const &rhs);
	sockaddr_in	addr_;
protected:
	int			fd_;
	Server		&server_;
	time_t		last_active_time_;
	bool		to_delete_;
	void		setFd(int fd);
	void		setAddr(sockaddr_in const &addr);
	void		setSocketAsClose(void);
public:
	explicit	ASocket(int fd, Server &server);
	virtual		~ASocket();

	sockaddr_in const &getAddr(void) const;
	int				getFd(void) const;
	bool			toDelete(void) const;
	void			updateLastActiveTime(void);
	void			markSocketDelete(void);
	virtual bool	isObsolete(void) const = 0;
	virtual void	handleEvent(uint32_t event) = 0;
};
