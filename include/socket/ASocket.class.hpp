/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:36:55 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/28 10:48:24 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>

class ASocket
{
public:
	typedef enum {listening, accepted, to_delete} socket_type_t;
	typedef struct sockaddr_s
	{
		struct sockaddr_in	addr;
		socklen_t			addrlen;
		
	}	sockaddr_t;
protected:
	int				fd_;//todo const
	socket_type_t	type_;
	sockaddr_t		addr_;
	explicit ASocket(socket_type_t type);
public:
	virtual			~ASocket() = 0;
	virtual void	setSockaddr(void) = 0;
	int				getFd(void) const;
	socket_type_t	getSocketType(void) const;
	void			markSocketDelete(void);
	class SocketException : public std::runtime_error
	{
	public:
		SocketException(std::string const &msg);
	};
};
