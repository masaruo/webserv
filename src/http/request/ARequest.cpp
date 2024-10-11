#include "ARequest.hpp"
#include "string.hpp"
#include "HttpExceptionWithConfig.hpp"
#include "HttpRedirection.hpp"
#include <sstream>
#include <unistd.h>// for access

ARequest::ARequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:requestLine_(line)
,header_(header)
,body_()
,config_(config)
,configLocation_(setServerConfigLocation())
,localPath_(setLocalPath())
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
,configLocation_(setServerConfigLocation())
,localPath_(setLocalPath())
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
,configLocation_(rhs.configLocation_)
,localPath_(rhs.localPath_)
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
		configLocation_ = rhs.configLocation_;
		localPath_ = rhs.localPath_;
	}
	return (*this);
}

// setters
config::Config::LocationConfig	ARequest::setServerConfigLocation(void)
{
	config::Config::LocationConfig loc;
	std::string const	&path = getLine().getUri().getPath();
	loc = config_.getConfigLocation(path);
	//todo if host == empty? possible? or if loc is empty?
	return (loc);
}

std::string	ARequest::setLocalPath(void)
{
	HttpUri const		uri = getLine().getUri();
	std::string const	path = uri.getPath();
	std::string const	root = config_.getRoot(path);
	std::string localAbsPath = root + path;
	return (localAbsPath);
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
	std::string const	&method = requestLine_.getMethod();

	if (!configLocation_.directive_.hasValue(config::Config::ALLOWED_METHOD, method))
	{
		throw (HttpExceptionWithConfig(HttpCode::METHOD_NOT_ALLOWED, getConfig()));
	}
}

void	ARequest::assertFileExist(std::string const &file_path) const
{
	if (access(file_path.c_str(), W_OK) == ft::err)
		throw (HttpExceptionWithConfig(HttpCode::NOT_FOUND, getConfig()));
}

// getters
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

config::Config::LocationConfig	ARequest::getConfigLocation(void) const
{
	return (configLocation_);
}

std::string	ARequest::getLocalPath(void) const
{
	return (localPath_);
}
