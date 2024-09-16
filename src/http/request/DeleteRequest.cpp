#include "DeleteRequest.hpp"
#include "CgiResponse.hpp"

DeleteRequest::DeleteRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body)
:ARequest(line, header)
,body_(body)
{
	return ;
}

DeleteRequest::~DeleteRequest()
{
	return ;
}

DeleteRequest::DeleteRequest(DeleteRequest const &rhs)
:ARequest(rhs.getLine(), rhs.getHeader())
,body_(rhs.body_)
{
	return ;
}

DeleteRequest &DeleteRequest::operator=(DeleteRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator=(rhs);
		body_ = rhs.body_;
	}
	return (*this);
}

AResponse	*DeleteRequest::createResponse(void) const
{
	return (new CgiResponse(getLine().getUri(), getHeader(), body_));
}
