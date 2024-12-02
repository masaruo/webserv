#include "PostRequest.hpp"
#include "CgiSocket.hpp"
#include "Env.hpp"
#include "Server.hpp"

PostRequest::PostRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config, Server &server)
:ARequest(line, header, body, config, server)
,cgi_socket_(NULL)
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

	if (cgi_socket_ == NULL)
	{
		Server	&server = getServerReference();
		Env env(getLine(), getHeader(), getBody());
		CgiSocket	*cgi = new CgiSocket(env, "/webserv/cgi-bin/echo.py", getBody().c_str(), server);
		server.addSocket(cgi);
		return ;
	}
	else if (cgi_socket_->getState() != ft::CGI_COMPLETE)
	{
		return ;
	}
	else
	{
		std::string const	&res_str = cgi_socket_->getData();
	}




	// CgiRequest	cgi(getLine(), getHeader(), getBody(), getConfig(), getServerReference());
	// setResponseStatus(cgi.getResponseStatus());
	// setResponseHeader(cgi.getResponseHeader());
	// setResponseBody(cgi.getResponseBody());
	// setResponseHasBody(cgi.getResponseHasBody());
	return;
}
