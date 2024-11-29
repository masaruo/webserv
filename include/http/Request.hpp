#pragma once
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"
#include "Server.hpp"

class Request
{
private:
	RequestLine	line_;
	HttpHeader	header_;
	HttpBody	body_;
	Server		&server_;
	bool		hasBody_;
	void		assertAllowedMethod(void) const;
	Request &operator=(Request const &rhs);//delete
public:
	explicit Request(RequestLine const &line, HttpHeader const &header, Server &server);
	explicit Request(RequestLine const &line, HttpHeader const &header, HttpBody const &body, Server &server);
	Request(Request const &rhs);
	~Request();
	config::Config const	getConfig(void) const;
	bool					hasBody(void) const;
	RequestLine const		&getLine(void) const;
	HttpHeader const		&getHeader(void) const;
	HttpBody const			&getBody(void) const;
};
