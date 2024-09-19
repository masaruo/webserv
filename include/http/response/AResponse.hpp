#pragma once
#include <string>
#include <map>
#include "define.hpp"
#include "HttpHeader.hpp"
#include "StatusCode.hpp"
#include "HttpBody.hpp"
#include "unique_ptr.hpp"
#include "ARequest.hpp"

class AResponse
{
private:
	ft::unique_ptr<ARequest>	request_;
	// std::string	uri_;//todo delete
	// HttpHeader	request_header_;//todo delete
	StatusCode	code_;
	HttpHeader	header_;
	HttpBody	body_;

	AResponse();//=delete

protected:
	void		setCode(StatusCode const &code);
	void		setHeader(HttpHeader const &inHeader);
	void		setBody(HttpBody const &body);
	std::string	getUri(void) const;

public:
	// AResponse(std::string const &uri, HttpHeader const &req_header);//todo delete
	AResponse(ft::unique_ptr<ARequest>request);
	virtual ~AResponse();
	AResponse(AResponse const &rhs);
	AResponse &operator=(AResponse const &rhs);
	RequestLine		getRequestLine(void) const;
	HttpHeader		getRequestHeader(void) const;
	HttpBody		getRequestBody(void) const;
	StatusCode		getCode(void) const;
	HttpHeader		getHeader(void) const;
	HttpBody		getBody(void) const;
	Binary::vec_bytes	getResponse(void) const;
	virtual void generateResponse(void) = 0;
	class ResponseException : public std::runtime_error
	{
	public:
		ResponseException(std::string const &msg);
	};
};
