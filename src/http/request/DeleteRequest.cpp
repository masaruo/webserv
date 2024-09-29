#include "DeleteRequest.hpp"
#include "CgiResponse.hpp"

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

Response	*DeleteRequest::createResponse(void) const
{
	ft::unique_ptr<ARequest>tmp(new DeleteRequest(*this));
	return (new CgiResponse(tmp));
}
