/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fd.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 04:34:06 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/31 07:07:13 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fd.hpp"
#include "unistd.h"

Fd::Fd(int fd)
:fd_(fd)
{
	return ;
}

Fd::~Fd()
{
	close();
}

int	Fd::getFd(void) const
{
	return (fd_);
}

void	Fd::close(void)
{
	if (fd_ > 2)
	{
		::close(fd_);
	}
	fd_ = -1;
}

int	Fd::transfer(void)
{
	int	tmp = fd_;
	fd_ = -1;
	return (tmp);
}
