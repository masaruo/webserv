#pragma once
#include <string>
#include "define.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"
#include "HttpStatus.hpp"
#include "unique_ptr.hpp"
#include "ARequest.hpp"
#include "ResourceManager.hpp"

class Response
{
private:
	// ft::unique_ptr<ARequest>	request_;
	// ResourceManager				resource_;
	HttpStatus					status_;
	HttpHeader					header_;
	HttpBody					body_;
	bool						has_body_;

	Response();//=delete

protected:
	void		setStatus(HttpStatus const &code);
	void		setHeader(HttpHeader const &inHeader);
	void		setBody(HttpBody const &body);
	std::string	getUri(void) const;

public:
	explicit Response(HttpStatus const &status, HttpHeader const &header);
	explicit Response(HttpStatus const &status, HttpHeader const &header, HttpBody const &body);
	~Response();
	Response(Response const &rhs);
	Response &operator=(Response const &rhs);

	HttpStatus		getStatus(void) const;//todo move to private
	HttpHeader		getHeader(void) const;//todo move to private
	HttpBody		getBody(void) const;//todo move to private
	std::string		generateResponse(void) const;
};
