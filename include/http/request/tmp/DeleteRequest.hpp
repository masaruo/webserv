#pragma once
#include "ARequest.hpp"
#include "HttpBody.hpp"

class DeleteRequest : public ARequest
{
private:
	DeleteRequest();//=delete
public:
	explicit DeleteRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config);
	DeleteRequest(DeleteRequest const &rhs);
	DeleteRequest &operator=(DeleteRequest const &rsh);
	~DeleteRequest();

	Response	generateResponse(void) const;
};
