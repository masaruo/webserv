#include "StatusCode.hpp"
#include "define.hpp"
#include "string.hpp"

//todo FULL LIST to be added
// List of StatusCode
StatusCode const StatusCode::OK(200, "OK");
StatusCode const StatusCode::OK_NOCONTENT(204, "No Content");
StatusCode const StatusCode::NOT_FOUND(404, "Not Found");
StatusCode const StatusCode::INTERNAL_SERVER_ERROR(500, "Internal Server Error");

StatusCode::StatusCode()
:code_(0)
,message_("UNINITIALIZED")
{
	return ;
}

StatusCode::StatusCode(int code, std::string msg)
:code_(code)
,message_(msg + ft::string::CR + ft::string::LF)
{
	return ;
}

StatusCode::~StatusCode()
{
	return ;
}

StatusCode::StatusCode(StatusCode const &rhs)
:code_(rhs.code_)
,message_(rhs.message_)
{
	return ;
}

StatusCode &StatusCode::operator=(StatusCode const &rhs)
{
	if (this != &rhs)
	{
		code_ = rhs.code_;
		message_ = rhs.message_;
	}
	return (*this);
}

void	StatusCode::setCode(int inCode)
{
	code_ = inCode;
}

void	StatusCode::setMessage(std::string const &inMsg)
{
	message_ = inMsg;
}


int	StatusCode::getCode(void) const
{
	return (code_);
}

std::string	StatusCode::getMessage(void) const
{
	return (message_);
}
