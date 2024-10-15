#pragma once
#include "AResponseException.hpp"

class AutoIndexException : public AResponseException
{
private:
	// std::string	path_;
	AutoIndexException();//=delete
	AutoIndexException &operator=(AutoIndexException const &rhs);//=delete
public:
	AutoIndexException(HttpCode::StatusCode statuscode, std::string const &path);
	~AutoIndexException();
	AutoIndexException(AutoIndexException const &rhs);
	Response	generateResponse(void) const;
};
