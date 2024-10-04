/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:39:34 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/06 18:59:03 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include "define.hpp"

namespace ft
{

class string
{
private:
	std::string	base_;
public:
	static std::string const	DIGIT;
	static std::string const	LOALPHA;
	static std::string const	UPALPHA;
	static std::string const	ALPHA;
	static std::string const	ALNUM;
	static std::string const	SP;
	static std::string const	HTAB;
	static std::string const	WS;
	static std::string const	CR;
	static std::string const	LF;
	static std::string const	CRLF;
	static std::string const	CTL_EX_NUL_HTAB_CR_LF;
	static std::string const	NUL;
	static std::string const	CTL;
	static std::string const	DQUOTE;
	static std::string const	HEXDIG;
	static std::string const	VCHAR;
	static std::string const	CHAR;
	static std::string const	TOKEN;
	static std::string const	OBS_TEXT;
	static std::string const	FIELD_VALUE;
	static std::string const	URI_RESERVED;
	static std::string const	URI_UNRESERVED;
	static std::string const	QUERY;
	static std::string const	PCHAR;
	static std::string const	SCHEME;
	static std::string const	SUBDELIMS;
	static std::string const	HOST;

	typedef std::string::iterator 				iterator;
	typedef std::string::const_iterator			const_iterator;
	typedef std::string::reverse_iterator		reverse_iterator;
	typedef std::string::const_reverse_iterator	const_reverse_iterator;
	typedef std::string::size_type				size_type;
	typedef std::vector<ft::string>				string_vector;
	typedef string_vector::iterator				string_vector_iterator;
	typedef string_vector::const_iterator		string_vector_const_iterator;

	string();
	string(std::string const &str);
	string(char const *str);
	~string();
	string(string const &rhs);
	string &operator=(string const &rhs);
	string &operator=(std::string const &rhs);
	string &operator=(char const *ch);
	string &operator+=(string const &rhs);
	string &operator+=(std::string const &rhs);
	bool operator==(char const *rhs) const;
	bool operator==(std::string const &rhs) const;
	bool operator==(string const &rhs) const;
	operator std::string&();
	operator const std::string&() const;

	//! iterator
	iterator		begin();
	const_iterator	begin() const;
	iterator		end();
	const_iterator	end() const;

	//! wrapper
	size_type	size() const;
	bool		empty() const;
	char const	*c_str() const;

	//! provide access to base
	std::string	&str();
	std::string const &str() const;

	//! added functions
	bool		has_only(std::string const &to_search, size_type start = 0, size_type end = std::string::npos) const;
	bool		has(std::string const &to_search, size_type start = 0, size_type end = std::string::npos) const;
	bool		start_with(std::string const &to_search) const;
	bool		start_with(char const to_search) const;
	bool		start_with_str(std::string const &to_search) const;
	bool		end_with(std::string const &to_search) const;
	bool		end_with(char const to_search) const;
	bool		end_with_str(std::string const &to_search) const;
	char		&front(void);
	char const	&front(void) const;
	char		&back(void);
	char const	&back(void) const;
	void		pop(void);
	void		pop_back(void);
	void		trim(std::string const &target);
	void		trim(ft::string const &target);
	void		trim(char target);
	void		to_lower(void);
	void		to_upper(void);
	ft::bytes_vec	to_binary(void) const;
	string_vector	split(std::string const &to_split) const;
};

std::string		concatSplitVector(ft::string::string_vector const &str_vec, char delim);
std::string		removeConsecutiveDelim(std::string const &str, char delim);
} //end of namespace ft
