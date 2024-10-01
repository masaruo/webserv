#pragma once
#include "HttpCode.hpp"

class Response;

class HttpStatus
{
private:
	HttpCode::code_e	code_;
public:
	HttpStatus();
	HttpStatus(HttpCode::code_e code);
	~HttpStatus();
	HttpStatus(HttpStatus const &rhs);
	HttpStatus &operator=(HttpStatus const &rhs);
	void				setCode(HttpCode::code_e code);
	HttpCode::code_e	getCode(void) const;
	std::string			to_string(void) const;
};
