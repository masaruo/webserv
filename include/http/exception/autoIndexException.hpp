#pragma once
#include "HttpException.hpp"

class AutoIndexException : public HttpException
{
private:
	std::string	path_;
	AutoIndexException();//=delete
	AutoIndexException &operator=(AutoIndexException const &rhs);//=delete
public:
	AutoIndexException(HttpCode::StatusCode statuscode, std::string const &path);
	~AutoIndexException() throw();
	AutoIndexException(AutoIndexException const &rhs);
	Response	generateResponse(void) const;
};
