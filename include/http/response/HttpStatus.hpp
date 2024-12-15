#pragma once
#include "HttpCode.hpp"

class Response;

class HttpStatus
{
private:
	HttpCode::StatusCode	code_;
public:
	HttpStatus();
	HttpStatus(HttpCode::StatusCode code);
	~HttpStatus();
	HttpStatus(HttpStatus const &rhs);
	HttpStatus &operator=(HttpStatus const &rhs);
	void					setCode(HttpCode::StatusCode code);
	HttpCode::StatusCode	getCode(void) const;
	std::string				to_string(void) const;
};
