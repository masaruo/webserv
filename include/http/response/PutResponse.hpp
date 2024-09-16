#pragma once
#include "AResponse.hpp"
#include "HttpBody.hpp"

class PutResponse : public AResponse
{
private:
	HttpBody	request_body_;
	PutResponse();//=delete
public:
	PutResponse(std::string const &uri, HttpHeader const &req_header, HttpBody const &req_body);
	~PutResponse();
	PutResponse(PutResponse const &rhs);
	PutResponse &operator=(PutResponse const &rhs);
	void	generateResponse(void);
};
