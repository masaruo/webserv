/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:52:30 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/02 06:27:03 by mogawa           ###   ########.fr       */
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
	return ;
}

ClientSocket::~ClientSocket()
{
	// delete request_;
}

void	ClientSocket::setData(std::string const &data)//todo delete
{
	data_ = data;
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
		// todo chunk
		std::string const &data = data_;
		send(getFd(), data.c_str(), data.size(), 0);
		// server_.del(this);
		to_delete_ = true;
	}
	else
	{
		throw (std::runtime_error("Socket failed"));
	}
}
