/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MSocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 00:43:04 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/31 06:51:16 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ISocket.hpp"
#include "unistd.h"

template <typename SocketT, typename k>
class MSocket : public ISocket
{
private:
	SocketT	*socket_;
	k		*io_;
	MSocket();
	MSocket(MSocket const &rhs);
	MSocket &operator=(MSocket const &rhs);
public:
	explicit	MSocket(SocketT *socket);
	~MSocket();
	int			getFd(void) const;
	void		close(void);
	// ISocket		*clone(void);
};

// #include "MSocket.tpp"

template <typename SocketT, typename k>
MSocket<SocketT, k>::MSocket(SocketT *socket)
:socket_(socket)
{
	return ;
}

template <typename SocketT, typename k>
MSocket<SocketT, k>::~MSocket()
{
	//todo
}

template <typename SocketT, typename k>
int	MSocket<SocketT, k>::getFd(void) const
{
	return (socket_->getFd());
}

template <typename SocketT, typename k>
void	MSocket<SocketT, k>::close(void)
{
	socket_->close();
}
