#include "RedirectionException.hpp"
#include "Response.hpp"

RedirectionException::RedirectionException(HttpCode::StatusCode statuscode, std::string const &location)
:AResponseException(statuscode, location)
{
	return ;
}

RedirectionException::~RedirectionException()
{
	return ;
}

RedirectionException::RedirectionException(RedirectionException const &rhs)
:AResponseException(rhs)
{
	return ;
}

Response	RedirectionException::generateResponse(void) const
{
	HttpCode::StatusCode	error_code = getCode();
	HttpStatus const		status(error_code);

	ResponseHeader	header;
	// header.addValue("content-length", "0");
	// header.addValue("location", getPath());
	header.AHeader::add(AHeader::LOCATION, getPath());

	Response	r(status, header);
	return (r);
}
