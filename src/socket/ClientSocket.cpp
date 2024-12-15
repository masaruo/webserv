/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:52:30 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/15 06:03:41 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"
#include "define.hpp"
#include "Server.hpp"
#include "ARequest.hpp"
#include "Response.hpp"
#include "CgiSocket.hpp"
#include "unique_ptr.hpp"
#include "Response.hpp"

#include <sys/epoll.h>

ClientSocket::ClientSocket(sockaddr_in const &addr, int fd, Server &server)
:ASocket(addr, fd, server)
,factory_(server)
,data_()
,cgi_socket_(NULL)
{
	updateLastActiveTime();
	return ;
}

ClientSocket::~ClientSocket()
{
	if (cgi_socket_)
	{
		cgi_socket_->setSocketClose();
		cgi_socket_ = NULL;
	}
}

void	ClientSocket::setData(std::string const &data)
{
	data_ = data;
}

void	ClientSocket::assertTimeout(void)
{
	time_t	now = time(NULL);
	if (now == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	else if (now > getLastActiveTime() + ft::TIMEOUT)
	{
		updateLastActiveTime();
		throw (HttpException(HttpCode::REQUEST_TIMEOUT));
	}
}

void	ClientSocket::handleEvent(uint32_t event)
{
	if (event == EPOLLIN)
	{
		#ifndef DEBUG
		assertTimeout();
		#endif
		handleRead();
	}
	else if (event == EPOLLOUT)
	{
		updateLastActiveTime();
		handleSend();
	}
	else if (event & (EPOLLERR | EPOLLHUP | EPOLLRDHUP))
	{
		setSocketClose();
	}
	else
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
}

void	ClientSocket::handleRead(void)
{
	std::string buf(ft::READ_BUF_SIZE, '\0');
	ssize_t	bytes = ::recv(getFd(), &buf[0], buf.size(), 0);
	if (bytes == -1)
		throw (HttpException(HttpCode::BAD_REQUEST));
	factory_.parse(buf, bytes);
	if (factory_.isParseCompleted())
	{
		updateLastActiveTime();
		if (factory_.isCgiRequest())
		{
			try
			{
				server_.mod(this, 0);
				CgiSocket	*cgi = new CgiSocket(this, factory_, server_);
				setCgiSocket(cgi);
				cgi->handleCgiExecution();
				server_.add(cgi, EPOLLOUT);
			}
			catch(HttpException const &e)
			{
				std::cerr << "ClientSocket.cpp HttpException catch block: " << e.what() << std::endl;
				throw (HttpException(e.getErrorCode()));
			}
			catch(std::exception const &e)
			{
				std::cerr << "ClientSocket.cpp std::exception catch block: " << e.what() << std::endl;
				throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
			}
		}
		else
		{
			ft::unique_ptr<ARequest>request(factory_.createRequest(server_));
			request->init();
			request->generateResponseData();
			Response res = request->generateResponse();
			data_ = res.to_string();
			server_.mod(this, EPOLLOUT);
		}
	}
}

void	ClientSocket::handleSend(void)
{
	std::size_t	sendSize = std::min(data_.size(), ft::WRITE_BUF_SIZE);
	ssize_t	bytes = ::send(getFd(), data_.c_str(), sendSize, 0);
	if (bytes == 0 || bytes == -1)
	{
		setSocketClose();
		return ;
	}
	data_ = data_.substr(bytes);
	if (data_.empty())
	{
		setSocketClose();
	}
}

void	ClientSocket::setCgiSocket(CgiSocket *cgi)
{
	cgi_socket_ = cgi;
}

time_t	ClientSocket::getLastActiveTime(void) const
{
	return (last_active_time_);
}
