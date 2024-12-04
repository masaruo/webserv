/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:57:36 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/04 08:06:41 by mogawa           ###   ########.fr       */
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

	ClientSocket();//=delete
	ClientSocket(ClientSocket const &rhs);//=delete
	ClientSocket &operator=(ClientSocket const &rhs);//=delete
public:
	explicit ClientSocket(int fd, Server &server);
	virtual ~ClientSocket();
	bool			isObsolete(void) const;
	virtual void	handleEvent(uint32_t event);
	void			setData(std::string const &data);
};
