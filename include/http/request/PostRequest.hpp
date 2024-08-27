#pragma once
#include "ARequest.hpp"
#include "AHttpBody.hpp"

class AResponse;

class PostRequest : public ARequest
{
private:
	AHttpBody	body_;
	PostRequest();//=delete
public:
	PostRequest(RequestLine const &line, HttpHeader const &header, AHttpBody const &body);
	PostRequest(PostRequest const &rhs);
	PostRequest &operator=(PostRequest const &rhs);
	~PostRequest();
	AResponse	*createResponse(void) const;
};
