#include "HttpRedirection.hpp"
#include "Response.hpp"

HttpRedirection::HttpRedirection(HttpCode::code_e error_code, std::string const &location)
:HttpException(error_code)
,location_(location)
{
	return ;
}

HttpRedirection::~HttpRedirection() throw()
{
	return ;
}

HttpRedirection::HttpRedirection(HttpRedirection const &rhs)
:HttpException(rhs.getErrorCode())
,location_(rhs.location_)
{
	return ;
}

Response	HttpRedirection::generateResponse(void) const
{
	HttpCode::code_e	error_code = getErrorCode();
	HttpStatus const	status(error_code);

	HttpHeader	header;
	header.setElem("content-length", "0");
	header.setElem("location", location_);

	Response	r(status, header);
	return (r);
}
