/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:57:36 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/15 06:02:16 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ASocket.hpp"
#include "RequestFactory.hpp"

class CgiSocket;

class ClientSocket : public ASocket
{
private:
	RequestFactory	factory_;
	std::string		data_;
	CgiSocket		*cgi_socket_;
	void	handleRead(void);
	void	handleSend(void);

	ClientSocket();//=delete
	ClientSocket(ClientSocket const &rhs);//=delete
	ClientSocket &operator=(ClientSocket const &rhs);//=delete
public:
	explicit ClientSocket(sockaddr_in const &addr, int fd, Server &server);
	virtual ~ClientSocket();
	void			assertTimeout(void);
	virtual void	handleEvent(uint32_t event);
	void			setData(std::string const &data);
	void			setCgiSocket(CgiSocket *cgi);
	time_t			getLastActiveTime(void) const;
};
