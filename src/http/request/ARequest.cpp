#include "ARequest.hpp"
#include "string.hpp"
#include "HttpExceptionWithConfig.hpp"
#include <sys/stat.h>
#include <sstream>
#include <unistd.h>// for access

ARequest::ARequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:line_(line)
,header_(header)
,body_()
,config_(config)
,matched_location_(setLocation())
,local_path_(setLocalPath())
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
,local_path_(setLocalPath())
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
,local_path_(rhs.local_path_)
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
		local_path_ = rhs.local_path_;
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

// bool	ARequest::assertIsDir(std::string const &absolute_path) const
// {
// 	struct stat	filestat;
// 	if (stat(absolute_path.c_str(), &filestat) == ft::err)
// 	{
// 		throw (HttpExceptionWithConfig(HttpCode::NOT_FOUND, config_));
// 	}
// 	bool	isDir;
// 	isDir = S_ISDIR(filestat.st_mode);
// 	return (isDir);
// }

std::string	ARequest::setLocalPath(void)
{
	std::string const	path = getLine().getUri().getPath();
	std::string const	root = config_.getRoot(path);
	std::string localAbsPath = root + path;

	// if (checkIsDir(localAbsPath))
	// {
	// 	std::string	fileName;
	// 	fileName =  config_.getIndex(path);
	// 	localAbsPath += "/" + fileName;
	// }
	// assertIsDir(localAbsPath);
	return (localAbsPath);
}

void	ARequest::assertAllowedMethod(void) const
{
	std::string const	method = line_.getMethod();
	if (!config_.isAllowedMethod(line_.getUri().getPath(), method))
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

std::string	ARequest::getLocalPath(void) const
{
	return (local_path_);
}
