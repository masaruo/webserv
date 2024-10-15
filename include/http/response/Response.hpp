#pragma once
#include "define.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"
#include "HttpStatus.hpp"
#include <string>

class Response
{
private:
	HttpStatus					status_;
	HttpHeader					header_;
	HttpBody					body_;
	bool						has_body_;

	Response();//=delete

	void		setStatus(HttpStatus const &code);
	void		setHeader(HttpHeader const &inHeader);
	void		setBody(HttpBody const &body);
	void		addMandetaryHeader(void);

public:
	explicit Response(HttpStatus const &status, HttpHeader const &header);
	explicit Response(HttpStatus const &status, HttpHeader const &header, HttpBody const &body);
	~Response();
	Response(Response const &rhs);
	Response &operator=(Response const &rhs);

	std::string		to_string(void) const;
};
