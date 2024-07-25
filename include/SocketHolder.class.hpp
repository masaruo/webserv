/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHolder.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:38:55 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/24 23:47:49 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ASocket.class.hpp"
#include <vector>

class ClientSocket;
class ListenSocket;

class SocketHolder
{
public://*typedef
	typedef std::vector<ASocket*>		vec_socket;
	typedef	vec_socket::const_iterator	const_iterator;
	typedef vec_socket::iterator		iterator;
	typedef vec_socket::size_type		size_type;
	typedef vec_socket::difference_type	difference_type;
private:
	vec_socket	vec_;
	// void	clearSockets(void);
	// void	deleteSockets(void);
	SocketHolder(SocketHolder const &rhs);
	SocketHolder &operator=(SocketHolder const &rhs);
public:
	SocketHolder();
	~SocketHolder();
	void	addSocket(ClientSocket *socket);
	void	addSocket(ListenSocket *socket);
	void	markSocketDelete(iterator iter);
	void	clearSocketVec(void);
	template <typename F>
	void	foreach(F func);
};
