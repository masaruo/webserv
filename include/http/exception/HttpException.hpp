#pragma once
#include "HttpCode.hpp"
#include <stdexcept>

class Response;

class HttpException : public std::runtime_error
{
private:
	HttpCode::StatusCode error_code_;
	HttpException();//=delete
	HttpException &operator=(HttpException const &rhs);//=delete

protected:
	HttpCode::StatusCode	getErrorCode(void) const;
	std::string			to_string(void) const;

public:
	explicit HttpException(HttpCode::StatusCode error_code);
	HttpException(HttpException const &rhs);
	~HttpException() throw();
	virtual Response generateResponse(void) const;
};
