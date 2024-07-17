/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft::string.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:46:16 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/05 18:25:54 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.hpp"

const std::string	ft::string::NUMBER = "0123456789";
const std::string	ft::string::LOWER = "abcdefghijklmnopqrstuvwxyz";
const std::string	ft::string::UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string	ft::string::ALPHA = ft::string::LOWER + ft::string::UPPER;
const std::string	ft::string::ALNUM = ft::string::NUMBER + ft::string::ALPHA;

ft::string::string()
:std::string()
{
	return ;
}


ft::string::string(std::string const &initialStr)
:std::string(initialStr)
{
	return ;
}

ft::string::string(char const *initialStr)
:std::string(initialStr)
{
	return ;
}

ft::string::~string()
{
	return ;
}

ft::string::string(string const &rhs)
:std::string(rhs)
{
	
}

ft::string &ft::string::operator=(string const &rhs)
{
	if (this != &rhs)
	{
		this->std::string::operator = (rhs);
	}
	return (*this);
}

bool	ft::string::has_only(std::string const &to_search, size_type start, size_type end) const
{
	if (end == std::string::npos)
		end = this->size();

	size_type const	pos = find_first_not_of(to_search, start);

	if (pos == std::string::npos || pos > end || pos < start)
		return (true);
	else
		return (false);
}

bool	ft::string::start_with(std::string const &to_search) const
{
	size_type pos = find_first_of(to_search);
	if (pos == 0)
		return (true);
	else
		return (false);
}

bool	ft::string::start_with(char const to_search) const
{
	size_type pos = find_first_of(to_search);
	if (pos == 0)
		return (true);
	else
		return (false);
}

bool	ft::string::end_with(std::string const &to_search) const
{
	size_type pos = find_last_of(to_search);
	if (pos + 1 == this->size())
		return (true);
	else
		return (false);
}

bool	ft::string::end_with(char const to_search) const
{
	size_type pos = find_last_of(to_search);
	if (pos + 1 == this->size())
		return (true);
	else
		return (false);
}

char	&ft::string::front(void)
{
	return (std::string::at(0));
}

char const	&ft::string::front(void) const
{
	return (std::string::at(0));
}

char	&ft::string::back(void)
{
	return (std::string::at(std::string::size() - 1));
}

char const	&ft::string::back(void) const
{
	return (std::string::at(std::string::size() - 1));
}

void	ft::string::pop(void)
{
	if (std::string::size() > 0)
		std::string::erase(0, 1);
}

void	ft::string::pop_back(void)
{
	if (std::string::size() > 0)
		std::string::erase(std::string::size() - 1, 1);
}

void	ft::string::trim(std::string const &target)
{
	while (start_with(target))
		this->pop();
	while (end_with(target))
		this->pop_back();
}

void	ft::string::trim(char const &target)
{
	while (start_with(target))
		this->pop();
	while (end_with(target))
		this->pop_back();
}

ft::string::string_vector	ft::string::split(std::string const &delims) const
{
	string_vector	split_v;
	size_type		cp_end = 0;
	size_type		cp_begin = 0;

	while (true)
	{
		cp_end = std::string::find_first_of(delims, cp_end);
		if (cp_end == std::string::npos)
		{
			break ;
		}
		else
		{
			split_v.push_back(std::string::substr(cp_begin, cp_end - cp_begin));
			cp_end = std::string::find_first_not_of(delims, cp_end);
			cp_begin = cp_end;
		}
	}
	if (cp_begin < std::string::size())
		split_v.push_back(std::string::substr(cp_begin, std::string::size() - cp_begin));
	return (split_v);
}
