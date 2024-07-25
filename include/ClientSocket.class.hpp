/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:10:22 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/24 22:27:44 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ASocket.class.hpp"

class ClientSocket : public ASocket
{
private:
	//todo create buffer class
	int	acceptHandler(int listen_fd);
	ClientSocket();
	ClientSocket(ClientSocket const &rhs);
	ClientSocket &operator=(ClientSocket const &rhs);
public:
	ClientSocket(int listen_fd);
	~ClientSocket();
	void setSockaddr(void);
};
