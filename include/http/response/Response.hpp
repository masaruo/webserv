#pragma once
#include "define.hpp"
#include "ResponseHeader.hpp"
#include "HttpBody.hpp"
#include "HttpStatus.hpp"
#include <string>

class Response
{
private:
	HttpStatus					status_;
	ResponseHeader				header_;
	HttpBody					body_;
	bool						has_body_;


	void		setStatus(HttpStatus const &code);
	void		setHeader(ResponseHeader const &inHeader);
	void		setBody(HttpBody const &body);
	void		addMandetaryHeader(void);

public:
	Response();
	explicit Response(HttpStatus const &status);
	explicit Response(HttpStatus const &status, ResponseHeader const &header);
	explicit Response(HttpStatus const &status, ResponseHeader const &header, HttpBody const &body);
	~Response();
	Response(Response const &rhs);
	Response &operator=(Response const &rhs);

	std::string		to_string(void);
};
