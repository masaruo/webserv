#include "PutRequest.hpp"
#include "Response.hpp"
#include "HttpExceptionWithConfig.hpp"
#include "string.hpp"
#include "FileHandler.hpp"
#include "UriNormalizer.hpp"
#include <fstream>
// #include <cstdio>// for fdopen

PutRequest::PutRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config)
:ARequest(line, header, body, config)
{
	generateResponseData();
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

static void	assertFileWithNoControlChar(std::string const &data)
{
	ft::string	ftdata(data);
	if (ftdata.has(ft::string::CTL_EX_NUL_HTAB_CR_LF))
		throw (HttpException(HttpCode::BAD_REQUEST));
}

void	PutRequest::uploadFile(std::string const &absPath) const
{
	HttpUri const		&uri = getLine().getUri();
	std::string const	&fileName = uri.getPathInfo().fileName_;
	std::string			uploadPath = absPath;

	if (uploadPath.empty() || fileName.empty())
		throw (HttpException(HttpCode::BAD_REQUEST));

	std::ofstream	ofs(uploadPath.c_str() , std::ios_base::trunc | std::ios_base::binary);//chuncked?
	if (!ofs)
	{
		throw (HttpExceptionWithConfig(HttpCode::INTERNAL_SERVER_ERROR, getConfig()));
	}
	ofs.write(getBody().to_string().c_str(), getBody().getSize());
	if (!ofs)
	{
		throw (HttpExceptionWithConfig(HttpCode::INTERNAL_SERVER_ERROR, getConfig()));
	}
}

std::string	PutRequest::setLocalPath(void) const
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
			throw (HttpException(HttpCode::CONFLICT));
		if (access(pathWithRoot.c_str(), W_OK) == ft::err)
			throw (HttpException(HttpCode::FORBIDDEN));
	}
	else
	{
		std::string const &parentPath = root + uri.getPathInfo().directory_;
		if (!FileHandler::checkPathExist(parentPath))
			throw (HttpException(HttpCode::NOT_FOUND));
		if (!FileHandler::checkIfDirectory(parentPath))
			throw (HttpException(HttpCode::CONFLICT));
		if (access(parentPath.c_str(), W_OK) == ft::err)
			throw (HttpException(HttpCode::FORBIDDEN));
	}
	return (pathWithRoot);
}

void	PutRequest::generateResponseData(void)
{
	std::string const &abspath = setLocalPath();
	uploadFile(abspath);

	HttpStatus	status(HttpCode::OK);

	HttpHeader	header;
	header.addValue(HttpHeader::CONTENT_LENGTH, "0");

	setResponseStatus(status);
	setResponseHeader(header);
	setResponseHasBody(false);
	return ;
}
