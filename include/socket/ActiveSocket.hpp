/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ActiveSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:57:36 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/18 05:54:23 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ASocket.hpp"
#include "ARequest.hpp"
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"
#include "Response.hpp"
#include "unique_ptr.hpp"
#include "IO.hpp"

class ARequest;
class Response;

class ActiveSocket : public ASocket
{
private:
	IO							io_;
	ARequest					*request_;
	Response					*response_;

	ActiveSocket();
	ActiveSocket(ActiveSocket const &rhs);
	ActiveSocket &operator=(ActiveSocket const &rhs);
protected:
	virtual ARequest	*generateRequest(Server &server) const;
public:
	explicit ActiveSocket(int port, int fd, ft::State state, uint32_t event, Server &server, Addr addr);
	virtual	~ActiveSocket();
	void		setData(std::string const &data);
	std::string	getData(void) const;
	void		execute(void);
};
