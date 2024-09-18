/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoller.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:23:52 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/26 16:43:52 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include "SocketHolder.class.hpp"

class SocketHolder;

class Epoller
{
public:
	typedef std::vector<struct epoll_event>	ev_vec;
	typedef ev_vec::iterator				iterator;
	typedef ev_vec::const_iterator			const_iterator;
	typedef ev_vec::difference_type			difference_type;
	typedef ev_vec::size_type				size_type;
private:
	int const			epfd_;
	SocketHolder		SocketHolder_;
	ev_vec				res_evlist_;
	int					timeout_;
	int					epollWait(void);

//hidden
	Epoller();
	Epoller(Epoller const &rhs);
	Epoller &operator=(Epoller const &rhs);
public:
	Epoller(int size = 1, int timeout = -1);
	~Epoller();
	void	epollAdd(ASocket *socket);
	void	epollClose(ASocket *socket);
	void	epollLoop(void);
	class EpollerException : public std::runtime_error
	{
	public:
		EpollerException(std::string const &msg);
	};
};
