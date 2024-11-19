/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ActiveSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:52:30 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/18 06:22:28 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ActiveSocket.hpp"
#include "Config.hpp"
#include "Server.hpp"
#include "unique_ptr.hpp"
#include "AResponseException.hpp"
#include "HttpException.hpp"
#include "CgiRequest.hpp"
#include "GetRequest.hpp"

ActiveSocket::ActiveSocket(int port, int fd, ft::State state, uint32_t event, Server &server, Addr addr)
:ASocket(port, fd, state, event, server ,addr)
,io_(fd)
,request_(NULL)
{
	return ;
}

ActiveSocket::~ActiveSocket()
{
	delete request_;
}

void	ActiveSocket::setData(std::string const &data)
{
	io_.setData(data);
}

std::string	ActiveSocket::getData(void) const
{
	return (io_.getData());
}

ARequest	*ActiveSocket::generateRequest(Server &server) const
{
	RequestLine const &line = io_.getLine();
	HttpUri const &uri = line.getUri();
	HttpHeader const &header = io_.getHeader();
	HttpBody const &body = io_.getBody();

	if (uri.IsCgi())
	{
		return (new CgiRequest())
	}
}

void	ActiveSocket::execute(void)//todo
{
	ft::State	&state = getRefState();
	bool		parse_completed = false;
	Response	res;

	if (state == ft::RECV_REQUESTLINE || state == ft::RECV_HEADER || state == ft::RECV_BODY)
	{
		parse_completed = io_.recv(state);
		if (!parse_completed)
			return ;
		updateEventsWithState();
	}
	if (state == ft::IDLE)
	{
		request_ = generateRequest(getServer());
	}
	// if (state == ft::RESPONSE_READY)
	// {
		// try
		// {
		// 	ft::unique_ptr<ARequest>request(io_.createRequest(getServer()));
		// 	res = request->generateResponse();
		// }
		// catch(AResponseException const &request)
		// {
		// 	res = request.generateResponse();
		// }
		// catch(HttpException const &exception)
		// {
		// 	res = exception.generateResponse();
		// }
		// state = ft::SEND;
		// updateEventsWithState();
		// io_.setData(res.to_string());
	// }
	if (state == ft::SEND)
	{
		bool is_send_completed = io_.send(state);
		if (is_send_completed)
		{
			state = ft::DELETE;
			updateEventsWithState();
			return ;
		}
	}
}
