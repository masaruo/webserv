#pragma once
#include "HttpException.hpp"

class HttpRedirection : public HttpException
{
private:
	std::string	location_;
	HttpRedirection();//=delete
	HttpRedirection &operator=(HttpRedirection const &rhs);//=delete
public:
	explicit HttpRedirection(HttpCode::StatusCode statuscode, std::string const &location);
	~HttpRedirection() throw();
	HttpRedirection(HttpRedirection const &rhs);
	Response	generateResponse(void) const;
};
