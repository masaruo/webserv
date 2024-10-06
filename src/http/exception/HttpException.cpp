#include "HttpException.hpp"
#include "HttpStatus.hpp"
#include <sstream>
#include "Response.hpp"

//! HttpException
HttpException::HttpException(HttpCode::code_e error_code)
:std::runtime_error(HttpCode::str(error_code))
,error_code_(error_code)
{
	return ;
}

HttpException::~HttpException() throw ()
{
	return ;
}

HttpException::HttpException(HttpException const &rhs)
:std::runtime_error(rhs)
,error_code_(rhs.error_code_)
{
	return ;
}

HttpCode::code_e	HttpException::getErrorCode(void) const
{
	return (error_code_);
}

std::string	HttpException::to_string(void) const
{
	std::string const	runtime_msg = std::runtime_error::what();

	std::ostringstream	oss;
	oss << "HTTP/1.1";
	oss << " ";
	oss << runtime_msg;
	return (oss.str());
}

Response	HttpException::generateResponse(void) const
{
	HttpHeader	header;
	header.setElem("content-type", "text/plain");
	header.setElem("content-length", "0");

	HttpStatus	status(error_code_);

	Response	response(status, header);

	return (response);
}
