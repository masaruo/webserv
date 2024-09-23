#pragma once
#include <string>
#include <stdexcept>

class StatusCode
{
public:
	static const StatusCode	OK;
	static const StatusCode OK_NOCONTENT;
	static const StatusCode	NOT_FOUND;
	static const StatusCode	INTERNAL_SERVER_ERROR;
private:
	int			code_;
	std::string	message_;
	explicit StatusCode(int code, std::string msg);
	void	setCode(int inCode);
	void	setMessage(std::string const &inMsg);
	explicit StatusCode();
public:
	~StatusCode();
	StatusCode(StatusCode const &rhs);
	StatusCode &operator=(StatusCode const &rhs);

	//getter
	int			getCode(void) const;
	std::string	getMessage(void) const;

	//error
	class HttpError : public std::runtime_error
	{
	public:
		HttpError(std::string const &msg);
	};
};
