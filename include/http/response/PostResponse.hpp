#pragma once
#include "AResponse.hpp"

class PostResponse : public AResponse
{
private:
	PostResponse();//=delete
public:
	PostResponse(std::string const &target, HttpHeader const &req_header);
	~PostResponse();
	PostResponse(PostResponse const &rhs);
	PostResponse &operator=(PostResponse const &rhs);
	ft::bytes_vec	generateResponse(void);
};
