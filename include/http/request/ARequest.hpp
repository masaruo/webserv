#pragma once
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include "RequestFactory.hpp"
#include <stdexcept>

class AResponse;

class ARequest
{
private:
	RequestLine	line_;
	HttpHeader	header_;
	ARequest();//=delete:
public:
	ARequest(RequestLine const &line, HttpHeader const &header);
	virtual ~ARequest();
	ARequest(ARequest const &rhs);
	ARequest &operator=(ARequest const &rhs);
	RequestLine 		getLine(void) const;
	HttpHeader 			getHeader(void) const;
	virtual	AResponse	*createResponse(void) const = 0;
	//ERROR CLASS
	class RequestException : public std::runtime_error
	{
	public:
		RequestException(std::string const &msg);
	};
};
