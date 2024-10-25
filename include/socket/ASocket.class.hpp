/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:36:55 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/25 08:25:03 by mogawa           ###   ########.fr       */
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
		RECVCHUNK,
		READ,
		SEND,
		WRITE,
		IDLE,
	};
	typedef struct sockaddr_s
	{
		struct sockaddr_in	addr;
		socklen_t			addrlen;
		
	}	sockaddr_t;
private:
	SocType						type_;
	ft::unique_ptr<ARequest>	request_;
protected:
	int				fd_;//todo const
	sockaddr_t		addr_;
	explicit ASocket(SocType type);
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
