/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoller.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:24:00 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/30 03:58:57 by mogawa           ###   ########.fr       */
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
#include "GetRequest.hpp"
#include "Response.hpp"
#include "FileIOSocket.hpp"
#include "DeleteRequest.hpp"
#include "PostRequest.hpp"
#include "CgiRequest.hpp"
#include "PutRequest.hpp"
#include "IO.class.hpp""

#include <sys/epoll.h>
#include <unistd.h>

Epoller::Epoller(int size, std::string const &config_path)
:epfd_(epoll_create(size))
,config_factory_(config_path)
{
	if (epfd_ == -1)
	{
		// throw(EpollerException("epoll class initialization failed at 28.");
	}
	return ;
}

Epoller::Epoller(int size, int flag)
:epfd_(epoll_create(size))
,config_factory_(flag)
{
	if (epfd_ == -1)
	{
		// throw(EpollerException("epoll class initialization failed at 28."));
	}
	return ;
}

Epoller::~Epoller()
{
	if (epfd_ != -1)
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
	if (res == -1)
	{
		// throw (EpollerException("epoll add failed at 49."));
	}
	// SocketHolder_.addSocket(socket);//todo try catch
	// SocketHolder::addSocket(socket);
	return ;
}

void	Epoller::epollClose(ASocket *socket)
{
	int res = 0;
	res = epoll_ctl(epfd_, EPOLL_CTL_DEL, socket->getFd(), NULL);
	if (res == -1)
	{
		// throw (EpollerException("epoll close failed at 61."));
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
	if (numEvents == -1)
	{
		//? if (errno == EINTR)//forbidden
		// throw (EpollerException("epoll wait failed at 79."));
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
			else if (ev & EPOLLIN && type == ASocket::LISTEN)
			{
				ASocket *new_socket = new ClientSocket(socket->getFd());
				new_socket->setSocketType(ASocket::RECV);
				SocketHolder::addSocket(new_socket);
				// epollAdd(new_socket);
			}
			else if (ev & (EPOLLIN))
			{
				ClientSocket *client;
				client = dynamic_cast<ClientSocket*>(socket);
				if (client == NULL)
					std::cout << "138" << std::endl;//!
					// throw (EpollerException("epoll to get client socket failed at 111."));

				int fd = socket->getFd();
				try
				{
					if (type == ASocket::RECV)
					{
						RequestLine line;
						HttpHeader header;
						RequestFactory::createRequestLineAndHeader(fd, line, header);
						client->line_ = line;
						client->header_ = header;
						int flg = RequestFactory::hasBody(header);
						if (flg != RequestFactory::NOBODY)
							socket->setSocketType(ASocket::RECVBODY);
						else
							socket->setSocketType(ASocket::SEND);

						std::string const		&host = header.getFirstValue("host");
						config::Config const	&config = config_factory_.getConfig(host);
						std::string const		&method = line.getMethod();
						if (method == "GET")
						{
							ft::unique_ptr<ARequest>get(new GetRequest(line, header, config));
							client->request_ = get;
							client->response_ = client->request_->generateResponse();
							socket->setSocketType(ASocket::SEND);
						}
						else if (method == "DELETE")
						{
							ft::unique_ptr<ARequest>del(new DeleteRequest(line, header, config));
							client->request_ = del;
							client->response_ = client->request_->generateResponse();
							socket->setSocketType(ASocket::SEND);
						}
					}
					else if (type == ASocket::RECVBODY)
					{
						io::IO	input(fd);
						std::string	bodyStr;
						// RequestLine const &line = client->request_->getLine();
						// HttpHeader const &header = client->request_->getHeader();
						HttpHeader header = client->header_;
						RequestLine line = client->line_;
						int flg = RequestFactory::hasBody(header);
						if (flg == RequestFactory::HASBODY)
						{
							bodyStr = input.recv(header.getContentLen());
						}
						else// chunk
						{
							bodyStr = input.recv("chunked");
						}
						std::string const	&method = line.getMethod();
						std::string const	&host = header.getFirstValue("host");
						config::Config const &config = config_factory_.getConfig(host);
						if (method == "POST")
						{
							ft::unique_ptr<ARequest>post(new PostRequest(line, header, bodyStr, config));
							client->request_ = post;
							client->response_ = client->request_->generateResponse();
							socket->setSocketType(ASocket::SEND);
						}
						else if (method == "PUT")
						{
							ft::unique_ptr<ARequest>put(new PutRequest(line, header, bodyStr, config));
							client->request_ = put;
							client->response_ = client->request_->generateResponse();
							socket->setSocketType(ASocket::SEND);
						}
					}
				}
				catch (HttpException const &request)
				{
					client->response_ = request.generateResponse();
					socket->setSocketType(ASocket::SEND);
				}
			}
			else if (ev & (EPOLLOUT))
			{
				int fd = socket->getFd();
				ClientSocket *client;
				client = dynamic_cast<ClientSocket*>(socket);
				if (client == NULL)
					std::cout << "138" << std::endl;
				if (type == ASocket::SEND)
				{
					// Response res = client->request_->generateResponse();
					Response res = client->response_;
					send(fd, res.to_string().c_str(), res.to_string().size(), 0);
					epollClose(socket);
					//todo
				}
			}
			else if (ev & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
			{
				epollClose(socket);
			}
			else
			{
				epollClose(socket);
				// throw (EpollerException("epoll with unknown error at 123."));
			}
			it++;
		}
		// SocketHolder_.deleteMarkedSocket();
		SocketHolder::deleteMarkedSocket();
	}
}


// exception
// Epoller::EpollerException::EpollerException(std::string const &msg)
// :std::runtime_error(msg)
// {
// 	return ;
// }
