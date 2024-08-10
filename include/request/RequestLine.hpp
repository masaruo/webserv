#pragma once
#include <string>
#include "define.hpp"

class RequestLine
{
private:
	std::string			method_str_;
	std::string			uri_;
	std::string			ver_;
	ft::http_method_t	method_type;

	void				parse_line(std::string const &line);
	ft::http_method_t	get_method(std::string const &method_str) const;

	RequestLine();
public:
	RequestLine(std::string const &line);
	// RequestLine(ft::string inMethod, ft::string inUri, ft::string inVer);//? may not needed
	~RequestLine();
	RequestLine(RequestLine const &rhs);
	RequestLine &operator=(RequestLine const &rhs);
	ft::http_method_t	get_method(void) const;
	std::string			get_uri(void) const;
	std::string			get_ver(void) const;
	//todo ERROR and Verification
};
