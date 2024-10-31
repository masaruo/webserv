/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientImpl.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 02:28:40 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/31 03:03:08 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <netinet/in.h>

class ClientImpl
{
private:
	int			fd_;
	sockaddr_in	addr_;
	socklen_t	addrlen_;
public:
	explicit	ClientImpl(int listening_fd);
	~ClientImpl();
	void	close(void);
	int		getFd(void) const;
};
