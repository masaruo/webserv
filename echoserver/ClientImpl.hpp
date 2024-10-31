/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientImpl.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 02:28:40 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/31 05:44:06 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Fd.hpp"
#include <netinet/in.h>

class ClientImpl
{
private:
	Fd			fd_;
	sockaddr_in	addr_;
	socklen_t	addrlen_;
public:
	explicit	ClientImpl(int passive_fd);
	~ClientImpl();
	void	close(void);
	int		getFd(void) const;
};
