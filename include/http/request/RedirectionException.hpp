#pragma once
#include "AResponseException.hpp"

class RedirectionException : public AResponseException
{
private:
	RedirectionException();//=delete
	RedirectionException &operator=(RedirectionException const &rhs);//=delete
public:
	explicit RedirectionException(HttpCode::StatusCode statuscode, std::string const &location);
	~RedirectionException();
	RedirectionException(RedirectionException const &rhs);
	Response	generateResponse(void) const;
};
