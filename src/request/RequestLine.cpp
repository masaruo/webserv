#include "RequestLine.hpp"

RequestLine::RequestLine()
{
	return ;
}

RequestLine::~RequestLine()
{
	return ;
}

RequestLine::RequestLine(RequestLine const &rhs)
:method_(rhs.method_)
,uri_(rhs.uri_)
,version_(rhs.version_)
{
	return ;
}

RequestLine &RequestLine::operator=(RequestLine const &rhs)
{
	if (this != &rhs)
	{
		method_ = rhs.method_;
		uri_ = rhs.uri_;
		version_ = rhs.version_;
	}
	return (*this);
}

void	RequestLine::setMethod(std::string const &inMethod)
{
	method_ = inMethod;
}

void	RequestLine::setUri(std::string const &inUri)
{
	uri_ = inUri;
}

void	RequestLine::setVersion(std::string const &inVer)
{
	version_ = inVer;
}

std::string	RequestLine::getMethod(void) const
{
	return (method_);
}

std::string	RequestLine::getUri(void) const
{
	return (uri_);
}

std::string RequestLine::getVersion(void) const
{
	return (version_);
}
