#include "PostRequest.hpp"
#include "CgiRequest.hpp"
#include "CgiRequest.hpp"

PostRequest::PostRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config, Server &server)
:ARequest(line, header, body, config, server)
{
	generateResponseData();
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

std::string	PostRequest::setLocalPath(void) const
{
	std::string	dummy = "";
	return (dummy);
}

void	PostRequest::generateResponseData(void)
{
	std::string const dummy = setLocalPath();
	(void) dummy;

	CgiRequest	cgi(getLine(), getHeader(), getBody(), getConfig(), getServerReference());
	setResponseStatus(cgi.getResponseStatus());
	setResponseHeader(cgi.getResponseHeader());
	setResponseBody(cgi.getResponseBody());
	setResponseHasBody(cgi.getResponseHasBody());
	return;
}
