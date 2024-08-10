#pragma once
#include "RequestHeader.hpp"
#include "RequestLine.hpp"
#include "RequestFactory.hpp"

class ARequest
{
private:

protected:
	RequestLine		line_;
	RequestHeader	header_;
	// RequestBody		body_;
	// Response		response_;
	void	parse(std::string const &raw_request);

public:
	ARequest();
	ARequest(std::string const &raw_request);
	virtual ~ARequest() = 0;
	ARequest(ARequest const &rhs);
	ARequest &operator=(ARequest const &rhs);
	RequestLine	const &getRequestLine(void) const;
	RequestHeader const &getRequestHeader(void) const;
};
