#pragma once
#include "AResponse.hpp"
#include "HttpBody.hpp"

class PutResponse : public Response
{
private:
	PutResponse();//=delete
public:
	explicit PutResponse(ft::unique_ptr<ARequest>request);
	// PutResponse(std::string const &uri, HttpHeader const &req_header, HttpBody const &req_body);
	~PutResponse();
	PutResponse(PutResponse const &rhs);
	PutResponse &operator=(PutResponse const &rhs);
	void	generateResponse(void);
};
