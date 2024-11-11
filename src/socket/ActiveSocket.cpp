/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ActiveSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:52:30 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/11 01:12:08 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ActiveSocket.hpp"
#include "Config.hpp"
#include "Server.hpp"
#include "unique_ptr.hpp"
#include "AResponseException.hpp"
#include "HttpException.hpp"

ActiveSocket::ActiveSocket(int port, int fd, ft::State state, uint32_t event, Server &server, Addr addr)
:ASocket(port, fd, state, event, server ,addr)
,io_(fd, server.getConfigFactory())
{
	return ;
}

ActiveSocket::~ActiveSocket()
{
	return ;
}

void	ActiveSocket::setData(std::string const &data)
{
	io_.setData(data);
}

std::string	ActiveSocket::getData(void) const
{
	return (io_.getData());
}

void	ActiveSocket::execute(void)//todo
{
	ft::State	&state = getRefState();
	bool		parse_completed = false;
	Response	res;

	// updateEventsWithState();

	if (state == ft::CGISEND)
	{
		std::cerr << "CGISEND activated" << std::endl;
		if (io_.send(state))
		{
			shutdown(this->getFd(), SHUT_WR);
			state = ft::CGIRECV;
			io_.clear();
			updateEventsWithState();
		}
		return ;
	}
	if (state == ft::CGIRECV)
	{
		std::cerr << "CGIRECV activated" << std::endl;
		if (io_.recv_cgi())
		{
			state = ft::IDLE;
			updateEventsWithState();
		}
		return ;
	}
	if (state == ft::RECV_REQUESTLINE || state == ft::RECV_HEADER || state == ft::RECV_BODY)
	{
		parse_completed = io_.recv(state);
		if (!parse_completed)
			return ;
		updateEventsWithState();
	}
	if (state == ft::IDLE)
	{
		try
		{
			ft::unique_ptr<ARequest>request(io_.createRequest(getServer()));
			res = request->generateResponse();
		}
		catch(AResponseException const &request)
		{
			res = request.generateResponse();
		}
		catch(HttpException const &exception)
		{
			res = exception.generateResponse();
		}
		state = ft::SEND;
		updateEventsWithState();
		io_.setData(res.to_string());
	}
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
