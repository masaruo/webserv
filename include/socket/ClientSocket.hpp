/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:57:36 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/12 05:32:46 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ASocket.hpp"
#include "RequestFactory.hpp"

class ClientSocket : public ASocket
{
private:
	RequestFactory	factory_;
	std::string		data_;

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
	time_t			getLastActiveTime(void) const;
	void			setData(std::string const &data);
};
