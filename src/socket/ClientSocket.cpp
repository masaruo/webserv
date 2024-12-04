/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:52:30 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/04 08:15:22 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"
#include "define.hpp"
#include "Server.hpp"
#include "ARequest.hpp"
#include "Response.hpp"
#include "AResponseException.hpp"
#include "CgiSocket.hpp"

#include <sys/epoll.h>

ClientSocket::ClientSocket(int fd, Server &server)
:ASocket(fd, server)
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

bool	ClientSocket::isObsolete(void) const
{
	time_t	now = time(NULL);
	if (now == -1)
		return (true);
	else if (now > last_active_time_ + ft::TIMEOUT_SEC)
		return (true);
	else
		return (false);
}

void	ClientSocket::handleEvent(uint32_t event)
{
	if (event == EPOLLIN)
	{
		std::string buf(ft::READ_BUF_SIZE, 0);
		ssize_t	bytes = ::recv(getFd(), &buf[0], buf.size(), 0);
		factory_.parse(buf, bytes);
		if (factory_.isParseCompleted())
		{
			try
			{
				if (factory_.isCgiRequest())
				{
					server_.mod(this, 0);
					CgiSocket	*cgi = new CgiSocket(this, factory_, server_);
					cgi->handleCgiExecution();
				}
				else
				{
					ARequest	*request = factory_.createRequest(server_);
					request->generateResponseData();
					Response res = request->generateResponse();
					data_ = res.to_string();
					server_.mod(this, EPOLLOUT);
					delete request;
				}
			}
			catch (AResponseException const &e)
			{
				Response res = e.generateResponse();
				data_ = res.to_string();
				server_.mod(this, EPOLLOUT);
			}
			catch (HttpException const &e)
			{
				Response res = e.generateResponse();
				data_ = res.to_string();
				server_.mod(this, EPOLLOUT);
			}
		}
	}
	else if (event == EPOLLOUT)
	{
		std::size_t	sendSize = std::min(data_.size(), ft::WRITE_BUF_SIZE);
		try
		{
			ssize_t	bytes = ::send(getFd(), data_.c_str(), sendSize, 0);
			if (bytes == -1)
			{
				to_delete_ = true;
				throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
			}
			data_ = data_.substr(bytes);
			if (data_.empty())
			{
				to_delete_ = true;
				// server_.mod(this, 0);
			}
		}
		catch (std::exception const &e)
		{
			to_delete_ = true;
			throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
		}
		to_delete_ = true;
	}
	else
	{
		throw (std::runtime_error("Socket failed"));//? where to pick up exception?
	}
}
