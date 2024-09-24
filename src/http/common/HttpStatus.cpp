#include "HttpStatus.hpp"

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

//! EXCEPTIONS
HttpStatus::HttpStatusException::HttpStatusException(HttpCode::code_e error_code)
:std::runtime_error(HttpCode::str(error_code))
,error_code_(error_code)
{
	return ;
}

HttpCode::code_e	HttpStatus::HttpStatusException::getErrorCode(void) const
{
	return (error_code_);
}

char const	*HttpStatus::HttpStatusException::what() const throw()
{
	std::string const	runtime_msg = std::runtime_error::what();
	std::string const	res("HTTP/1.1 " + runtime_msg); 
	return (res.c_str());
}
