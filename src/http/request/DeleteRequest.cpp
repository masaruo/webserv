#include "DeleteRequest.hpp"
#include "Response.hpp"
#include "HttpExceptionWithConfig.hpp"
#include <cstdio>// for std::remove

DeleteRequest::DeleteRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:ARequest(line, header, config)
{
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

void	DeleteRequest::removeFile(void) const
{
	HttpUri const		uri = getLine().getUri();
	std::string const	fileName = uri.getQueryValue("filename");
	std::string			deletePath = getLocalPath();

	if (deletePath.empty() || fileName.empty())
		throw (HttpException(HttpCode::BAD_REQUEST));
	deletePath.append("/" + fileName);

	assertFileExist(deletePath);

	if (std::remove(deletePath.c_str()) == ft::err)
		throw (HttpExceptionWithConfig(HttpCode::INTERNAL_SERVER_ERROR, getConfig()));
}

Response	DeleteRequest::generateResponse(void) const
{
	removeFile();

	HttpHeader	header;
	header.setHeader("content-length", "0");
	// header.setHeader("connection", "keep-alive");

	HttpStatus	status(HttpCode::NO_CONTENT);

	Response	r(status, header);
	return (r);
}
