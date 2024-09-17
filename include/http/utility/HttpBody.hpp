#pragma once
#include "define.hpp"
#include "Binary.hpp"
#include <string>
// #include <sstream>

class HttpBody
{
private:
	Binary		body_;
	std::size_t	size_;
	Binary	parseBody(std::istringstream &iss);
	Binary	parseBody(std::string const &str);
public:
	HttpBody();
	HttpBody(std::istringstream &iss);
	HttpBody(std::string const &str);
	HttpBody(Binary const &binary);
	~HttpBody();
	HttpBody(HttpBody const &rhs);
	HttpBody &operator=(HttpBody const &rhs);
	std::string	str(void) const;
	std::size_t	getSize(void) const;
};
