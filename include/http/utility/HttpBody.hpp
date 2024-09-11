#pragma once
#include "define.hpp"
#include <sstream>

class HttpBody
{
private:
	ft::bytes_vec	body_;
	ft::bytes_vec	parseBody(std::istringstream &iss, std::size_t len);
public:
	HttpBody();
	HttpBody(std::istringstream &iss, std::size_t len);
	~HttpBody();
	HttpBody(HttpBody const &rhs);
	HttpBody &operator=(HttpBody const &rhs);
	ft::bytes_vec	getBody(void) const;
};
