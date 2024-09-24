#include "ARequest.hpp"
#include "string.hpp"

ARequest::ARequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:line_(line)
,header_(header)
,body_()
,config_(config)
{
	return ;
}

ARequest::ARequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config)
:line_(line)
,header_(header)
,body_(body)
,config_(config)
{
	return ;
}

ARequest::ARequest(ARequest const &rhs)
:line_(rhs.line_)
,header_(rhs.header_)
,body_(rhs.body_)
,config_(rhs.config_)
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
		line_ = rhs.line_;
		header_ = rhs.header_;
		body_ = rhs.body_;
		config_ = rhs.config_;
	}
	return (*this);
}

RequestLine	ARequest::getLine(void) const
{
	return (line_);
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
