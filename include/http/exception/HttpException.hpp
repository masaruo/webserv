#pragma once
#include "HttpCode.hpp"
#include "Config.hpp"
#include <stdexcept>

class Response;

class HttpException : public std::runtime_error
{
private:
	HttpCode::code_e error_code_;
	HttpException();									//=delete
	HttpException &operator=(HttpException const &rhs); //=delete

protected:
	HttpCode::code_e getErrorCode(void) const;
	std::string to_string(void) const;

public:
	explicit HttpException(HttpCode::code_e error_code);
	HttpException(HttpException const &rhs);
	~HttpException() throw();
	virtual Response generateResponse(void) const;
};
