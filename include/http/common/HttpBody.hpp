#pragma once
#include "define.hpp"
#include "HttpHeader.hpp"
#include <string>

class HttpBody
{
public:
	static std::size_t const	MAX_BODY_SIZE = 6000000;
private:
	std::string	data_;
	std::string	checkBodyLen(std::string const &body);
public:
	HttpBody();
	HttpBody(std::istringstream &iss, HttpHeader const &header);
	HttpBody(std::string const &str);
	~HttpBody();
	HttpBody(HttpBody const &rhs);
	HttpBody &operator=(HttpBody const &rhs);
	std::string	to_string(void) const;
	char const	*c_str(void) const;
	std::size_t	getSize(void) const;
	std::string	getSizeStr(void) const;
};
