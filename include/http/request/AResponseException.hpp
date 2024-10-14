#pragma once
#include <string>
#include "HttpCode.hpp"

class Response;

class AResponseException
{
private:
	HttpCode::StatusCode	statusCode_;
	std::string				path_;
	AResponseException();//=delete
	AResponseException &operator=(AResponseException const &rhs);//=delete
protected:
	HttpCode::StatusCode	getCode(void) const;
	std::string				getPath(void) const;
public:
	explicit AResponseException(HttpCode::StatusCode statuscode, std::string const &path);
	virtual ~AResponseException();
	AResponseException(AResponseException const &rhs);
	virtual Response	generateResponse(void) const = 0;
};
