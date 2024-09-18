#include "ARequest.hpp"
#include "string.hpp"

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

RequestLine	ARequest::getLine(void) const
{
	return (line_);
}

HttpHeader	ARequest::getHeader(void) const
{
	return (header_);
}

//Error
ARequest::RequestException::RequestException(std::string const &msg)
:std::runtime_error(msg)
{
	return ;
}
