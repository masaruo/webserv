#pragma once
#include <PostRequest.hpp>

class CgiRequest : public PostRequest
{
private:
	CgiRequest();//=delete
public:
	CgiRequest(RequestLine const &line, HttpHeader const &header, AHttpBody const &body);
	~CgiRequest();
	CgiRequest(CgiRequest const &rhs);
	CgiRequest &operator=(CgiRequest const &rhs);
	AResponse	*createResponse(void) const;
};
