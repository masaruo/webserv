#include "CgiRequest.hpp"
#include "CgiResponse.hpp"

CgiRequest::CgiRequest(RequestLine const &line, HttpHeader const &header, AHttpBody const &body)
:PostRequest(line, header, body)
{
	return ;
}

CgiRequest::~CgiRequest()
{
	return ;
}

CgiRequest::CgiRequest(CgiRequest const &rhs)
:PostRequest(rhs)
{
	return ;
}

CgiRequest &CgiRequest::operator=(CgiRequest const &rhs)
{
	if (this != &rhs)
	{
		PostRequest::operator=(rhs);
	}
	return (*this);
}

AResponse	*CgiRequest::createResponse(void) const
{
	return (new CgiResponse(getLine().getUri(), getHeader()));
}
