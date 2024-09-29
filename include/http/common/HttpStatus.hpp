#pragma once
#include "HttpCode.hpp"
#include <stdexcept>

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

	class HttpException : public std::runtime_error
	{
	private:
		HttpCode::code_e	error_code_;
	public:
		HttpException(HttpCode::code_e error_code);
		HttpCode::code_e	getErrorCode(void) const;
		char const			*what() const throw();
		std::string			to_string(void) const;
	};

	class HttpStatusException : public HttpException
	{
	public:
		HttpStatusException(HttpCode::code_e error_code);
	};

	class HttpStatusExceptionWithResponse : public HttpException
	{
	public:
		HttpStatusExceptionWithResponse(HttpCode::code_e error_code);
	};
};
