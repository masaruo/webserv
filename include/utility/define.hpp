#pragma once
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>

namespace ft
{
	// constants
	int const			eof = 0;
	int const			err = -1;
	std::size_t const	MAX_BODY_SIZE = 600000;
	std::size_t const	MAX_FIELD_LEN = 4000;
	std::size_t const	MAX_HEADERS_NUM = 100;
	std::size_t const	URI_MAX_LEN = 8000;

	// typedef
	typedef std::vector<std::string>			str_vec;
	typedef std::map<std::string, std::string>	str_map;

	// communal functions
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
}// end of namespace ft
