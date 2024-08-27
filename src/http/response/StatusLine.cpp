#include "StatusLine.hpp"

StatusLine::StatusLine()
:version_()
,status_code_()
{
	return ;
}

StatusLine::~StatusLine()
{
	return ;
}

StatusLine::StatusLine(StatusLine const &rhs)
:version_(rhs.version_)
,status_code_(rhs.status_code_)
{
	return ;
}

StatusLine &StatusLine::operator=(StatusLine const &rhs)
{
	if (this != &rhs)
	{
		version_ = rhs.version_;
		status_code_ = rhs.status_code_;
	}
	return (*this);
}

void	StatusLine::setVersion(std::string const &inVer)
{
	version_ = inVer;
}

void	StatusLine::setStatusCode(StatusCode const &inStatus)
{
	status_code_ = inStatus;
}

std::string	StatusLine::getVersion(void) const
{
	return (version_);
}


StatusCode	StatusLine::getStatusCode(void) const
{
	return (status_code_);
}
