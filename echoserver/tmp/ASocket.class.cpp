/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:37:44 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/30 04:58:11 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASocket.class.hpp"

ASocket::ASocket(SocType type)
:type_(type)
{
	return ;
}

ASocket::ASocket(SocType type, int fd)
:type_(type)
,fd_(fd)
{
	return ;
}

ASocket::~ASocket()
{
	//todo check close fd or now?!
	return ;
}

int	ASocket::getFd(void) const
{
	return (fd_);
}

void	ASocket::setSocketType(ASocket::SocType type)
{
	type_ = type;
}

ASocket::SocType	ASocket::getSocketType(void) const
{
	return (type_);
}

void	ASocket::markSocketDelete(void)
{
	type_ = DELETE;
}

//exception
ASocket::SocketException::SocketException(std::string const &msg)
:std::runtime_error(msg)
{
	return ;
}
