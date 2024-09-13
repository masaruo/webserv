#pragma once
#include <string>
#include <Binary.hpp>

class StatusCode
{
public:
	static const StatusCode	OK;
	static const StatusCode	NOT_FOUND;
	static const StatusCode	INTERNAL_SERVER_ERROR;
private:
	int			code_;
	std::string	message_;
	// Binary		binary_;
	StatusCode(int code, std::string msg);
	//setter
	void	setCode(int inCode);
	void	setMessage(std::string const &inMsg);
public:
	explicit StatusCode();
	~StatusCode();
	StatusCode(StatusCode const &rhs);
	StatusCode &operator=(StatusCode const &rhs);

	//getter
	int			getCode(void) const;
	std::string	getMessage(void) const;
};
