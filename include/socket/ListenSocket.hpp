/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:35:20 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/28 01:43:33 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ASocket.hpp"

class ListenSocket : public ASocket
{
private:
	ListenSocket();
	ListenSocket(ListenSocket const &rhs);
	ListenSocket &operator=(ListenSocket const &rhs);
public:
	explicit ListenSocket(int port, Server &server);
	~ListenSocket();
	void	handleEvent(uint32_t event);
};
