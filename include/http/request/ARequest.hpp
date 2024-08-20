#pragma once
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include "RequestFactory.hpp"
// #include "unique_ptr.hpp"

class AResponse;

class ARequest
{
private:

protected:
	RequestLine	line_;
	HttpHeader	header_;
public:
	ARequest();
	ARequest(RequestLine const &line, HttpHeader const &header);
	virtual ~ARequest() = 0;
	ARequest(ARequest const &rhs);
	ARequest &operator=(ARequest const &rhs);
	RequestLine const	&getRequestLine(void) const;
	HttpHeader const	&getRequestHeader(void) const;
	virtual	AResponse	*createResponse(int sockfd) const = 0;
};
