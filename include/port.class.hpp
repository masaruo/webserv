/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:47:26 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/23 12:02:35 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Port
{
private:
	int                         port_;
	int							fd_;
	struct sockaddr_in const	addr_;
	// hidden
	Port();
	Port(Port const &rhs);
	Port &operator=(Port const &rhs);
public:
	Port(int port);
	~Port();
	void    closePort(void) const;
	int     getFd(void) const;
	//todo exceptions
};
