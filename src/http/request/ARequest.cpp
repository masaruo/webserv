#include "ARequest.hpp"
#include "string.hpp"
#include <sys/stat.h>

ARequest::ARequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:line_(line)
,header_(header)
,body_()
,config_(config)
,matched_location_(setLocation())
,absolute_path_(setAbsolutePath())
,is_directory_(checkIsDirectory())
{
	assertAllowedMethod();
	return ;
}

ARequest::ARequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config)
:line_(line)
,header_(header)
,body_(body)
,config_(config)
,matched_location_(setLocation())
,absolute_path_(setAbsolutePath())
,is_directory_(checkIsDirectory())
{
	assertAllowedMethod();
	return ;
}

ARequest::ARequest(ARequest const &rhs)
:line_(rhs.line_)
,header_(rhs.header_)
,body_(rhs.body_)
,config_(rhs.config_)
,matched_location_(rhs.matched_location_)
,absolute_path_(rhs.absolute_path_)
,is_directory_(rhs.is_directory_)
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
		matched_location_ = rhs.matched_location_;
		absolute_path_ = rhs.absolute_path_;
		is_directory_ = rhs.is_directory_;
	}
	return (*this);
}

// setters
config::Config::location_s	ARequest::setLocation(void)
{
	config::Config::location_s loc;
	loc = config_.getLocation(header_.getFirstValue("host"));
	//todo if host == empty? possible? or if loc is empty?
	return (loc);
}

std::string	ARequest::setAbsolutePath(void)
{
	std::string	ans(config_.getRoot() + getLine().getUri().getPath());
	return (ans);
}

bool	ARequest::checkIsDirectory(void)
{
	struct stat	filestat;
	if (stat(absolute_path_.c_str(), &filestat) == ft::err)
	{
		throw (HttpStatus::HttpStatusExceptionWithResponse(HttpCode::NOT_FOUND));
	}
	bool	isDir;
	isDir = S_ISDIR(filestat.st_mode);
	return (isDir);
}

void	ARequest::assertAllowedMethod(void) const
{
	std::string const	method = line_.getMethod();
	if (!config_.isAllowedMethod(line_.getUri().getPath(), method))
	{
		throw (HttpStatus::HttpStatusException(HttpCode::METHOD_NOT_ALLOWED));
	}
}

// getters
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

config::Config::location_s	ARequest::getLocation(void) const
{
	return (matched_location_);
}

std::string	ARequest::getAbsolutePath(void) const
{
	return (absolute_path_);
}

bool	ARequest::isDirectory(void) const
{
	return (is_directory_);
}
