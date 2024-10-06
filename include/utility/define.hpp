#pragma once
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <stdint.h> // uint8_t
#include <stdexcept>

namespace ft
{
	int const	eof = 0;
	int const	err = -1;

	typedef enum 
	{
		GET,
		POST,
		DELETE,
		ERROR
	}	http_method_t;

//! str_vec
	typedef std::vector<std::string>	str_vec;
	typedef str_vec::iterator			str_vec_iter;
	typedef str_vec::const_iterator		str_vec_const_iter;
	typedef str_vec::size_type			str_vec_size_type;
	typedef str_vec::difference_type	str_vec_diff_type;

//! str_map
	typedef std::map<std::string, std::string>	str_map;
	typedef str_map::iterator					str_map_iter;
	typedef str_map::const_iterator				str_map_const_iter;
	typedef str_map::size_type					str_map_size_type;
	typedef str_map::difference_type			str_map_diff_type;

	template <typename T>
	T stonum(std::string const &str)
	{
		std::stringstream	ss(str);
		T					num = 0;
		ss >> num;
		if (ss.fail() || !ss.eof())
		{
			throw (std::invalid_argument("Conversion error in stonum (define.hpp at line 51)."));
		}
		return (num);
	}

	template <typename T>
	std::string	to_string(T num)
	{
		std::stringstream	numStr;
		numStr << num;
		if (numStr.fail())
		{
			throw (std::invalid_argument("Conversion error in to_string (define.hpp at line 63)."));
		}
		return (numStr.str());
	}

	template <typename CONTAINER>
	bool	is_empty(CONTAINER const &c)
	{
		if (c.empty())
			return (true);
		else
			return (false);
	}
}
