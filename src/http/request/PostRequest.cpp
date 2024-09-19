#include "PostRequest.hpp"
// #include "PostResponse.hpp"
#include "CgiResponse.hpp"
#include <fstream>

PostRequest::PostRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body)
:ARequest(line, header, body)
{
	return ;
}

PostRequest::~PostRequest()
{
	return ;
}

PostRequest::PostRequest(PostRequest const &rhs)
:ARequest(rhs)
{
	return ;
}

PostRequest &PostRequest::operator=(PostRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator=(rhs);
	}
	return (*this); 
}

AResponse	*PostRequest::createResponse(void) const
{
	ft::unique_ptr<ARequest>tmp(new PostRequest(*this));
	return (new CgiResponse(tmp));
}
