#include "ARequest.hpp"
#include "string.hpp"
#include "HttpExceptionWithConfig.hpp"
#include <sys/stat.h>
#include <sstream>

ARequest::ARequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:line_(line)
,header_(header)
,body_()
,config_(config)
,matched_location_(setLocation())
,absolute_path_(setAbsolutePath())
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
	}
	return (*this);
}

// setters
config::Config::location_s	ARequest::setLocation(void)
{
	config::Config::location_s loc;
	std::string const	path = getLine().getUri().getPath();
	loc = config_.getLocation(path);
	//todo if host == empty? possible? or if loc is empty?
	return (loc);
}

static bool	checkIsDirectory(std::string const &absolute_path, config::Config const &config)
{
	struct stat	filestat;
	if (stat(absolute_path.c_str(), &filestat) == ft::err)
	{
		throw (HttpExceptionWithConfig(HttpCode::NOT_FOUND, config));
	}
	bool	isDir;
	isDir = S_ISDIR(filestat.st_mode);
	return (isDir);
}

std::string	ARequest::setAbsolutePath(void)
{
	std::string	path = getLine().getUri().getPath();

	// create path by concatinate root and path;
	std::stringstream	ss;

	if (path == "/uploads")
		path = config_.getUploadStore(path);
	else if (matched_location_.is_cgi_)//! todo if cgi not implemented
		;
	else
		ss << config_.getRoot();

	if (path != "/")
		ss << "/";
	ss << path;
	std::string	tmp = ss.str();//todo delete
	config::Config	tmpconfig = getConfig();//todo delete
	if (checkIsDirectory(ss.str(), getConfig()))
	{
		std::string	file = config_.getIndex(path);
		ss << file;
	}
	return (ss.str());
}

void	ARequest::assertAllowedMethod(void) const
{
	std::string const	method = line_.getMethod();
	if (!config_.isAllowedMethod(line_.getUri().getPath(), method))
	{
		throw (HttpExceptionWithConfig(HttpCode::METHOD_NOT_ALLOWED, getConfig()));
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
