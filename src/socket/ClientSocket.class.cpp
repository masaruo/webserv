/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:10:36 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/28 14:18:54 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.class.hpp"
#include "define.hpp"
#include "Fcntl.class.hpp"
#include "unistd.h"
#include "ConnectionHandler.hpp"
#include "RequestFactory.hpp"
#include "AResponse.hpp"
#include "GetResponse.hpp"

ClientSocket::ClientSocket(int listen_fd)
:ASocket(ASocket::accepted)
,request_()
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

#include <iostream>
ssize_t	ClientSocket::recv_handler(void)//! create request class and return response class?
{
	std::string	raw_data = ConnectionHandler::recvData(fd_, 8000);
	ft::unique_ptr<ARequest>req_tmp(RequestFactory::createRequest(raw_data));
	request_ = req_tmp;
	//request_->createMockResponse(fd_);
	ft::unique_ptr<AResponse>res(request_->createResponse(fd_));
	res->createBody();
	ConnectionHandler::sendData(fd_, res->str());
	return (0);
}

ssize_t	ClientSocket::send_hander(void) const
{
	std::cout << "send hander" << std::endl;
	return (0);
}
