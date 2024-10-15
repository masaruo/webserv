#include "DeleteRequest.hpp"
#include "HttpException.hpp"
#include "UriNormalizer.hpp"
#include "FileHandler.hpp"
#include "string.hpp"
#include <cstdio>// for std::remove

DeleteRequest::DeleteRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:ARequest(line, header, config)
{
	generateResponseData();
	return ;
}

DeleteRequest::~DeleteRequest()
{
	return ;
}

DeleteRequest::DeleteRequest(DeleteRequest const &rhs)
:ARequest(rhs)
{
	return ;
}

DeleteRequest &DeleteRequest::operator=(DeleteRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator=(rhs);
	}
	return (*this);
}

std::string	DeleteRequest::setLocalPath(void) const
{
	HttpUri const		&uri = getLine().getUri();
	std::string const	&dir = UriNormalizer::decodeDots(uri.getPathInfo().directory_);
	std::string const	&file = UriNormalizer::decodeDots(uri.getPathInfo().fileName_);
	std::string const	&root = getConfig().getRoot(dir);
	std::string const	&pathWithRoot = root + dir + "/" + file;

	if (FileHandler::checkPathExist(pathWithRoot))
	{
		if (FileHandler::checkIfDirectory(pathWithRoot))
			throw (HttpException(HttpCode::METHOD_NOT_ALLOWED));
		if (!FileHandler::checkIfFile(pathWithRoot))
			throw (HttpException(HttpCode::NOT_FOUND));

		std::string const &parentPath = root + uri.getPathInfo().directory_;
		if (access(parentPath.c_str(), W_OK) == ft::err)
			throw (HttpException(HttpCode::FORBIDDEN));
	}
	else
	{
		throw (HttpException(HttpCode::NOT_FOUND));
	}
	return (pathWithRoot);
}

void	DeleteRequest::removeFile(std::string const &path) const
{
	if (path.empty())
		throw (HttpException(HttpCode::BAD_REQUEST));

	if (std::remove(path.c_str()) == ft::err)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
}

void	DeleteRequest::generateResponseData(void)
{
	std::string const &abspath = setLocalPath();
	removeFile(abspath);

	HttpStatus	status(HttpCode::NO_CONTENT);

	HttpHeader	header;
	header.addValue(HttpHeader::CONTENT_LENGTH, "0");

	setResponseStatus(status);
	setResponseHeader(header);
	setResponseHasBody(false);
}
