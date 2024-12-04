/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHolder.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:38:55 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/04 08:41:34 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <string>
#include <sys/epoll.h>

class ASocket;

class SocketHolder
{
public://*typedef
	typedef std::vector<ASocket*>		vec_socket;
	typedef	vec_socket::const_iterator	const_iterator;
	typedef vec_socket::iterator		iterator;
	typedef vec_socket::size_type		size_type;
	typedef vec_socket::difference_type	difference_type;
private:
	vec_socket	vec_sockets_;
	SocketHolder(SocketHolder const &rhs);
	SocketHolder &operator=(SocketHolder const &rhs);
public:
	SocketHolder();
	~SocketHolder();

	void		add(ASocket *socket);
	void		cleanUpSockets(void);
	int			getSize(void) const;
};
