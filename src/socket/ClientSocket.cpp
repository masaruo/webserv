/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:52:30 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/06 02:52:14 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"
#include "define.hpp"
#include "Server.hpp"
#include "ARequest.hpp"
#include "Response.hpp"
#include "CgiSocket.hpp"

#include <sys/epoll.h>

ClientSocket::ClientSocket(sockaddr_in const &addr, int fd, Server &server)
:ASocket(addr, fd, server)
{
	updateLastActiveTime();
	return ;
}

ClientSocket::~ClientSocket()
{
	return ;
}

void	ClientSocket::setData(std::string const &data)//todo delete
{
	data_ = data;
}

void	ClientSocket::assertTimeout(void) const
{
	time_t	now = time(NULL);

	if (now == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	else if (now > getLastActiveTime() + ft::TIMEOUT_SEC)
	{
		throw (HttpException(HttpCode::REQUEST_TIMEOUT));
	}
	else
		return ;
}

void	ClientSocket::handleEvent(uint32_t event)
{
	#ifndef DEBUG
	assertTimeout();
	#endif

	if (event == EPOLLIN)
		handleRead();
	else if (event == EPOLLOUT)
		handleSend();
	else
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

	// try
	// {
	// 	if (event == EPOLLIN)
	// 		handleRead();
	// 	else if (event == EPOLLOUT)
	// 		handleSend();
	// 	else
	// 		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

	// }
	// catch(AResponseException const &e)
	// {
	// 	Response res = e.generateResponse();
	// 	data_ = res.to_string();
	// 	server_.mod(this, EPOLLOUT);
	// }
	// catch (HttpException const &e)
	// {
	// 	Response res = e.generateResponse();
	// 	data_ = res.to_string();
	// 	server_.mod(this, EPOLLOUT);	
	// }
	// catch (std::exception const &e)
	// {
	// 	std::cerr << e.what() << std::endl;
	// }

	// if (event == EPOLLIN)
	// {
	// 	std::string buf(ft::READ_BUF_SIZE, 0);
	// 	ssize_t	bytes = ::recv(getFd(), &buf[0], buf.size(), 0);
	// 	factory_.parse(buf, bytes);
	// 	if (factory_.isParseCompleted())
	// 	{
	// 		try
	// 		{
	// 			updateLastActiveTime();
	// 			if (factory_.isCgiRequest())
	// 			{
	// 				server_.mod(this, 0);
	// 				CgiSocket	*cgi = new CgiSocket(this, factory_, server_);
	// 				cgi->handleCgiExecution();
	// 			}
	// 			else
	// 			{
	// 				ARequest	*request = factory_.createRequest(server_);
	// 				request->generateResponseData();
	// 				Response res = request->generateResponse();
	// 				data_ = res.to_string();
	// 				server_.mod(this, EPOLLOUT);
	// 				delete request;
	// 			}
	// 		}
	// 		catch (AResponseException const &e)
	// 		{
	// 			Response res = e.generateResponse();
	// 			data_ = res.to_string();
	// 			server_.mod(this, EPOLLOUT);
	// 		}
	// 		catch (HttpException const &e)
	// 		{
	// 			Response res = e.generateResponse();
	// 			data_ = res.to_string();
	// 			server_.mod(this, EPOLLOUT);
	// 		}
	// 	}
	// }
	// else if (event == EPOLLOUT)
	// {
	// 	std::size_t	sendSize = std::min(data_.size(), ft::WRITE_BUF_SIZE);
	// 	try
	// 	{
	// 		ssize_t	bytes = ::send(getFd(), data_.c_str(), sendSize, 0);
	// 		if (bytes == -1)
	// 		{
	// 			setSocketClose();
	// 			throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));//todo this error will not be caught.
	// 		}
	// 		data_ = data_.substr(bytes);
	// 		if (data_.empty())
	// 		{
	// 			setSocketClose();
	// 		}
	// 	}
	// 	catch (std::exception const &e)
	// 	{
	// 		setSocketClose();
	// 		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	// 	}
	// }
	// else
	// {
	// 	throw (std::runtime_error("Socket failed"));//? where to pick up exception?
	// }
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
			server_.mod(this, 0);
			CgiSocket	*cgi = new CgiSocket(this, factory_, server_);
			cgi->handleCgiExecution();
			server_.add(cgi, EPOLLOUT);
		}
		else
		{
			ARequest	*request = factory_.createRequest(server_);
			request->init();
			request->generateResponseData();
			Response res = request->generateResponse();
			data_ = res.to_string();
			server_.mod(this, EPOLLOUT);
			delete request;
		}
	}
}

void	ClientSocket::handleSend(void)
{
	std::size_t	sendSize = std::min(data_.size(), ft::WRITE_BUF_SIZE);
	ssize_t	bytes = ::send(getFd(), data_.c_str(), sendSize, 0);
	if (bytes == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	data_ = data_.substr(bytes);
	if (data_.empty())
	{
		setSocketClose();
	}
}
