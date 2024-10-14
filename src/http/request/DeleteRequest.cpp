#include "DeleteRequest.hpp"
#include "Response.hpp"
#include "HttpExceptionWithConfig.hpp"
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

static std::string getParentPath(std::string const &path, std::string const &root)
{
	ft::string const 				&ftPath(path);
	ft::string::string_vector const	&splitBySlah = ftPath.split("/");

	if (splitBySlah.empty() || splitBySlah.size() == 1)
		return (root);

	std::string const &concat = root + ft::reverse_split(splitBySlah, '/');
	return (concat);
}

std::string	DeleteRequest::setLocalPath(void) const
{
	HttpUri const		&uri = getLine().getUri();
	std::string const	&path = UriNormalizer::decodeDots(uri.getPath());
	std::string const	&root = getConfig().getRoot(path);
	std::string const	&pathWithRoot = root + path;

	if (FileHandler::checkPathExist(pathWithRoot))
	{
		if (FileHandler::checkIfDirectory(pathWithRoot))
			throw (HttpException(HttpCode::METHOD_NOT_ALLOWED));
		if (!FileHandler::checkIfFile(pathWithRoot))
			throw (HttpException(HttpCode::NOT_FOUND));

		std::string const &parentPath = getParentPath(path, root);
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
	HttpUri const		&uri = getLine().getUri();
	std::string const	&fileName = uri.getQueryValue("filename");
	std::string			deletePath = path;

	if (deletePath.empty() || fileName.empty())
		throw (HttpException(HttpCode::BAD_REQUEST));
	deletePath.append("/" + fileName);

	if (std::remove(deletePath.c_str()) == ft::err)
		throw (HttpExceptionWithConfig(HttpCode::INTERNAL_SERVER_ERROR, getConfig()));
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
