#include "PostRequest.hpp"
#include "Response.hpp"
#include "CgiRequest.hpp"
#include "CgiRequest.hpp"

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

Response	PostRequest::generateResponse(void) const
{
	CgiRequest	cgi(getLine(), getHeader(), getBody(), getConfig());
	Response	r(cgi.generateResponse());
	return (r);
}
