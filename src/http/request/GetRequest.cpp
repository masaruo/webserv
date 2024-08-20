#include "GetRequest.hpp"
#include "GetResponse.hpp"

GetRequest::GetRequest()
:ARequest()
{
	return ;
}

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
		*this = rhs;
	}
	return (*this);
}

GetResponse	*GetRequest::createResponse(int sockfd) const
{
	return (new GetResponse());
}

std::string	GetRequest::get_path(void) const
{
	return (line_.getUri());
}
