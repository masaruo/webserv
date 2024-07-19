/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 07:34:36 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/19 10:21:25 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sys/socket.h>
#include "string.hpp"

#ifndef BUFSIZE
#define BUFSIZE (1025)
#endif

#define END_OF_FILE (0)//todo move to int const
#define ERR (-1)

class Port;

class Socket
{
private:
	Port const		&port_;
	int				accepted_fd_;
	char			buffer_[BUFSIZE];
	ft::string		bufStr_;
	size_t			length_;
	int				flags_;
	struct sockaddr	client_addr_;
	socklen_t		addrlen_;
	int	accept(int sockfd, struct sockaddr *addr_, socklen_t *addrlen_);
	//hidden
	Socket();
	Socket(Socket const &rhs);
	Socket  &operator=(Socket const &rhs);
public:
	Socket(Port const &port);
	~Socket();
	ssize_t	recv(void);
	ssize_t	send(void) const;
	//todo updateBuf need to be refactored
	void	updateBuf(ft::string out);//? string const &
	//todo EXCEPTION
};
