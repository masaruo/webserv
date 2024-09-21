#pragma once
#include "AResponse.hpp"

class PostResponse : public AResponse
{
private:
	PostResponse();//=delete
public:
	explicit PostResponse(ft::unique_ptr<ARequest>request);
	// PostResponse(std::string const &target, HttpHeader const &req_header);
	~PostResponse();
	PostResponse(PostResponse const &rhs);
	PostResponse &operator=(PostResponse const &rhs);
	void	generateResponse(void);
};
