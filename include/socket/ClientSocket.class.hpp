/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:10:22 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/28 10:08:18 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ASocket.class.hpp"

class ARequest;
class AResponse;

class ClientSocket : public ASocket
{
private:
	ARequest	*request_;
	AResponse	*response_;
	//todo create buffer class
	int	acceptHandler(int listen_fd);
	ClientSocket();
	ClientSocket(ClientSocket const &rhs);
	ClientSocket &operator=(ClientSocket const &rhs);
public:
	ClientSocket(int listen_fd);
	~ClientSocket();
	void setSockaddr(void);
	ssize_t	recv_handler(void);
	ssize_t	send_hander(void) const;
};
