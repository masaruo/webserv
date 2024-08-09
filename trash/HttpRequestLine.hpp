#pragma once
#include "string.hpp"

class HttpRequestLine
{
public:
	typedef enum method_e {GET, POST, DELETE}	method_t;
private:
	method_t	method_;
	ft::string	methodStr_;
	ft::string	uri_;
	ft::string	httpVersion_;
	method_t	getMethod(ft::string method) const;
	HttpRequestLine();
	HttpRequestLine &operator=(HttpRequestLine const &rhs);
public:
	HttpRequestLine(ft::string method, ft::string uri, ft::string version);
	HttpRequestLine(HttpRequestLine const &rhs);
	~HttpRequestLine();
	method_t	getMethod(void) const;
};
