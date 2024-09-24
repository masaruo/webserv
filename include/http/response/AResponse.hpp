#pragma once
#include <string>
#include <map>
#include "define.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"
#include "HttpStatus.hpp"
#include "unique_ptr.hpp"
#include "ARequest.hpp"

class AResponse
{
private:
	ft::unique_ptr<ARequest>	request_;
	HttpStatus	status_;
	HttpHeader	header_;
	HttpBody	body_;

	AResponse();//=delete

protected:
	void		setStatus(HttpStatus const &code);
	void		setHeader(HttpHeader const &inHeader);
	void		setBody(HttpBody const &body);
	std::string	getUri(void) const;

public:
	explicit AResponse(ft::unique_ptr<ARequest>request);
	virtual ~AResponse();
	AResponse(AResponse const &rhs);
	AResponse &operator=(AResponse const &rhs);
	RequestLine		getRequestLine(void) const;
	HttpHeader		getRequestHeader(void) const;
	HttpBody		getRequestBody(void) const;
	HttpStatus		getStatus(void) const;
	HttpHeader		getHeader(void) const;
	HttpBody		getBody(void) const;
	Binary::vec_bytes	getResponse(void) const;
	virtual void generateResponse(void) = 0;
};
