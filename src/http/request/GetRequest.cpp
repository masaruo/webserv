#include "GetRequest.hpp"
#include "ResourceManager.hpp"
#include "Response.hpp"
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
	ResourceManager const	resource(getLine().getUri(), getConfig());
	std::string	path = resource.getNormalizedPath();

	HttpBody	body(FileReader::readTextFile(path));

	HttpHeader	header;
	header.setHeader("content-type", "text/html");
	header.setHeader("content-length", body.getSizeStr());

	HttpStatus	status(HttpCode::OK);

	Response	response(status, header, body);
	return (response);
}

