/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassiveSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:35:20 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/02 06:33:06 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ASocket.hpp"

class PassiveSocket : public ASocket
{
private:
	PassiveSocket();
	PassiveSocket(PassiveSocket const &rhs);
	PassiveSocket &operator=(PassiveSocket const &rhs);
public:
	explicit PassiveSocket(int port, Server &server);
	~PassiveSocket();

	void	execute(void);
};
