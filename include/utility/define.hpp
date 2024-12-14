#pragma once
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>

namespace ft
{
	// constants
	int			const	MAX_SOCKET_NUM = 255;
	std::size_t const	MAX_BODY_SIZE = 60000;
	std::size_t const	MAX_FIELD_LEN = 4000;
	std::size_t const	MAX_HEADERS_NUM = 100;
	std::size_t const	URI_MAX_LEN = 8000;
	std::size_t const	READ_BUF_SIZE = 4000;
	std::size_t const	WRITE_BUF_SIZE = 8000;
	int			const	PARENTFD = 0;
	int			const	CHILDFD = 1;
	time_t		const	TIMEOUT = 10;

	typedef std::vector<std::string>			str_vec;
	typedef std::map<std::string, std::string>	str_map;

	// communal functions
	template <typename SocketT>
	SocketT stonum(std::string const &str)
	{
		std::stringstream	ss(str);
		SocketT				num = 0;
		ss >> num;
		if (ss.fail() || !ss.eof())
		{
			throw (std::invalid_argument("Conversion error in stonum (define.hpp at line 51)."));
		}
		return (num);
	}

	template <typename SocketT>
	std::string	to_string(SocketT num)
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
