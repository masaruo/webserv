/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ActiveSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:52:30 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/02 22:56:09 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ActiveSocket.hpp"

int const	ActiveSocket::NO_BODY = 0;
int const	ActiveSocket::LENGTH_BODY = 1;
int const	ActiveSocket::CHUNK_BODY = 2;

ActiveSocket::ActiveSocket(int port, int fd, ft::State state, uint32_t event, Server &server, Addr addr)
:ASocket(port, fd, state, event, server ,addr)
,io_(fd)
{
	return ;
}

ActiveSocket::~ActiveSocket()
{
	return ;
}

int	ActiveSocket::checkHasBody(void) const
{
	if (header_.hasKey("transfer-encoding") && header_.hasKey("content-length"))
		throw (HttpException(HttpCode::BAD_REQUEST));
	else if (header_.hasKey("transfer-encoding") && header_.getLastValue("transfer-encoding") == "chunked")
		return (ActiveSocket::CHUNK_BODY);
	else if (header_.hasKey("content-length") && header_.getContentLen() > 0)
		return (ActiveSocket::LENGTH_BODY);
	else
		return (ActiveSocket::NO_BODY);
}

void	ActiveSocket::execute(void)//todo
{
	// ssize_t		bytes = 0;
	// ft::State	state = getState();

	// bytes = io_.recv(state);

	// if (bytes > 0)
	// 	return;
	// else if (bytes == -1)
	// 	throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

	// if (state == ft::RECV_REQUESTLINE)
	// {
	// 	RequestLine	line(io_.getData());
	// 	line_ = line;
	// 	io_.clear();
	// 	setState(ft::RECV_HEADER);
	// }
	// else if (state == ft::RECV_HEADER)
	// {
	// 	HttpHeader	header(io_.getData());
	// 	header_ = header;
	// 	io_.clear();
	// 	int checkbody = checkHasBody();
	// 	if (checkbody == ActiveSocket::CHUNK_BODY)
	// 		setState(ft::RECV_CHUNKBODY);
	// 	else if (checkbody == ActiveSocket::LENGTH_BODY)
	// 		setState(ft::RECV_LENGTHBODY);
	// 	else
	// 		setState(ft::IDLE);
	// }
	// else if (state == ft::RECV_LENGTHBODY)
	// {
	// 	;
	// }
	// else if (state == ft::RECV_CHUNKBODY)
	// 	;

}
