#pragma once
#include "ARequest.hpp"

class Response;

class PostRequest : public ARequest
{
private:
	PostRequest();//=delete
public:
	explicit PostRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config);
	PostRequest(PostRequest const &rhs);
	PostRequest &operator=(PostRequest const &rhs);
	~PostRequest();
	Response	createResponse(void) const;
};
