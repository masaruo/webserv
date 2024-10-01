#include "DeleteRequest.hpp"
#include "Response.hpp"

DeleteRequest::DeleteRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config)
:ARequest(line, header, body, config)
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

Response	DeleteRequest::generateResponse(void) const
{
	ResourceManager const	resource(getLine().getUri(), getConfig());
	std::string const	normalized_path = resource.getNormalizedPath();

}
