/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:47:26 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/19 19:02:21 by mogawa           ###   ########.fr       */
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
	int		getPort(void) const;
	//todo exceptions
};
