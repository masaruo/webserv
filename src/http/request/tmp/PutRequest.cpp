#include "PutRequest.hpp"
#include "Response.hpp"
#include "ResourceManager.hpp"
#include <fstream>

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
		ARequest::operator=(rhs);
	}
	return (*this);
}

Response	PutRequest::createResponse(void) const
{
	ResourceManager const	resource(getLine().getUri(), getConfig());
	std::string const	normalized_path = resource.getNormalizedPath();
	upload(normalized_path);

	HttpHeader	header;
	header.setHeader("content-length", "0");

	HttpStatus	status(HttpCode::OK);

	Response	response(status, header);
	return (response);
}

void	PutRequest::upload(std::string const &path) const
{
	std::string const	upload_path = getConfig().getCgiUploadPath(path);
	std::string const	fullpath = getConfig().getRoot() + upload_path;

	std::ofstream	ofs(fullpath.c_str() , std::ios_base::trunc | std::ios_base::binary);
	if (!ofs)
	{
		throw (HttpStatus::HttpStatusException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	ofs.write(getBody().to_string().c_str(), getBody().getSize());
	if (!ofs)
	{
		throw (HttpStatus::HttpStatusException(HttpCode::INTERNAL_SERVER_ERROR));
	}
}
