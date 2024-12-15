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

	if (!FileHandler::isExist(pathWithRoot))
		throw (HttpException(HttpCode::NOT_FOUND));

	finalPath = pathWithRoot;
	if (FileHandler::isDir(pathWithRoot))
	{
		if (!FileHandler::isR_OK(pathWithRoot))
			throw (HttpException(HttpCode::FORBIDDEN));
		assertAutoIndex(path, pathWithRoot);
		std::string const &indexFileName = getIndexFileName(path);
		finalPath = pathWithRoot + "/" + indexFileName;
	}
	if (!FileHandler::isFile(finalPath))
		throw (HttpException(HttpCode::NOT_FOUND));
	if (!FileHandler::isR_OK(finalPath))
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
		if (FileHandler::isR_OK(index_path))
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

static std::string	getMimeType(std::string const &path)
{
	if (path == "/")
		return ("text/html");

	std::string::size_type	posDot = path.find_last_of(".");
	if (posDot == std::string::npos)
		return ("application/octet-stream");
	
	std::string const	&ext = path.substr(posDot);
	if (ext == ".jpeg")
		return ("image/jpeg");
	else if (ext == ".png")
		return ("image/png");
	else if (ext == ".mp4")
		return ("video/mp4");
	else if (ext == ".html")
		return ("text/html");
	else if (ext == ".txt")
		return ("text/plain");
	else if (ext == ".pdf")
		return ("application/pdf");
	else if (ext == ".json")
		return ("application/json");
	else if (ext == ".zip")
		return ("application/zip");
	else
		return ("application/octet-stream");
}

void	GetRequest::generateResponseData(void)
{
	HttpUri const		&uri = getLine().getUri();
	std::string const	&path = uri.getPath();

	std::string const &abspath = setLocalPath();

	HttpBody body(FileHandler::read(abspath));

	ResponseHeader header;
	std::string const &mimetype = getMimeType(path);
	header.AHeader::add(AHeader::CONTENT_TYPE, mimetype);

	HttpStatus	status(HttpCode::OK);

	setResponseStatus(status);
	setResponseHeader(header);
	setResponseBody(body);
	setResponseHasBody(true);
	return ;
}
