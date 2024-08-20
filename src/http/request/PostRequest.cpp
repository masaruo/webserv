#include "PostRequest.hpp"
#include "AResponse.hpp"

PostRequest::PostRequest()
:ARequest()
{
	return ;
}

PostRequest::PostRequest(RequestLine const &line, HttpHeader const &header, AHttpBody const &body)
:ARequest(line, header)
,body_(body)
{
	return ;
}

PostRequest::~PostRequest()
{
	return ;
}

PostRequest::PostRequest(PostRequest const &rhs)
:ARequest()
{
	return ;
}

PostRequest &PostRequest::operator=(PostRequest const &rhs)
{
	if (this != &rhs)
	{
		//todo 
	}
	return (*this);
}

#include "GetResponse.hpp"//todo change to post response
AResponse	*PostRequest::createResponse(int sockfd) const
{
	return (new GetResponse());//todo change to PostResponse;
}
