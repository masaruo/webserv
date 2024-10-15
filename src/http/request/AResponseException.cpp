#include "AResponseException.hpp"

AResponseException::AResponseException(HttpCode::StatusCode statuscode, std::string const &path)
:statusCode_(statuscode)
,path_(path)
{
	return ;
}

AResponseException::~AResponseException()
{
	return ;
}

AResponseException::AResponseException(AResponseException const &rhs)
:statusCode_(rhs.statusCode_)
,path_(rhs.path_)
{
	return ;
}

HttpCode::StatusCode	AResponseException::getCode(void) const
{
	return (statusCode_);
}

std::string				AResponseException::getPath(void) const
{
	return (path_);
}
