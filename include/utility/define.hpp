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

	// typedef enum 
	// {
	// 	GET,
	// 	POST,
	// 	DELETE,
	// 	ERROR
	// }	http_method_t;

//! str_vec
	typedef std::vector<std::string>	str_vec;

//! str_map
	typedef std::map<std::string, std::string>	str_map;

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

	// char	decodeHex(std::string const &str)
	// {
	// 	std::istringstream	iss(str.substr(1));
	// 	int	value;
	// 	iss >> std::hex >> value;
	// 	if (iss.fail())
	// 	{
	// 		throw (std::invalid_argument("Convesion error in decodeHex at define.hpp:69."));
	// 	}
	// 	return (static_cast<char>(value));
	// }
}
