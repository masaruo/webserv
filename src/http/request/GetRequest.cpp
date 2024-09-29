#include "GetRequest.hpp"
// #include "GetResponse.hpp"
#include "string.hpp"

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

}

GetRequest &GetRequest::operator=(GetRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator=(rhs);
	}
	return (*this);
}

// GetResponse	*GetRequest::createResponse(void) const
// {
// 	ft::unique_ptr<ARequest>tmp(new GetRequest(*this));
// 	return (new GetResponse(tmp));
// }
