#include "HttpError.class.hpp"
#include <sstream>

HttpError::HttpError(ErrorCode_t code, std::string const &msg)
:std::runtime_error(msg)
,code_(code)
{
	return ;
}

HttpError::~HttpError()
{
	return ;
}

HttpError::ErrorCode_t	HttpError::getCode(void) const
{
	return (code_);
}

char const	*HttpError::what(void) const throw ()
{
	static std::string	fullMessage;
	std::stringstream	ss;

	ss << code_;
	fullMessage = ss.str();
	fullMessage += ": " + std::string(std::runtime_error::what());
	return (fullMessage.c_str());
}
