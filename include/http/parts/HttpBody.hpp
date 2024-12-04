#pragma once
#include "HttpHeader.hpp"
#include <string>

class HttpBody
{
public:
private:
	std::string	data_;
public:
	HttpBody();
	HttpBody(std::string const &str);
	~HttpBody();
	HttpBody(HttpBody const &rhs);
	HttpBody &operator=(HttpBody const &rhs);
	std::string	to_string(void) const;
	char const	*c_str(void) const;
	std::size_t	getSize(void) const;
	std::string	size(void) const;
	bool		empty(void) const;
};
