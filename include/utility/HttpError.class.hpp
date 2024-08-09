#pragma once
#include <stdexcept>

class HttpError : public std::runtime_error
{
public:
	typedef enum ErrorCode_e
	{
		BAD_REQUEST = 400,
		UNAUTHORIZED = 401,
		FORBIDDEN = 403,
		NOT_FOUND = 404,
		INTERNAL_SERVER_ERROR= 500,
	}	ErrorCode_t;
private:
	ErrorCode_t	code_;
	HttpError();
	HttpError(HttpError const &rhs);
	HttpError &operator=(HttpError const &rhs);
public:
	HttpError(ErrorCode_t code, std::string const &msg);
	~HttpError();
	ErrorCode_t	getCode() const;
	char const *what() const throw ();
};
