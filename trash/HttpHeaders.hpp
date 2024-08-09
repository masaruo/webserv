#pragma once
#include <map>
#include "string.hpp"

class HttpHeaders
{
public:
	typedef std::multimap<ft::string, ft::string>	string_map;
	typedef string_map::const_iterator				const_iterator;
	typedef string_map::iterator					iterator;
private:
	string_map	headers_;
	HttpHeaders &operator=(HttpHeaders const &rhs);
public:
	HttpHeaders();
	~HttpHeaders();
	HttpHeaders(HttpHeaders const &rhs);
	void		addHeader(ft::string key, ft::string value);
	ft::string	getHeader(ft::string key) const;
};
