#include "HttpRequestLine.hpp"

HttpRequestLine::method_t	HttpRequestLine::getMethod(ft::string method) const
{
	if (method == "GET")
		return (HttpRequestLine::GET);
	else if (method == "POST")
		return (HttpRequestLine::POST);
	else if (method == "DELETE")
		return (HttpRequestLine::DELETE);
	else
	{
		//todo error?
	}
}

HttpRequestLine::method_t	HttpRequestLine::getMethod(void) const
{
	return (method_);
}

HttpRequestLine::HttpRequestLine(ft::string method, ft::string uri, ft::string version)
:method_(getMethod(method))
,methodStr_(method)
,uri_(uri)
,httpVersion_(version)
{
	return ;
}

HttpRequestLine::HttpRequestLine(HttpRequestLine const &rhs)
:method_(rhs.method_)
,methodStr_(rhs.methodStr_)
,uri_(rhs.uri_)
,httpVersion_(rhs.httpVersion_)
{
	return ;
}

HttpRequestLine::~HttpRequestLine()
{
	return ;
}
