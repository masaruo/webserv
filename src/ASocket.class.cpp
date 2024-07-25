/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:37:44 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/24 23:20:13 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASocket.class.hpp"

ASocket::~ASocket()
{
	return ;
}

int	ASocket::getFd(void) const
{
	return (fd_);
}

ASocket::socket_type_t	ASocket::getSocketType(void) const
{
	return (type_);
}

void	ASocket::markSocketDelete(void)
{
	type_ = to_delete;
}
