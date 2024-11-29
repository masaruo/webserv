/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:57:36 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/29 05:57:07 by mogawa           ###   ########.fr       */
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
	virtual void	handleEvent(uint32_t event);
	void			setData(std::string const &data);
};
