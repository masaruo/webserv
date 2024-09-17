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
,last_activity_(std::time(NULL))
,timeout_(1000)// config
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
	// std::string	raw_data = ConnectionHandler::recvData(fd_, 800000);
	ft::unique_ptr<ARequest>req_tmp(RequestFactory::createRequest(fd_));
	request_ = req_tmp;//todo how to directly copy unique_ptr
	ft::unique_ptr<AResponse>res(request_->createResponse());
	res->generateResponse();
	ConnectionHandler::sendData(fd_, res->getResponse());
	set_time();
	return (0);
}

ssize_t	ClientSocket::send_hander(void) const
{
	std::cout << "send hander" << std::endl;
	return (0);
}

void	ClientSocket::set_time(void)
{
	std::time_t	now = std::time(NULL);
	last_activity_ = now;
}

std::time_t	ClientSocket::get_time(void) const
{
	return (last_activity_);
}

void	ClientSocket::check_timeouts(void)
{
	std::time_t	now = std::time(NULL);
	if (now - last_activity_ > timeout_)
	{
		this->markSocketDelete();
	}
}
