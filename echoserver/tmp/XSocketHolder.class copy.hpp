/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHolder.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:38:55 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/02 02:40:12 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <string>

class ASocket;
class Epoller;

class SocketHolder
{
public://*typedef
	typedef std::vector<ASocket*>		vec_socket;
	typedef	vec_socket::const_iterator	const_iterator;
	typedef vec_socket::iterator		iterator;
	typedef vec_socket::size_type		size_type;
	typedef vec_socket::difference_type	difference_type;
private:
	static vec_socket	vec_sockets_;
	static Epoller		*poller_;
	SocketHolder();
	~SocketHolder();
	SocketHolder(SocketHolder const &rhs);
	SocketHolder &operator=(SocketHolder const &rhs);
public:
	static void		init(Epoller *poller);
	static void		destructor(void);

	static void		addSocket(ASocket *socket);
	// void		checkTimeout(void);
	static void		markSocketDelete(ASocket *socket);
	static void		deleteMarkedSocket(void);
	static int		getSize(void);
};
