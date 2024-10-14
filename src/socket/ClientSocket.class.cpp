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
#include "RequestFactory.hpp"
#include "Response.hpp"
#include "HttpException.hpp"
#include "AResponseException.hpp"
#include "IO.class.hpp"
#include <unistd.h>

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
		throw(SocketException("accept failed at ClientSocket.class.cpp at 44."));
	}
	ft::Fcntl::setNonBlock(fd);
	return (fd);
}

void	ClientSocket::setSockaddr(void)
{
	//todo
}

#include <iostream>
void	ClientSocket::recv_handler(config::ConfigFactory const &config_factory)
{
	try
	{
		ft::unique_ptr<ARequest>request_(RequestFactory::createRequest(fd_, config_factory));
		Response res = request_->generateResponse();
		io::IO sender(fd_);
		sender.send(res.to_string());
		std::cerr << "Good Request" << std::endl;//todo
	}
	catch(HttpException const &e)
	{
		std::cerr << e.what() << std::endl;//todo
		Response res = e.generateResponse();
		io::IO sender(fd_);
		sender.send(res.to_string());
	}
	catch(AResponseException const &request)
	{
		Response r = request.generateResponse();
		io::IO sender(fd_);
		sender.send(r.to_string());
		std::cerr << "Auto index or redirect " << std::endl;//todo
	}
	catch(std::runtime_error const &e)
	{
		std::cerr << e.what() << std::endl;//todo
	}	
	set_time();
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
