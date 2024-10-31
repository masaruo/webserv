/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenImpl.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:18:59 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/31 02:59:28 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class ListenImpl
{
private:
	int	port_;
	int	fd_;

	ListenImpl();
	ListenImpl(ListenImpl const &rhs);
	ListenImpl &operator=(ListenImpl const &rhs);
public:
	explicit	ListenImpl(int port);
	~ListenImpl();
	void	close(void);
	int		getFd(void) const;
};
