#include "HttpGet.hpp"
#include "HttpHeaders.hpp"
#include "HttpRequestLine.hpp"

HttpGet::HttpGet(HttpRequestLine line, HttpHeaders headers)
:ARequest(line, headers)
{
	return ;
}

HttpGet::HttpGet(HttpGet const &rhs)
:ARequest(rhs.line_, rhs.headers_)
{
	return ;
}

HttpGet::~HttpGet()
{
	return ;
}

AResponse	*HttpGet::createResponse(void) const
{
	return ;
}
