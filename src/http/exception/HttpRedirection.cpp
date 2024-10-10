#include "HttpRedirection.hpp"
#include "Response.hpp"

HttpRedirection::HttpRedirection(HttpCode::StatusCode statuscode, std::string const &location)
:HttpException(statuscode)
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
	HttpCode::StatusCode	error_code = getErrorCode();
	HttpStatus const		status(error_code);

	HttpHeader	header;
	header.addValue("content-length", "0");
	header.addValue("location", location_);

	Response	r(status, header);
	return (r);
}
