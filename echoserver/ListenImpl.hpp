/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenImpl.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:18:59 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/31 05:13:00 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Fd.hpp"

class ISocket;

class ListenImpl
{
private:
	int	port_;
	Fd	fd_;

	ListenImpl();
	ListenImpl(ListenImpl const &rhs);
	ListenImpl &operator=(ListenImpl const &rhs);
public:
	explicit	ListenImpl(int port);
	explicit	ListenImpl(int port, int fd);
	~ListenImpl();
	int		getFd(void) const;
	void	close(void);
	// ISocket	*clone(void);
};
