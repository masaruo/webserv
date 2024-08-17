#pragma once
#include <map>
#include <string>
#include "string.hpp"

class HttpHeader
{
public:
	typedef std::map<std::string, std::string>	header_map_t;
	typedef header_map_t::const_iterator		const_iterator;
	typedef header_map_t::iterator				iterator;
private:
	header_map_t	headers_;
	void	make_headers(ft::string::string_vector const &str_vec);
public:
	HttpHeader();
	HttpHeader(ft::string::string_vector const &str_vec);
	~HttpHeader();
	HttpHeader(HttpHeader const &rhs);
	HttpHeader &operator=(HttpHeader const &rhs);
	iterator		get_pair(std::string const &key);
	const_iterator	get_pair(std::string const &key) const;
	std::string		printHeader(void) const;
	//todo error
	//todo duplicate key
};
