/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:36:55 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/30 08:42:23 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include "ARequest.hpp"
#include "unique_ptr.hpp"

class ASocket
{
public:
	enum SocType
	{
		LISTEN,
		ACCEPTED,
		DELETE,
		RECV,
		RECVBODY,
		SEND,
		CGISEND,
		CGIRECV,
		IDLE,
	};
	typedef struct sockaddr_s
	{
		struct sockaddr_in	addr;
		socklen_t			addrlen;
		
	}	sockaddr_t;
private:
	SocType						type_;
protected:
	int				fd_;//todo const
	sockaddr_t		addr_;
	explicit ASocket(SocType type);
	explicit ASocket(SocType type, int fd);
public:
	virtual			~ASocket() = 0;
	virtual void	setSockaddr(void) = 0;
	int				getFd(void) const;
	void			setSocketType(SocType type);
	SocType			getSocketType(void) const;
	void			markSocketDelete(void);

	class SocketException : public std::runtime_error
	{
	public:
		SocketException(std::string const &msg);
	};
};
