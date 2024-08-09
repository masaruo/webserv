#pragma once
#include "ARequest.hpp"

class HttpRequestLine;
class Httpheaders;

class HttpGet : public ARequest
{
private:
	HttpGet();
	HttpGet &operator=(HttpGet const &rhs);
public:
	HttpGet(HttpRequestLine line, HttpHeaders headers);
	HttpGet(HttpGet const &rhs);
	~HttpGet();
	AResponse	*createResponse(void) const;
};
