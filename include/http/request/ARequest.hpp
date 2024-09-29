#pragma once
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"
#include "HttpStatus.hpp"
#include "RequestFactory.hpp"
#include "Config.hpp"
// #include "Response.hpp"

class Response;

class ARequest
{
private:
	RequestLine		line_;
	HttpHeader		header_;
	HttpBody		body_;
	config::Config	config_;
	ARequest();//=delete:
protected:
	RequestLine 		getLine(void) const;
	HttpHeader 			getHeader(void) const;
	HttpBody			getBody(void) const;
	config::Config		getConfig(void) const;
public:
	explicit ARequest(RequestLine const &line, HttpHeader const &header, config::Config const &config);
	explicit ARequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config);
	virtual ~ARequest();
	ARequest(ARequest const &rhs);
	ARequest &operator=(ARequest const &rhs);
	virtual	Response	generateResponse(void) const = 0;
};
