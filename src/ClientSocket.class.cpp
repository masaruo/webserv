/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:10:36 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/24 22:33:46 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ClientSocket.class.hpp>
#include "define.hpp"
#include "Fcntl.class.hpp"

ClientSocket::ClientSocket(int listen_fd)
{
	fd_ = acceptHander(listen_fd);
	return ;
}

int	ClientSocket::acceptHander(int listen_fd)
{
	int	fd = 0;

	fd = accept(listen_fd, NULL, NULL);//todo sockaddr_t
	if (fd == ft::err)
	{
		//todo error
	}
	ft::Fcntl::setNonBlock(fd);
	return (fd);
}

void	ClientSocket::setSockaddr(void)
{
	//todo
}
