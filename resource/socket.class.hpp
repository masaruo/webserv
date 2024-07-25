/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 07:34:36 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/24 15:09:58 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sys/socket.h>
#include <sys/epoll.h>
#include "string.hpp"

#ifndef BUFSIZE
#define BUFSIZE (1025)
#endif

class Port;

class Socket
{
private:
	int				fd_;

	// todo curve out buffer class
	char			buffer_[BUFSIZE];
	ft::string		bufStr_;
	size_t			length_;


	int				flags_;

	// is listening socket or client socket
	bool			is_listening;

	// client addr info after accept
	struct sockaddr	client_addr_;
	socklen_t		addrlen_;

	// struct epoll_event	ev;
	bool			to_delete;

public:
	Socket();
	Socket(Port const &port);
	Socket(Socket const &rhs);
	Socket &operator=(Socket const &rhs);
	~Socket();
	Socket	accept(void) const;
	ssize_t	recv(void);
	ssize_t	send(void) const;
	int		getFd(void) const;
	bool	getSocketType(void) const;
	bool	getToDelete(void) const;
	void	makeToDelete(void);
	void	makeNoListening(void);

	//todo updateBuf need to be refactored
	void	updateBuf(ft::string out);//? string const &
	//todo EXCEPTION
};
