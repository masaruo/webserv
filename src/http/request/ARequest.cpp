/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ARequest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 01:05:46 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/08 06:43:26 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ARequest.hpp"
#include "string.hpp"
#include "HttpException.hpp"
#include "RedirectionException.hpp"
#include "FileHandler.hpp"
#include "Response.hpp"
#include <sstream>
#include <unistd.h>// for access

ARequest::ARequest(RequestLine const &line, RequestHeader const &header, config::Config const &config, Server &server)
:requestLine_(line)
,header_(header)
,body_()
,config_(config)
,response_()
,server_(server)
,is_initialized_(false)
{
	// assertAllowedMethod();
	// assertRedirection();
	return ;
}

ARequest::ARequest(RequestLine const &line, RequestHeader const &header, HttpBody const &body, config::Config const &config, Server &server)
:requestLine_(line)
,header_(header)
,body_(body)
,config_(config)
,response_()
,server_(server)
,is_initialized_(false)
{
	// assertAllowedMethod();
	// assertRedirection();
	return ;
}

ARequest::ARequest(ARequest const &rhs)
:requestLine_(rhs.requestLine_)
,header_(rhs.header_)
,body_(rhs.body_)
,config_(rhs.config_)
,response_(rhs.response_)
,server_(rhs.server_)
,is_initialized_(rhs.is_initialized_)
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
		is_initialized_ = rhs.is_initialized_;
	}
	return (*this);
}

// setters
config::Config::LocationConfig	ARequest::setServerConfigLocation(void)//? detelte
{
	config::Config::LocationConfig loc;
	std::string const	&path = getLine().getUri().getPath();
	loc = config_.getConfigLocation(path);
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
	throw (RedirectionException(statuscode, redirectPath));
}

void	ARequest::assertAllowedMethod(void) const
{
	std::string const				&method = requestLine_.getMethod();
	std::string	const				&path = getLine().getUri().getPath();
	config::Config::LocationConfig	const	&loc = getConfig().getConfigLocation(path);
	if (!loc.directive_.hasValue(config::Config::ALLOWED_METHOD, method))
	{
		throw (HttpException(HttpCode::METHOD_NOT_ALLOWED));
	}
}

void	ARequest::setResponseStatus(HttpStatus const &response_status)
{
	response_.status_ = response_status;
}

void	ARequest::setResponseHeader(ResponseHeader const &response_header)
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

ResponseHeader	ARequest::getResponseHeader(void) const
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

RequestHeader	ARequest::getHeader(void) const
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

Server	&ARequest::getServerReference(void)
{
	return (server_);
}

void	ARequest::init(void) const
{
	if (is_initialized_)
		return ;
	assertAllowedMethod();
	assertRedirection();
	is_initialized_ = true;
}
