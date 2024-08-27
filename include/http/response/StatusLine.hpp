#pragma once
#include <string>
#include "StatusCode.hpp"

class StatusCode;

class StatusLine
{
private:
	std::string		version_;
	StatusCode		status_code_;
public:
	StatusLine();
	~StatusLine();
	StatusLine(StatusLine const &rhs);
	StatusLine &operator=(StatusLine const &rhs);
	//setter
	void	setVersion(std::string const &inVer);
	void	setStatusCode(StatusCode const &inStatus);

	//getter
	std::string	getVersion(void) const;
	StatusCode	getStatusCode(void) const;
};
