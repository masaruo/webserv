/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fd.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 04:25:18 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/13 06:02:59 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Fd
{
private:
	int	fd_;

	Fd();
	Fd(Fd const &rhs);
	Fd &operator=(Fd const &rhs);
public:
	Fd(int fd = -1);
	~Fd();
	int		getFd(void) const;
	void	setFd(int vd);
	void	close(void);
	int		transfer(void);
};
