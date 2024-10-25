/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoller.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:24:00 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/25 08:33:26 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "epoller.class.hpp"
#include "SocketHolder.class.hpp"
#include "ASocket.class.hpp"
#include "ClientSocket.class.hpp"
#include "define.hpp"

#include "unique_ptr.hpp"
#include "Response.hpp"
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"
#include "RequestFactory.hpp"

#include <sys/epoll.h>
#include <unistd.h>

Epoller::Epoller(int size, std::string const &config_path)
:epfd_(epoll_create(size))
,config_factory_(config_path)
{
	if (epfd_ == ft::err)
	{
		throw(EpollerException("epoll class initialization failed at 28."));
	}
	return ;
}

Epoller::Epoller(int size, int flag)
:epfd_(epoll_create(size))
,config_factory_(flag)
{
	if (epfd_ == ft::err)
	{
		throw(EpollerException("epoll class initialization failed at 28."));
	}
	return ;
}

Epoller::~Epoller()
{
	if (epfd_ != ft::err)
		close (epfd_);
}

void	Epoller::epollAdd(ASocket *socket)
{
	epoll_event	ev;
	// ev.events = EPOLLIN | EPOLLRDHUP | EPOLLHUP | EPOLLET;//!
	ev.events = EPOLLIN | EPOLLRDHUP | EPOLLHUP | EPOLLERR | EPOLLOUT;
	ev.data.ptr = socket;
	int	res = 0;
	res = epoll_ctl(epfd_, EPOLL_CTL_ADD, socket->getFd(), &ev);
	if (res == ft::err)
	{
		throw (EpollerException("epoll add failed at 49."));
	}
	// SocketHolder_.addSocket(socket);//todo try catch
	SocketHolder::addSocket(socket);
	return ;
}

void	Epoller::epollClose(ASocket *socket)
{
	int res = 0;
	res = epoll_ctl(epfd_, EPOLL_CTL_DEL, socket->getFd(), NULL);
	if (res == ft::err)
	{
		throw (EpollerException("epoll close failed at 61."));
	}
	socket->markSocketDelete();
}

#include <cerrno>
int	Epoller::epollWait(void)
{
	int size = SocketHolder::getSize();
	// int	size = SocketHolder_.getSize();
	event_list_.resize(size);
	int	numEvents = 0;
	numEvents = epoll_wait(epfd_, event_list_.data(), size, ft::TIMEOUT);
	if (numEvents == ft::err)
	{
		//? if (errno == EINTR)//forbidden
		throw (EpollerException("epoll wait failed at 79."));
	}
	// SocketHolder_.checkTimeout();
	// SocketHolder_.deleteMarkedSocket();
	SocketHolder::deleteMarkedSocket();
	return (numEvents);
}

void	Epoller::epollLoop(void)
{
	while (true)
	{
		int numEvents = 0;
		while (numEvents == 0)
			numEvents = epollWait();

		const_iterator	it = event_list_.begin();
		const_iterator	end = event_list_.begin();
		std::advance(end, numEvents);

		while (it != end)
		{
			uint32_t			ev = it->events;
			ASocket				*socket = static_cast<ASocket*>(it->data.ptr);
			ASocket::SocType	type = socket->getSocketType();
			if (type == ASocket::IDLE)
				continue ;
			if (ev & EPOLLIN && type == ASocket::LISTEN)
			{
				ASocket *new_socket = new ClientSocket(socket->getFd());
				new_socket->setSocketType(ASocket::RECV);
				epollAdd(new_socket);
			}
			else if (ev & (EPOLLIN | EPOLLOUT))
			{
				int fd = socket->getFd();
				ClientSocket *client;
				client = dynamic_cast<ClientSocket*>(socket);
				if (client == NULL)
					throw (EpollerException("epoll to get client socket failed at 111."));
				if (ev & EPOLLIN)
				{
					if (type == ASocket::RECV)
					{
						RequestLine line;
						HttpHeader header;
						RequestFactory::createRequestLineAndHeader(fd, line, header);
						int flg = RequestFactory::hasBody(header);
						if (flg == RequestFactory::HASCHUNK)
							socket->setSocketType(ASocket::RECVCHUNK);
						else if (flg == RequestFactory::HASBODY)
							socket->setSocketType(ASocket::RECVBODY);
						else
							socket->setSocketType(ASocket::IDLE);
						// ft::unique_ptr<ARequest>request_(RequestFactory::createRequest(client->getFd(), config_factory_));
						// Response res = request_->generateResponse();
					}
					else if (type == ASocket::RECVBODY)
					{
						
					}
					else if (type == ASocket::RECVCHUNK)
					{
						
					}
					else if (type == ASocket::READ)
					{
						//todo read
					}
				}
				else
				{
					if (type == ASocket::SEND)
					{
						//todo
					}
					else if (type == ASocket::WRITE)
					{
						//todo
					}
				}
				// client->recv_handler(config_factory_);
				// epollClose(socket);
			}
			else if (ev & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
			{
				epollClose(socket);
			}
			else
			{
				epollClose(socket);
				throw (EpollerException("epoll with unknown error at 123."));
			}
			it++;
		}
		// SocketHolder_.deleteMarkedSocket();
		SocketHolder::deleteMarkedSocket();
	}
}

// exception
Epoller::EpollerException::EpollerException(std::string const &msg)
:std::runtime_error(msg)
{
	return ;
}
