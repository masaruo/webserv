#pragma once
#include <string>
#include <map>
#include <vector>
#include <sstream>

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

	std::size_t	stosizet(std::string const &numStr);
}
