#include "RequestLine.hpp"
#include "string.hpp"

RequestLine::RequestLine()
:method_str_(), uri_(), ver_(), method_type(ft::ERROR)
{
	return ;
}

RequestLine::RequestLine(std::string const &line)
:method_str_(), uri_(), ver_(), method_type(ft::ERROR)
{
	parse_line(line);
	method_type = get_method(method_str_);
	//todo ERRORCHECK / HTTPERROR
}

RequestLine::~RequestLine()
{
	return ;
}

RequestLine::RequestLine(RequestLine const &rhs)
:method_str_(rhs.method_str_)
,uri_(rhs.uri_)
,ver_(rhs.ver_)
,method_type(rhs.method_type)
{
	return ;
}

RequestLine &RequestLine::operator=(RequestLine const &rhs)
{
	if (this != &rhs)
	{
		method_str_ = rhs.method_str_;
		uri_ = rhs.uri_;
		ver_ = rhs.ver_;
		method_type = rhs.method_type;
	}
	return (*this);
}

void	RequestLine::parse_line(std::string const &line)
{
	ft::string	to_split = line;
	ft::string::string_vector	split_by_sp = to_split.split(ft::string::WHITESPACE);
	
	method_str_ = split_by_sp.at(0).str();
	uri_ = split_by_sp.at(1).str();
	ver_ = split_by_sp.at(2).str();
}

ft::http_method_t	RequestLine::get_method(std::string const &method_str) const
{
	if (method_str == "GET")
		return (ft::GET);
	else if (method_str == "POST")
		return (ft::POST);
	else if (method_str == "DELETE")
		return (ft::DELETE);
	else
		return (ft::ERROR);
}

ft::http_method_t	RequestLine::get_method(void) const
{
	return (method_type);
}

std::string	RequestLine::get_methodStr(void) const
{
	return (method_str_);
}

std::string	RequestLine::get_uri(void) const
{
	return (uri_);
}

std::string	RequestLine::get_ver(void) const
{
	return (ver_);
}
