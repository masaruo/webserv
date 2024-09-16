#pragma once
#include "ARequest.hpp"
#include "HttpBody.hpp"

class AResponse;

class PutRequest : public ARequest
{
private:
	HttpBody	body_;
	void	saveBody(void) const;
	PutRequest();//=delete
public:
	PutRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body);
	PutRequest(PutRequest const &rhs);
	PutRequest &operator=(PutRequest const &rhs);
	~PutRequest();
	AResponse	*createResponse(void) const;
};
