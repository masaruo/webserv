#include "PutRequest.hpp"
#include "Response.hpp"
#include "HttpExceptionWithConfig.hpp"
#include "string.hpp"
#include <fstream>
#include <cstdio>// for fdopen

PutRequest::PutRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config)
:ARequest(line, header, body, config)
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

static void	assertFileWithNoControlChar(std::string const &data)
{
	ft::string	ftdata(data);
	if (ftdata.has(ft::string::CTL_EX_NUL_HTAB_CR_LF))
		throw (HttpException(HttpCode::BAD_REQUEST));
}

void	PutRequest::uploadFile(void) const
{
	HttpUri const	uri = getLine().getUri();
	std::string const	fileName = uri.getQueryValue("filename");
	std::string			uploadPath = getLocalPath();

	if (uploadPath.empty() || fileName.empty())
		throw (HttpException(HttpCode::BAD_REQUEST));
	uploadPath.append("/" + fileName);

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

Response	PutRequest::generateResponse(void) const
{
	uploadFile();

	HttpHeader	header;
	header.setElem("content-length", "0");
	header.setElem("Connection", "close");

	HttpStatus	status(HttpCode::OK);

	Response	response(status, header);
	return (response);
}
