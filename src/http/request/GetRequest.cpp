#include "GetRequest.hpp"
#include "Response.hpp"
#include "CgiRequest.hpp"
// #include "AutoIndexRequest.hpp"
#include "autoIndexException.hpp"
#include "FileHandler.hpp"
#include <sys/stat.h>

GetRequest::GetRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:ARequest(line, header, config)
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
	std::string const	&path = uri.getPath();
	std::string const	&root = getConfig().getRoot(path);
	std::string const	&pathWithRoot = root + path;
	bool const			isDir = FileHandler::checkIfDirectory(pathWithRoot);

	if (isDir)
	{
		assertAutoIndex(path, pathWithRoot);
		std::string const &indexFileName = getIndexFileName(path);
		finalPath = pathWithRoot + "/" + indexFileName;
	}
	else
	{
		finalPath = pathWithRoot;
	}
	FileHandler::assertAccess(finalPath, R_OK);
	return (finalPath);
}

void	GetRequest::assertAutoIndex(std::string const &path, std::string const &pathWithRoot) const
{
	config::Config::LocationConfig	const &loc = getConfig().getConfigLocation(path);
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

Response	GetRequest::generateResponse(void) const
{
	HttpUri const		uri = getLine().getUri();
	std::string const	path = uri.getPath();

	if (uri.IsCgi())
	{
		CgiRequest	cgi(getLine(), getHeader(), getConfig());
		Response	r(cgi.generateResponse());
		return (r);
	}
	else if (checkIfAutoIndex(path))
	{
		AutoIndexRequest ai(getLine(), getHeader(), getConfig());
		Response	r(ai.generateResponse());
		return (r);
	}
	else
	{
		std::string	const	&path = uri.getPath();
		std::string const	&absPath = getLocalPath() + getConfigLocation().directive_.getFirstValue(config::Config::INDEX);

		HttpBody	body(FileHandler::read(absPath));//todo IOclass

		HttpHeader	header;
		header.addValue(HttpHeader::CONTENT_TYPE, "text/html");
		header.addValue(HttpHeader::CONTENT_LENGTH, body.getSizeStr());

		HttpStatus	status(HttpCode::OK);

		Response	r(status, header, body);
		return (r);
	}
}
