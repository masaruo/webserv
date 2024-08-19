/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:44:45 by mogawa            #+#    #+#             */
/*   Updated: 2024/04/25 11:54:25 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <stdexcept>

namespace ft
{
	template <typename T, typename F, int I>
	void	iter(T (&array)[I], int len, F f)
	{
		if (f == NULL)
			throw (std::invalid_argument("function pointer address is NULL."));
		else if (len < 0)
			throw (std::invalid_argument("len cannot be negative."));
		else if (I < len)
			throw (std::out_of_range("len is bigger than the size of the array."));
		int i = 0;
		while (i < len)
		{
			f(array[i]);
			i++;
		}
		return ;
	}

	template <typename T, typename F, int I>
	void	iter(T (&array)[I], F f)
	{
		if (f == NULL)
			throw (std::invalid_argument("function pointer address is NULL."));
		int i = 0;
		while (i < len)
		{
			f(array[i]);
			i++;
		}
		return ;
	}
}
