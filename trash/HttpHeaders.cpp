#include "HttpHeaders.hpp"
#include <utility>

HttpHeaders::HttpHeaders()
:headers_()
{
	return ;
}

HttpHeaders::HttpHeaders(HttpHeaders const &rhs)
:headers_(rhs.headers_)
{
	return ;
}

HttpHeaders::~HttpHeaders()
{
	return ;
}

void	HttpHeaders::addHeader(ft::string key, ft::string value)
{
	headers_.insert(std::make_pair(key, value));
}

ft::string	HttpHeaders::getHeader(ft::string key) const
{
	const_iterator	it = headers_.find(key);
	ft::string		res("");

	if (it != headers_.end())
	{
		res = it->second;
	}
	return (res);
}
