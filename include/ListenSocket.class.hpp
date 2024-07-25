/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:44:49 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/24 22:10:09 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ASocket.class.hpp"

class ListenSocket : public ASocket
{
private:
	int	const	listening_port_;
	int	makeListenSocket(void);
	ListenSocket();
	ListenSocket(ListenSocket const &rhs);
	ListenSocket &operator=(ListenSocket const &rhs);
public:
	ListenSocket(int in_port);
	~ListenSocket();
	void	setSockaddr(void) = 0;
};
