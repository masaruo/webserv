/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ActiveSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:57:36 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/12 04:04:16 by mogawa           ###   ########.fr       */
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

class ActiveSocket : public ASocket
{
private:
	IO							io_;

	ActiveSocket();
	ActiveSocket(ActiveSocket const &rhs);
	ActiveSocket &operator=(ActiveSocket const &rhs);
public:
	explicit	ActiveSocket(int port, int fd, ft::State state, uint32_t event, Server &server, Addr addr);
	~ActiveSocket();
	void		setData(std::string const &data);
	std::string	getData(void) const;
	void		execute(void);
};
