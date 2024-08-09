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
#include <cctype>
#include <algorithm>

std::string const	ft::string::DIGIT = "0123456789";
std::string const	ft::string::LOALPHA = "abcdefghijklmnopqrstuvwxyz";
std::string const	ft::string::UPALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string const	ft::string::ALPHA = LOALPHA + UPALPHA;
std::string const	ft::string::SP = " ";
std::string const	ft::string::HTAB = "\t";
std::string const	ft::string::VT = "\v";
std::string const	ft::string::FF = "\f";
std::string const	ft::string::CR = "\r";
std::string const	ft::string::LF = "\n";
std::string const	ft::string::WHITESPACE = SP + HTAB + VT + FF + CR;
std::string const	ft::string::CRLF = CR + LF;

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

ft::string::string(ft::string const &rhs)
:std::string(rhs)
{
	return ;
}

ft::string &ft::string::operator=(ft::string const &rhs)
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

void	ft::string::trim(ft::string const &target)
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

void	ft::string::to_lower(void)
{
	iterator		it = this->begin();
	const_iterator	end = this->end();
	while (it != end)
	{
		int	c = static_cast<int>(*it);
		if (isupper(c))
			*it = tolower(c);
		it++;
	}
}

void	ft::string::to_upper(void)
{
	iterator		it = this->begin();
	const_iterator	end = this->end();
	while (it != end)
	{
		int	c = static_cast<int>(*it);
		if (islower(c))
			*it = toupper(c);
		it++;
	}
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
