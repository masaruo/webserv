#include "GetRequest.hpp"
#include "CgiRequest.hpp"
#include "AutoIndexException.hpp"
#include "FileHandler.hpp"
#include "UriNormalizer.hpp"
#include <sys/stat.h>

GetRequest::GetRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:ARequest(line, header, config)
{
	generateResponseData();
	return ;
}

GetRequest::~GetRequest()
{
	return ;
}

GetRequest::GetRequest(GetRequest const &rhs)
:ARequest(rhs)
{
	return ;
}

GetRequest &GetRequest::operator=(GetRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator=(rhs);
	}
	return (*this);
}

std::string	GetRequest::setLocalPath(void) const
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
		finalPath = pathWithRoot + indexFileName;
	}
	if (!FileHandler::checkPathExist(finalPath))
		throw (HttpException(HttpCode::NOT_FOUND));
	if (!FileHandler::checkIfFile(finalPath))
		throw (HttpException(HttpCode::CONFLICT));
	if (access(finalPath.c_str(), R_OK) == ft::err)
		throw (HttpException(HttpCode::FORBIDDEN));
	return (finalPath);
}

void	GetRequest::assertAutoIndex(std::string const &path, std::string const &pathWithRoot) const
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

std::string	GetRequest::getIndexFileName(std::string const &path) const
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

void	GetRequest::generateResponseData(void)
{
	HttpUri const		uri = getLine().getUri();
	std::string const	path = uri.getPath();

	if (uri.IsCgi())
	{
		CgiRequest	cgi(getLine(), getHeader(), getConfig());
		setResponseStatus(cgi.getResponseStatus());
		setResponseHeader(cgi.getResponseHeader());
		setResponseBody(cgi.getResponseBody());
		setResponseHasBody(cgi.getResponseHasBody());
		return;
	}
	else
	{
		std::string const &abspath = setLocalPath();

		HttpBody body(FileHandler::read(abspath));

		HttpHeader	header;
		header.addValue(HttpHeader::CONTENT_TYPE, "text/html");
		header.addValue(HttpHeader::CONTENT_LENGTH, body.getSizeStr());

		HttpStatus	status(HttpCode::OK);

		setResponseStatus(status);
		setResponseHeader(header);
		setResponseBody(body);
		setResponseHasBody(true);
		return ;
	}
}
