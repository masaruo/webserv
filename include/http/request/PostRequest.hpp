#pragma once
#include "ARequest.hpp"
#include "HttpBody.hpp"
// #include "AHttpBody.hpp"

class AResponse;

class PostRequest : public ARequest
{
private:
	HttpBody	body_;
	// void	createTempFile(void) const;
	PostRequest();//=delete
public:
	PostRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body);
	PostRequest(PostRequest const &rhs);
	PostRequest &operator=(PostRequest const &rhs);
	~PostRequest();
	AResponse	*createResponse(void) const;
};
