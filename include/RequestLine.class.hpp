#pragma once
#include "string.hpp"

class RequestLine
{
public://typedef
typedef enum {GET, POST, DELETE, ERROR}	method_t;

private:
	method_t	method_;
	ft::string	target_;
	ft::string	version_;
	//method
	void	parse_line(ft::string const &line);
	method_t get_methodt(ft::string const &word) const;
	//hidden
	RequestLine();
	RequestLine &operator=(RequestLine const &rhs);
public:
	RequestLine(ft::string	const &line);
	RequestLine(RequestLine const &rhs);
	method_t	getMethod(void) const;

	//todo ERROR
	// 501 (not implemented)
	// 414 (uri too long)
};
