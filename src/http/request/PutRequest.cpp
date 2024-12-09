#include "PutRequest.hpp"
#include "HttpException.hpp"
#include "string.hpp"
#include "FileHandler.hpp"
#include "UriNormalizer.hpp"
#include <fstream>

PutRequest::PutRequest(RequestLine const &line, RequestHeader const &header, HttpBody const &body, config::Config const &config, Server &server)
:ARequest(line, header, body, config, server)
{
	return ;
}

PutRequest::~PutRequest()
{
	return ;
}

PutRequest::PutRequest(PutRequest const &rhs)
:ARequest(rhs)
{
	return ;
}

PutRequest &PutRequest::operator=(PutRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator = (rhs);
	}
	return (*this);
}

void	PutRequest::uploadFile(std::string const &absPath) const
{
	if (absPath.empty())
		throw (HttpException(HttpCode::BAD_REQUEST));

	std::ofstream	ofs(absPath.c_str() , std::ios_base::trunc | std::ios_base::binary);//chuncked?
	if (!ofs)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	ofs.write(getBody().to_string().c_str(), getBody().getSize());
	if (!ofs)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
}

std::string	PutRequest::setLocalPath(void) const
{
	HttpUri const		&uri = getLine().getUri();
	std::string const	&dir = UriNormalizer::decodeDots(uri.getPathInfo().directory_);
	std::string const	&file = UriNormalizer::decodeDots(uri.getPathInfo().fileName_);
	std::string const	&root = getConfig().getRoot(dir);
	std::string const	&pathWithRoot = root + dir + "/" + file;

	if (FileHandler::isExist(pathWithRoot))
	{
		if (FileHandler::isDir(pathWithRoot))
			throw (HttpException(HttpCode::METHOD_NOT_ALLOWED));
		if (!FileHandler::isFile(pathWithRoot) || !FileHandler::isW_OK(pathWithRoot))
			throw (HttpException(HttpCode::FORBIDDEN));
	}
	else
	{	std::string const &parent = root + dir;
		if (!FileHandler::isExist(parent))
			throw (HttpException(HttpCode::NOT_FOUND));
		if (!FileHandler::isDir(parent))
			throw (HttpException(HttpCode::CONFLICT));
		if (!FileHandler::isW_OK(parent))
			throw (HttpException(HttpCode::FORBIDDEN));
	}

	// if (FileHandler::checkPathExist(pathWithRoot))
	// {
	// 	if (FileHandler::checkIfDirectory(pathWithRoot))
	// 		throw (HttpException(HttpCode::METHOD_NOT_ALLOWED));
	// 	if (!FileHandler::checkIfFile(pathWithRoot))
	// 		throw (HttpException(HttpCode::CONFLICT));
	// 	if (access(pathWithRoot.c_str(), W_OK) == -1)
	// 		throw (HttpException(HttpCode::FORBIDDEN));
	// }
	// else
	// {
	// 	std::string const &parentPath = root + uri.getPathInfo().directory_;
	// 	if (!FileHandler::checkPathExist(parentPath))
	// 		throw (HttpException(HttpCode::NOT_FOUND));
	// 	if (!FileHandler::checkIfDirectory(parentPath))
	// 		throw (HttpException(HttpCode::CONFLICT));
	// 	if (access(parentPath.c_str(), W_OK) == -1)
	// 		throw (HttpException(HttpCode::FORBIDDEN));
	// }
	return (pathWithRoot);
}

void	PutRequest::generateResponseData(void)
{
	std::string const &abspath = setLocalPath();

	bool isOldFile = FileHandler::isFile(abspath);

	uploadFile(abspath);

	HttpStatus status;
	if (isOldFile)
		status.setCode(HttpCode::OK);
	else
		status.setCode(HttpCode::CREATED);

	ResponseHeader header;

	setResponseStatus(status);
	setResponseHeader(header);
	setResponseHasBody(false);
	return ;
}
