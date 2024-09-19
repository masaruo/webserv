#pragma once
#include "ARequest.hpp"
#include "HttpBody.hpp"

class DeleteRequest : public ARequest
{
private:
	DeleteRequest();//=delete
public:
	explicit DeleteRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body);
	DeleteRequest(DeleteRequest const &rhs);
	DeleteRequest &operator=(DeleteRequest const &rsh);
	~DeleteRequest();
	AResponse	*createResponse(void) const;
};
