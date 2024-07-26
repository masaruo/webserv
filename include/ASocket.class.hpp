/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:36:55 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/26 15:20:21 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>

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
public:
	virtual			~ASocket() = 0;
	virtual void	setSockaddr(void) = 0;
	int				getFd(void) const;
	socket_type_t	getSocketType(void) const;
	void			markSocketDelete(void);
	//todo errors
	class ASocketError : public std::runtime_error
	{
	public:
		char const *what() const throw();
	};
};
