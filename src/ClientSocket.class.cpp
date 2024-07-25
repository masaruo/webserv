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
#include "unistd.h"

ClientSocket::ClientSocket(int listen_fd)
{
	fd_ = acceptHandler(listen_fd);
	return ;
}

ClientSocket::~ClientSocket()
{
	close (fd_);
}

int	ClientSocket::acceptHandler(int listen_fd)
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
