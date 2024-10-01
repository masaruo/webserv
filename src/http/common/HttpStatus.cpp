#include "HttpStatus.hpp"
#include <sstream>
#include "Response.hpp"

HttpStatus::HttpStatus()
:code_(HttpCode::UNINITIALIZED)
{
	return ;
}

HttpStatus::HttpStatus(HttpCode::code_e code)
:code_(code)
{
	return ;
}

HttpStatus::~HttpStatus()
{
	return ;
}

HttpStatus::HttpStatus(HttpStatus const &rhs)
:code_(rhs.code_)
{
	return ;
}

HttpStatus &HttpStatus::operator=(HttpStatus const &rhs)
{
	if (this != &rhs)
	{
		code_ = rhs.code_;
	}
	return (*this);
}

void				HttpStatus::setCode(HttpCode::code_e code)
{
	code_ = code;
	return ;
}

HttpCode::code_e	HttpStatus::getCode(void) const
{
	return (code_);
}

std::string	HttpStatus::to_string(void) const
{
	std::string const	msg = HttpCode::str(code_);
	std::string const	res("HTTP/1.1 " + msg);
	return (res);
}

//! HttpException
HttpStatus::HttpException::HttpException(HttpCode::code_e error_code)
:std::runtime_error(HttpCode::str(error_code))
,error_code_(error_code)
{
	return ;
}

HttpStatus::HttpException::~HttpException() throw ()
{
	return ;
}

HttpStatus::HttpException::HttpException(HttpException const &rhs)
:std::runtime_error(rhs)
,error_code_(rhs.error_code_)
{
	return ;
}

HttpCode::code_e	HttpStatus::HttpException::getErrorCode(void) const
{
	return (error_code_);
}

std::string	HttpStatus::HttpException::to_string(void) const
{
	std::string const	runtime_msg = std::runtime_error::what();

	std::ostringstream	oss;
	oss << "HTTP/1.1";
	oss << " ";
	oss << runtime_msg;
	return (oss.str());
}

Response	HttpStatus::HttpException::generateResponse(void) const
{
	HttpHeader	header;
	header.setHeader("content-type", "text/plain");
	header.setHeader("content-length", "0");

	HttpStatus	status(error_code_);

	Response	response(status, header);

	return (response);
}

//! HttpExceptionWithConfig
HttpStatus::HttpExceptionWithConfig::HttpExceptionWithConfig(HttpCode::code_e error_code, config::Config const &config)
:HttpException(error_code)
,config_(config)
{
	return ;
}

HttpStatus::HttpExceptionWithConfig::~HttpExceptionWithConfig() throw ()
{
	return ;
}

HttpStatus::HttpExceptionWithConfig::HttpExceptionWithConfig(HttpExceptionWithConfig const &rhs)
:HttpException(rhs)
,config_(rhs.config_)
{
	return ;
}

static HttpBody	generateBody(std::string const &path)
{
	//todo 
}

static HttpHeader	generateHeader(std::size_t body_length)
{
	//todo
}

Response	HttpStatus::HttpExceptionWithConfig::generateResponse(void) const
{
	HttpCode::code_e	error_code = HttpException::getErrorCode();


	//todo 401 error et al = create body
	//todo create header according to error code
}
