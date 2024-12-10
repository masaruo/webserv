#pragma once
#include "HttpStatus.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"

class AResponseBuilder
{
protected:
	HttpStatus	status_;
	HttpHeader	header_;
	HttpBody	body_;
	bool		has_body_;
	virtual void buildStatusLine() = 0;
	virtual void buildHeader() = 0;
	virtual void buildBody() = 0;
public:
	AResponseBuilder();
	virtual ~AResponseBuilder();
	AResponseBuilder(AResponseBuilder const &rhs);
	AResponseBuilder &operator=(AResponseBuilder const &rhs);
	AResponseBuilder	&setStatusCode(HttpStatus const &status);
	AResponseBuilder	&setHeader(std::string const &key, std::string const &value);
	AResponseBuilder	&setBody(std::string const &body);
	std::string			build();
};
