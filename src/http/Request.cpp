#include "Request.hpp"
#include "Config.hpp"
#include "UriNormalizer.hpp"
#include "FileHandler.hpp"
#include "HttpException.hpp"
#include "AutoIndexException.hpp"

Request::Request(RequestLine const &line, HttpHeader const &header, Server &server)
:line_(line), header_(header), server_(server),hasBody_(false)
{
	return ;
}

Request::Request(RequestLine const &line, HttpHeader const &header, HttpBody const &body, Server &server)
:line_(line), header_(header), body_(body), server_(server), hasBody_(true)
{
	return ;
}

Request::Request(Request const &rhs)
:line_(rhs.line_), header_(rhs.header_), body_(rhs.body_), server_(rhs.server_), hasBody_(rhs.hasBody_)
{
	return ;
}

Request::~Request()
{
	return ;
}

// Request	&Request::operator=(Request const &rhs)
// {
// 	if (this != &rhs)
// 	{
// 		line_ = rhs.line_;
// 		header_ = rhs.header_;
// 		body_ = rhs.body_;
// 		server_ = rhs.server_;
// 		hasBody_ = rhs.hasBody_;
// 	}
// 	return (*this);
// }

// void	Request::assertAllowedMethod(void) const
// {
// 	std::string const &method = getLine().getMethod();
// 	std::string const &path = getLine().getUri().getPath();
// 	config::Config::LocationConfig const &loc = server_.getConfigFactory().getConfig().getConfigLocation(path);
// 	if (line_.getMethod() != "GET" && line_.getMethod() != "POST")
// 		throw (HttpException(HttpCode::METHOD_NOT_ALLOWED));
// }

config::Config const	Request::getConfig(void) const
{
	return (server_.getConfigFactory().getConfig(line_.getUri().getHost()));
}

bool	Request::hasBody(void) const
{
	return (hasBody_);
}

RequestLine const	&Request::getLine(void) const
{
	return (line_);
}

HttpHeader const	&Request::getHeader(void) const
{
	return (header_);
}

HttpBody const		&Request::getBody(void) const
{
	return (body_);
}

std::string 		Request::getMethod(void) const
{
	return (line_.getMethod());
}

void	Request::assertAutoIndex(std::string const &path, std::string const &pathWithRoot) const
{
	config::Config::LocationConfig	const &loc = getConfig().getConfigLocation(path);

	if (loc.directive_.hasKey(config::Config::INDEX))
		return ;

	if (loc.directive_.hasKey(config::Config::AUTOINDEX))
	{
		if (loc.directive_.getFirstValue(config::Config::AUTOINDEX) == "on")
		{
			throw (AutoIndexException(HttpCode::OK, pathWithRoot));
		}
	}
}

std::string	Request::getIndexFileName(std::string const &path) const
{
	config::Config::LocationConfig	const &loc = getConfig().getConfigLocation(path);
	if (loc.directive_.hasKey(config::Config::INDEX))
	{
		std::string const &index_directive = loc.directive_.getFirstValue(config::Config::INDEX);
		return (index_directive);
	}
	else
	{
		return ("");
	}
}

std::string 		Request::getTargetPath(void) const
{
	std::string			finalPath;
	HttpUri const		&uri = getLine().getUri();
	std::string const	&path = UriNormalizer::decodeDots(uri.getPath());
	std::string const	&root = getConfig().getRoot(path);
	std::string const	&pathWithRoot = root + path;

	if (!FileHandler::checkPathExist(pathWithRoot))
		throw (HttpException(HttpCode::NOT_FOUND));

	finalPath = pathWithRoot;
	if (FileHandler::checkIfDirectory(pathWithRoot))
	{
		assertAutoIndex(path, pathWithRoot);
		std::string const &indexFileName = getIndexFileName(path);
		finalPath = pathWithRoot + "/" + indexFileName;
	}
	if (!FileHandler::checkPathExist(finalPath))
		throw (HttpException(HttpCode::NOT_FOUND));
	if (!FileHandler::checkIfFile(finalPath))
		throw (HttpException(HttpCode::CONFLICT));
	if (access(finalPath.c_str(), R_OK) == ft::err)
		throw (HttpException(HttpCode::FORBIDDEN));
	return (finalPath);
}
