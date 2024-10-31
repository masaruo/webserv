/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MSocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 00:43:04 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/31 02:46:05 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ISocket.hpp"
#include "unistd.h"

template <typename T>
class MSocket : public ISocket
{
private:
	T	socket_;
	MSocket(MSocket const &rhs);
	MSocket &operator=(MSocket const &rhs);
public:
	MSocket();
	MSocket(T const &socket);
	~MSocket();
};

// #include "MSocket.tpp"

template <typename T>
MSocket<T>::MSocket()
{
	return ;
}

template <typename T>
MSocket<T>::~MSocket()
{
	//todo
}
