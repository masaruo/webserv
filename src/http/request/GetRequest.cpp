#include "GetRequest.hpp"
#include "Response.hpp"
#include "CgiRequest.hpp"
#include "FileHandler.hpp"

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

Response	GetRequest::generateResponse(void) const
{
	std::string	const	path = getLine().getUri().getPath();
	std::string const	absPath = getLocalPath() + getConfig().getIndex(path);

	HttpBody	body(FileReader::readTextFile(absPath));

	HttpHeader	header;
	header.setHeader("content-type", "text/html");
	header.setHeader("content-length", body.getSizeStr());

	HttpStatus	status(HttpCode::OK);

	Response	response(status, header, body);
	return (response);
}

