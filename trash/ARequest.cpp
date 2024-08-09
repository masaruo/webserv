#include "ARequest.hpp"
#include "HttpRequestLine.hpp"
#include "HttpHeaders.hpp"

ARequest::ARequest(HttpRequestLine line, HttpHeaders headers)
:line_(line)
,headers_(headers)
{
	return ;
}

ARequest::ARequest(ARequest const &rhs)
:line_(rhs.line_)
,headers_(rhs.headers_)
{
	return ;
}

ARequest::~ARequest()
{
	return ;
}

HttpRequestLine	ARequest::getRequestLine(void) const
{
	return (line_);
}

HttpHeaders ARequest::getRequestHeaders(void) const
{
	return (headers_);
}
