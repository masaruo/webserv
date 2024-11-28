/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:57:36 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/28 05:40:05 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ASocket.hpp"
#include "RequestFactory.hpp"

class ClientSocket : public ASocket
{
private:
	RequestFactory	factory_;

	// IO							io_;
	// // ARequest					*request_;
	// Response					*response_;

	ClientSocket();
	ClientSocket(ClientSocket const &rhs);
	ClientSocket &operator=(ClientSocket const &rhs);
protected:
	// virtual ARequest	*generateRequest(Server &server) const;
public:
	explicit ClientSocket(int fd, Server &server);
	virtual ~ClientSocket();
	void	handleEvent(uint32_t event);
};
