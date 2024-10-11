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
std::string const	ft::string::ALNUM = ft::string::ALPHA + ft::string::DIGIT;
std::string const	ft::string::SP = " ";
std::string const	ft::string::HTAB = "\t";
std::string const	ft::string::WS = ft::string::SP + ft::string::HTAB;
std::string const	ft::string::CR = "\r";
std::string const	ft::string::LF = "\n";
std::string const	ft::string::CRLF = CR + LF;
std::string const	ft::string::CTL_EX_NUL_HTAB_CR_LF =
	"\x01\x02\x03\x04\x05\x06\x07\x08\x0B\x0C\x0E\x0F"
	"\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x7F";
std::string const	ft::string::NUL = "\x00";
std::string const	ft::string::CTL =	ft::string::NUL + ft::string::CTL_EX_NUL_HTAB_CR_LF + \
										 ft::string::HTAB + ft::string::CRLF;
std::string const	ft::string::DQUOTE = "\"";
std::string const	ft::string::HEXDIG = ft::string::DIGIT + "ABCDEF";
std::string const	ft::string::VCHAR = ft::string::ALNUM + "!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~";
std::string const	ft::string::CHAR = ft::string::VCHAR + ft::string::CTL_EX_NUL_HTAB_CR_LF + "\x7f";
std::string const	ft::string::TOKEN = ft::string::ALNUM + "!#$%&'*+-.^_`|~";
std::string const	ft::string::OBS_TEXT = 
	"\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F"
	"\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F"
	"\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF"
	"\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF"
	"\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF"
	"\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF"
	"\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF"
	"\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";
std::string const	ft::string::FIELD_VALUE = ft::string::VCHAR + ft::string::WS + ft::string::OBS_TEXT;
std::string const	ft::string::SUBDELIMS = "!$&'()*+,;=";
std::string const	ft::string::URI_RESERVED = ":/?#[]@!$&'()*+,;=";
std::string const	ft::string::URI_UNRESERVED = ft::string::ALNUM + "-._~";
std::string const	ft::string::QUERY = ft::string::URI_UNRESERVED + "/?:@!$'()*+,;=";
std::string const	ft::string::PCHAR = ft::string::URI_UNRESERVED + ft::string::SUBDELIMS + ":@";
std::string const	ft::string::SCHEME = ft::string::ALNUM + "+-,";
//constructor / destructor
ft::string::string()
:base_()
{
	return ;
}


ft::string::string(std::string const &initialStr)
:base_(initialStr)
{
	return ;
}

ft::string::string(char const *initialStr)
:base_(initialStr)
{
	return ;
}

ft::string::~string()
{
	return ;
}

ft::string::string(ft::string const &rhs)
:base_(rhs.base_)
{
	return ;
}

ft::string &ft::string::operator=(ft::string const &rhs)
{
	if (this != &rhs)
	{
		base_ = rhs.base_;
	}
	return (*this);
}

ft::string &ft::string::operator=(std::string const &rhs)
{
	this->base_ = rhs;
	return (*this);
}

ft::string &ft::string::operator=(char const *ch)
{
	std::string tmp(ch);
	this->base_ = tmp;
	return (*this);
}

bool	ft::string::operator==(char const *rhs) const
{
	return (base_ == rhs);
}

bool	ft::string::operator==(std::string const &rhs) const
{
	return (base_ == rhs);
}

bool	ft::string::operator==(string const &rhs) const
{
	return (base_ == rhs.base_);
}

ft::string	&ft::string::operator+=(ft::string const &rhs)
{
	base_ += rhs.base_;
	return (*this);
}

ft::string	&ft::string::operator+=(std::string const &rhs)
{
	base_ += rhs;
	return (*this);
}

ft::string::operator std::string &()
{
	return (base_);
}

ft::string::operator const std::string &() const
{
	return (base_);
}

// iterator
ft::string::iterator	ft::string::begin()
{
	return (base_.begin());
}

ft::string::const_iterator	ft::string::begin() const
{
	return (base_.begin());
}

ft::string::iterator	ft::string::end()
{
	return (base_.end());
}

ft::string::const_iterator	ft::string::end() const
{
	return (base_.end());
}

// basic wrapper
ft::string::size_type	ft::string::size() const
{
	return (base_.size());
}

bool					ft::string::empty() const
{
	return (base_.empty());
}

char const	*ft::string::c_str() const
{
	return (base_.c_str());
}

// access to base
std::string	&ft::string::str()
{
	return (base_);
}

std::string const &ft::string::str() const
{
	return (base_);
}

bool	ft::string::has_only(std::string const &to_search, size_type start, size_type end) const
{
	if (end == std::string::npos)
		end = base_.size();

	size_type const	pos = base_.find_first_not_of(to_search, start);

	if (pos == std::string::npos || pos > end || pos < start)
		return (true);
	else
		return (false);
}

bool	ft::string::has(std::string const &to_search, size_type start, size_type end) const
{
	if (end == std::string::npos)
		end = base_.size();

	size_type const pos = base_.find(to_search);
	if (pos == std::string::npos || pos > end || pos < start)
		return (false);
	else
		return (true);
}

bool	ft::string::start_with(std::string const &to_search) const
{
	if (base_.empty() || to_search.empty())
		return (false);
	size_type pos = base_.find_first_of(to_search);
	if (pos == 0)
		return (true);
	else
		return (false);
}

bool	ft::string::start_with(char const to_search) const
{
	if (base_.empty())
		return (false);
	size_type pos = base_.find_first_of(to_search);
	if (pos == 0)
		return (true);
	else
		return (false);
}

bool	ft::string::start_with_str(std::string const &to_search) const
{
	if (base_.empty() || to_search.empty())
		return (false);
	size_type pos = base_.find(to_search);
	if (pos == 0)
		return (true);
	else
		return (false);
}

bool	ft::string::end_with(std::string const &to_search) const
{
	if (base_.empty() || to_search.empty())
		return (false);
	size_type pos = base_.find_last_not_of(to_search);
	if (pos == base_.size() - 1)
		return (false);
	else
		return (true);
}

bool	ft::string::end_with(char const to_search) const
{
	if (base_.empty())
		return (false);
	size_type pos = base_.find_last_not_of(to_search);
	if (pos == base_.size() - 1)
		return (false);
	else
		return (true);
}

bool	ft::string::end_with_str(std::string const &to_search) const
{
	if (base_.empty() || to_search.empty())
		return (false);
	size_type pos = base_.rfind(to_search);
	if (pos + to_search.size() == base_.size())
		return (true);
	else
		return (false);
}

char	&ft::string::front(void)
{
	return (base_.at(0));
}

char const	&ft::string::front(void) const
{
	return (base_.at(0));
}

char	&ft::string::back(void)
{
	return (base_.at(base_.size() - 1));
}

char const	&ft::string::back(void) const
{
	return (base_.at(base_.size() - 1));
}

void	ft::string::pop(void)
{
	if (base_.size() > 0)
		base_.erase(0, 1);
	else
		base_.clear();
}

void	ft::string::pop_back(void)
{
	if (base_.size() > 0)
		base_.erase(base_.size() - 1, 1);
	else
		base_.clear();
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

void	ft::string::trim(char target)
{
	while (start_with(target))
		this->pop();
	while (end_with(target))
		this->pop_back();
}

void	ft::string::to_lower(void)
{
	iterator		it = base_.begin();
	const_iterator	end = base_.end();
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
		cp_end = base_.find_first_of(delims, cp_end);
		if (cp_end == std::string::npos)
		{
			break ;
		}
		else
		{
			split_v.push_back(base_.substr(cp_begin, cp_end - cp_begin));
			cp_end = base_.find_first_not_of(delims, cp_end);
			cp_begin = cp_end;
		}
	}
	if (cp_begin < base_.size())
		split_v.push_back(base_.substr(cp_begin, base_.size() - cp_begin));
	return (split_v);
}

std::string	ft::concatSplitVector(ft::string::string_vector const &str_vec, char delim)
{
	ft::string::string_vector::const_iterator	iter = str_vec.begin();
	ft::string::string_vector::const_iterator	end = str_vec.end();
	std::string	concatinated = "";

	while (iter != end)
	{
		concatinated += iter->str();
		if (iter + 1 != end)
			concatinated += delim;
		iter++;
	}
	return (concatinated);
}

std::string	ft::removeConsecutiveDelim(std::string const &str, char delim)
{
	if (str.empty())
		return ("");

	ft::string	ftstr(str);
	std::string	delimStr(1, delim);
	ft::string::string_vector	strVec = ftstr.split(delimStr);
	std::string	concat = concatSplitVector(strVec, delim);
	return (concat);
}
