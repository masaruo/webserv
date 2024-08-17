#pragma once
#include <ARequest.hpp>

class AResponse;

class PostRequest : public ARequest
{
private:

public:
	PostRequest();
	PostRequest(PostRequest const &rhs);
	PostRequest &operator=(PostRequest const &rhs);
	~PostRequest();
	AResponse	*createResponse(int sockfd) const;
};
