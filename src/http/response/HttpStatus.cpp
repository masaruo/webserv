#include "HttpStatus.hpp"
#include <sstream>
#include "Response.hpp"

HttpStatus::HttpStatus()
:code_(HttpCode::INVALID_IN_WEBSERV)
{
	return ;
}

HttpStatus::HttpStatus(HttpCode::StatusCode code)
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

void	HttpStatus::setCode(HttpCode::StatusCode code)
{
	code_ = code;
	return ;
}

HttpCode::StatusCode	HttpStatus::getCode(void) const
{
	return (code_);
}

std::string	HttpStatus::to_string(void) const
{
	std::string const	msg = HttpCode::str(code_);
	std::string const	res("HTTP/1.1 " + msg);
	return (res);
}
