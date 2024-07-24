/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoller.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:23:52 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/24 13:22:15 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "socket.class.hpp"

namespace ft{
	template <typename T>
	class unique_ptr;
}

class Port;

class Epoller
{
public:
	// typedef std::vector<ft::unique_ptr<Socket> > sockets_vector;
	typedef std::vector<Socket>				sockets_vector;
	typedef std::vector<struct epoll_event> epoll_vector;
	typedef epoll_vector::iterator			iterator;
	typedef epoll_vector::const_iterator	const_iterator;
	typedef epoll_vector::difference_type	difference_type;
	typedef epoll_vector::size_type			size_type;
private:
	int const			epfd_;
	epoll_vector		evlist_;
	sockets_vector		sockets_;
	int					maxevents_;
	int					timeout_;
	int					epollWait(void);

//hidden
	Epoller();
	Epoller(Epoller const &rhs);
	Epoller &operator=(Epoller const &rhs);
public:
	Epoller(int size, int timeout);
	~Epoller();
	void	epollAdd(Socket const &socket);
	void	epollClose(Socket &socket);
	void	epollLoop(void);
};
