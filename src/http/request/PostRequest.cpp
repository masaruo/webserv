#include "PostRequest.hpp"
// #include "PostResponse.hpp"
#include "CgiResponse.hpp"
#include <fstream>

PostRequest::PostRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body)
:ARequest(line, header)
,body_(body)
{
	return ;
}

PostRequest::~PostRequest()
{
	return ;
}

PostRequest::PostRequest(PostRequest const &rhs)
:ARequest(rhs)
,body_(rhs.body_)
{
	return ;
}

PostRequest &PostRequest::operator=(PostRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator=(rhs);
		body_ = rhs.body_;
	}
	return (*this); 
}

AResponse	*PostRequest::createResponse(void) const
{
	// createTempFile();
	return (new CgiResponse(getLine().getUri(), getHeader(), body_));
}
