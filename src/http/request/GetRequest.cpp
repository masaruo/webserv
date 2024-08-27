#include "GetRequest.hpp"
#include "GetResponse.hpp"

GetRequest::GetRequest(RequestLine const &line, HttpHeader const &header)
:ARequest(line, header)
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

}

GetRequest &GetRequest::operator=(GetRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator=(rhs);
	}
	return (*this);
}

GetResponse	*GetRequest::createResponse(void) const
{
	return (new GetResponse(getLine().getUri(), getHeader()));
}
