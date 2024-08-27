#include "PostRequest.hpp"
#include "PostResponse.hpp"

PostRequest::PostRequest(RequestLine const &line, HttpHeader const &header, AHttpBody const &body)
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
	return (new PostResponse(getLine().getUri(), getHeader()));
}
