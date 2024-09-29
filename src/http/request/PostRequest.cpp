#include "PostRequest.hpp"
// #include "PostResponse.hpp"
#include "CgiResponse.hpp"
#include <fstream>

PostRequest::PostRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config)
:ARequest(line, header, body, config)
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

Response	*PostRequest::createResponse(void) const
{
	ft::unique_ptr<ARequest>tmp(new PostRequest(*this));
	return (new CgiResponse(tmp));
}
