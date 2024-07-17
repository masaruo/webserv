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
#include <ostream>

namespace ft
{

class string : public std::string
{
public:
	static const std::string	NUMBER;
	static const std::string	LOWER;
	static const std::string	UPPER;
	static const std::string	ALPHA;
	static const std::string	ALNUM;
	typedef std::string::iterator 			iterator;
	typedef std::string::const_iterator		const_iterator;
	typedef std::string::size_type			size_type;
	typedef std::vector<ft::string>			string_vector;

	string();
	string(std::string const &str);
	string(char const *str);
	~string();
	string(string const &rhs);
	string &operator=(string const &rhs);
	//! wrapper functions
	bool		has_only(std::string const &to_search, size_type start = 0, size_type end = std::string::npos) const;
	bool		start_with(std::string const &to_search) const;
	bool		start_with(char const to_search) const;
	bool		end_with(std::string const &to_search) const;
	bool		end_with(char const to_search) const;
	char		&front(void);
	char const	&front(void) const;
	char		&back(void);
	char const	&back(void) const;
	void		pop(void);
	void		pop_back(void);
	void		trim(std::string const &target);
	void		trim(char const &target);
	string_vector		split(std::string const &to_split) const;
};

} //end of namespace ft
