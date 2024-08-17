#pragma once
#include "HttpLine.hpp"
#include "HttpHeader.hpp"
#include "RequestFactory.hpp"
#include "unique_ptr.hpp"

class AResponse;

class ARequest
{
private:

protected:
	HttpLine	line_;
	HttpHeader	header_;
	// RequestBody		body_;
	// ft::unique_ptr<AResponse>	response_;

	void	parse(std::string const &raw_request);

public:
	std::string	dummy_res;//todo delete
	ARequest();
	ARequest(std::string const &raw_request);
	virtual ~ARequest();
	ARequest(ARequest const &rhs);
	ARequest &operator=(ARequest const &rhs);

	HttpLine const		&getRequestLine(void) const;
	HttpHeader const	&getRequestHeader(void) const;
	// virtual void		createMockResponse(int sockfd);
	virtual	AResponse	*createResponse(int sockfd) const = 0;
};
