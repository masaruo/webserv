#include "PostRequest.hpp"
#include "AResponse.hpp"

PostRequest::PostRequest()
:ARequest()
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
