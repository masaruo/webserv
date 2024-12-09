#include "GetRequest.hpp"
// #include "CgiRequest.hpp"
#include "AutoIndexException.hpp"
#include "FileHandler.hpp"
#include "UriNormalizer.hpp"
#include <sys/stat.h>

GetRequest::GetRequest(RequestLine const &line, RequestHeader const &header, config::Config const &config, Server &server)
:ARequest(line, header, config, server)
{
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
		finalPath = pathWithRoot + "/" + indexFileName;
	}
	if (!FileHandler::checkPathExist(finalPath))
		throw (HttpException(HttpCode::NOT_FOUND));
	if (!FileHandler::checkIfFile(finalPath))
		throw (HttpException(HttpCode::CONFLICT));
	if (access(finalPath.c_str(), R_OK) == -1)
		throw (HttpException(HttpCode::FORBIDDEN));
	return (finalPath);
}

void	GetRequest::assertAutoIndex(std::string const &path, std::string const &pathWithRoot) const
{
	config::Config::LocationConfig	const &loc = getConfig().getConfigLocation(path);

	if (loc.directive_.hasKey(config::Config::INDEX))
	{
		std::string const &index_name = loc.directive_.getFirstValue(config::Config::INDEX);
		std::string const &index_path = pathWithRoot + index_name;
		if (FileHandler::checkIfFile(index_path))
			return ;
	}

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
	HttpUri const		&uri = getLine().getUri();
	std::string const	&ext = uri.getPath();
	// std::string const	&pathinfo = uri.getPathInfo().fileName_;
	std::string const	&path = uri.getPath();

	std::string const &abspath = setLocalPath();

	HttpBody body(FileHandler::read(abspath));

	ResponseHeader header;
	// HttpHeader	header;
	// header.addValue(HttpHeader::CONTENT_TYPE, "text/html");//? how to get content-type???
	// header.addValue(HttpHeader::CONTENT_LENGTH, body.size());

	HttpStatus	status(HttpCode::OK);

	setResponseStatus(status);
	setResponseHeader(header);
	setResponseBody(body);
	setResponseHasBody(true);
	return ;
}
