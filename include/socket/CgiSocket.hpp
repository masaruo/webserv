/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiSocket.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:53:40 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/11 06:27:05 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ASocket.hpp"
#include "RequestFactory.hpp"
#include "ClientSocket.hpp"

class CgiSocket : public ASocket
{
public:
	static int const	INTERNAL_SERVER_ERROR;
	static int const	NOT_FOUND;
	static int const	FORBIDDEN;
private:
	ClientSocket	*parent_socket_;
	RequestFactory	factory_;
	pid_t			child_pid_;
	std::string		send_buf_;
	std::string		recv_buf_;
	// int				sockfd_[2];
	// Fd				sockfd_[2];
	void	killAndWait(void) const;
	void	execChild(int sockfd[2]);
public:
	explicit	CgiSocket(ClientSocket *parent, RequestFactory const &factory, Server &server);
	~CgiSocket();
	ClientSocket	*getParentSocket(void) const;
	void	assertTimeout(void);
	void	handleCgiExecution(void);
	void	handleEvent(uint32_t event);
private:
	CgiSocket(CgiSocket const &rhs);
	CgiSocket &operator=(CgiSocket const &rhs);
};
