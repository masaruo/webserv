#pragma once
#include "RequestHeader.hpp"
#include "RequestLine.hpp"
#include "RequestFactory.hpp"
#include "unique_ptr.hpp"

class AResponse;

class ARequest
{
private:

protected:
	RequestLine					line_;
	RequestHeader				header_;
	// RequestBody		body_;
	// ft::unique_ptr<AResponse>	response_;

	void	parse(std::string const &raw_request);

public:
	std::string	dummy_res;
	ARequest();
	ARequest(std::string const &raw_request);
	virtual ~ARequest() = 0;
	ARequest(ARequest const &rhs);
	ARequest &operator=(ARequest const &rhs);

	RequestLine	const	&getRequestLine(void) const;
	RequestHeader const	&getRequestHeader(void) const;
	virtual void		createMockResponse(int sockfd) = 0;
};
