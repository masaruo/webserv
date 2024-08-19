#pragma once
#include <string>
#include <map>

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

	typedef std::pair<std::string, std::string>	str_pair_t;
	typedef std::map<std::string, std::string>	str_map_t;
	typedef str_map_t::iterator					str_map_iter;
	typedef str_map_t::const_iterator			str_map_const_iter;
	typedef str_map_t::size_type				str_map_size_type;
	typedef str_map_t::difference_type			str_map_difference_type;
}
