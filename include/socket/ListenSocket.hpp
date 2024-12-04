/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:35:20 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/04 08:06:41 by mogawa           ###   ########.fr       */
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
	bool	isObsolete(void) const;
	void	handleEvent(uint32_t event);
};
