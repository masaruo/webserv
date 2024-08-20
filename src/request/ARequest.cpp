#include "ARequest.hpp"
#include "string.hpp"

ARequest::ARequest()
:line_()
,header_()
{
	return ;
}

ARequest::ARequest(RequestLine const &line, HttpHeader const &header)
:line_(line)
,header_(header)
{
	return ;
}

ARequest::ARequest(ARequest const &rhs)
:line_(rhs.line_)
,header_(rhs.header_)
{
	return ;
}

ARequest::~ARequest()
{
	return ;
}

ARequest	&ARequest::operator=(ARequest const &rhs)
{
	if (this != &rhs)
	{
		line_ = rhs.line_;
		header_ = rhs.header_;
	}
	return (*this);
}

RequestLine const &ARequest::getRequestLine(void) const
{
	return (line_);
}

HttpHeader const &ARequest::getRequestHeader(void) const
{
	return (header_);
}
