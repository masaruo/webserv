#pragma once
#include "HttpCode.hpp"
#include "Config.hpp"
#include <stdexcept>

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

	class HttpException : public std::runtime_error
	{
	private:
		HttpCode::code_e	error_code_;
		HttpException();//=delete
		HttpException &operator=(HttpException const &rhs);//=delete
	protected:
		HttpCode::code_e	getErrorCode(void) const;
		std::string	to_string(void) const;
	public:
		explicit HttpException(HttpCode::code_e error_code);
		HttpException(HttpException const &rhs);
		~HttpException() throw();
		virtual Response	generateResponse(void) const;
	};

	class HttpExceptionWithConfig : public HttpException
	{
	private:
		config::Config	config_;
		HttpExceptionWithConfig();//=delete
		HttpExceptionWithConfig &operator=(HttpExceptionWithConfig const &rhs);//=delete
	public:
		explicit HttpExceptionWithConfig(HttpCode::code_e error_code, config::Config const &config);
		~HttpExceptionWithConfig() throw ();
		HttpExceptionWithConfig(HttpExceptionWithConfig const &rhs);
		Response	generateResponse(void) const;
	};
};
