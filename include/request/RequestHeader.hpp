#pragma once
#include <map>
#include <string>
#include "string.hpp"

class RequestHeader
{
public:
	typedef std::map<std::string, std::string>	header_map;
	typedef header_map::const_iterator			const_iterator;
	typedef header_map::iterator				iterator;
private:
	header_map	headers_;
	void	make_headers(ft::string::string_vector const &str_vec);
public:
	RequestHeader();
	RequestHeader(ft::string::string_vector const &str_vec);
	~RequestHeader();
	RequestHeader(RequestHeader const &rhs);
	RequestHeader &operator=(RequestHeader const &rhs);
	iterator		get_pair(std::string const &key);
	const_iterator	get_pair(std::string const &key) const;
	//todo error
	//todo duplicate key
};
