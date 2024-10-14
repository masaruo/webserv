#include "ARequest.hpp"
#include "string.hpp"
#include "HttpExceptionWithConfig.hpp"
#include "HttpRedirection.hpp"
#include "FileHandler.hpp"
#include "Response.hpp"
#include <sstream>
#include <unistd.h>// for access

ARequest::ARequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:requestLine_(line)
,header_(header)
,body_()
,config_(config)
,response_()
{
	assertAllowedMethod();
	assertRedirection();
	return ;
}

ARequest::ARequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config)
:requestLine_(line)
,header_(header)
,body_(body)
,config_(config)
,response_()
{
	assertAllowedMethod();
	assertRedirection();
	return ;
}

ARequest::ARequest(ARequest const &rhs)
:requestLine_(rhs.requestLine_)
,header_(rhs.header_)
,body_(rhs.body_)
,config_(rhs.config_)
,response_(rhs.response_)
{
	return ;
}

ARequest::~ARequest()
{
	return ;
}

ARequest	&ARequest::operator=(ARequest const &rhs)
{
	if (this != &rhs)
	{
		requestLine_ = rhs.requestLine_;
		header_ = rhs.header_;
		body_ = rhs.body_;
		config_ = rhs.config_;
		response_ = rhs.response_;
	}
	return (*this);
}

// setters
config::Config::LocationConfig	ARequest::setServerConfigLocation(void)//? detelte
{
	config::Config::LocationConfig loc;
	std::string const	&path = getLine().getUri().getPath();
	loc = config_.getConfigLocation(path);
	//todo if host == empty? possible? or if loc is empty?
	return (loc);
}

void	ARequest::assertRedirection(void) const
{
	std::string const	&path = getLine().getUri().getPath();
	config::Config::LocationConfig const	loc = config_.getConfigLocation(path);
	if (loc.pathType_ != config::Config::REDIRECTION_PATH)
		return ;

	std::string const				&codeStr = loc.directive_.getFirstValue(config::Config::REDIRECT_TO);
	HttpCode::StatusCode	const	statuscode = HttpCode::getStatusCode(codeStr);
	std::string const				&redirectPath = loc.directive_.getLastValue(config::Config::REDIRECT_TO);
	throw (HttpRedirection(statuscode, redirectPath));
}

void	ARequest::assertAllowedMethod(void) const
{
	std::string const						&method = requestLine_.getMethod();
	std::string const						&path = getLine().getUri().getPath();
	config::Config::LocationConfig	const	&loc = getConfig().getConfigLocation(path);
	if (!loc.directive_.hasValue(config::Config::ALLOWED_METHOD, method))
	{
		throw (HttpExceptionWithConfig(HttpCode::METHOD_NOT_ALLOWED, getConfig()));
	}
}

void	ARequest::setResponseStatus(HttpStatus const &response_status)
{
	response_.status_ = response_status;
}

void	ARequest::setResponseHeader(HttpHeader const &response_header)
{
	response_.header_ = response_header;
}

void	ARequest::setResponseBody(HttpBody const &response_body)
{
	response_.body_ = response_body;
}

void	ARequest::setResponseHasBody(bool	hasBody)
{
	response_.has_body_ = hasBody;
}

// getters
HttpStatus	ARequest::getResponseStatus(void) const
{
	return (response_.status_);
}

HttpHeader	ARequest::getResponseHeader(void) const
{
	return (response_.header_);
}

HttpBody	ARequest::getResponseBody(void) const
{
	return (response_.body_);
}

bool	ARequest::getResponseHasBody(void) const
{
	return (response_.has_body_);
}

RequestLine	ARequest::getLine(void) const
{
	return (requestLine_);
}

HttpHeader	ARequest::getHeader(void) const
{
	return (header_);
}

HttpBody	ARequest::getBody(void) const
{
	return (body_);
}

config::Config	ARequest::getConfig(void) const
{
	return (config_);
}

Response	ARequest::generateResponse(void) const
{
	if (getResponseHasBody())
	{
		Response r(getResponseStatus(), getResponseHeader(), getResponseBody());
		return (r);
	}
	else
	{
		Response r(getResponseStatus(), getResponseHeader());
		return (r);
	}
}
