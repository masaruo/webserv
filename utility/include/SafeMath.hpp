/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SafeMath.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:58:59 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/23 21:57:28 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <stdexcept>
#include <limits>
#include <string>

namespace ft
{

template <typename T>
class SafeMath
{
private:
	//static class
	SafeMath(){};
	~SafeMath(){};
	SafeMath(SafeMath const &rhs){ (void) rhs; };
	SafeMath &operator=(SafeMath const &rhs){ (void) rhs; return (*this); };
public:
	static	T	add(T const &a, T const &b);
	static	T	sub(T const &a, T const &b);
	static	T	mul(T const &a, T const &b);
	static	T	div(T const &a, T const &b);
	static	T	mod(T const &a, T const &b);
};

template <typename T>
T	SafeMath<T>::add(T const &a, T const &b)
{
	T ans = 0;

	if (__builtin_add_overflow(a, b, &ans))
	{
		throw (std::runtime_error("Addition Exception"));
	}
	else
		return (ans);
}

template <typename T>
T	SafeMath<T>::sub(T const &a, T const &b)
{
	T	ans = 0;

	if (__builtin_sub_overflow(a, b, &ans))
	{
		throw (std::runtime_error("Subtraction Error"));
	}
	else
		return (ans);
}

template <typename T>
T	SafeMath<T>::mul(T const &a, T const &b)
{
	T	ans = 0;

	if (__builtin_mul_overflow(a, b, &ans))
	{
		throw (std::runtime_error("Multiplication Exception"));
	}
	return (ans);
}

template <typename T>
T	SafeMath<T>::div(T const &a, T const &b)
{
	if (b == 0)
	{
		throw (std::runtime_error("Division by zero"));
	}
	else if (a == std::numeric_limits<T>::min() && b == -1)
	{
		throw (std::runtime_error("Division Overflow"));
	}
	else 
		return (a / b);
}

template <typename T>
T	SafeMath<T>::mod(T const &a, T const &b)
{
	if (b == 0)
	{
		throw (std::runtime_error("remainder operation by zero"));
	}
	else if (a == std::numeric_limits<T>::min() && b == -1)
	{
		throw (std::runtime_error("remainder Overflow"));
	}
	else 
		return (a % b);
}
} // end of namespace ft
