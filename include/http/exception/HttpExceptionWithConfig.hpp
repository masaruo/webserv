#pragma once
#include "HttpException.hpp"
#include "HttpBody.hpp"

class HttpExceptionWithConfig : public HttpException
{
private:
	config::Config config_;
	HttpExceptionWithConfig();												//=delete
	HttpExceptionWithConfig &operator=(HttpExceptionWithConfig const &rhs); //=delete

	//helpder func
	HttpBody	generateBody(std::string const &path) const;
	// void		updateHeader(HttpHeader &header) const;
public:
	explicit HttpExceptionWithConfig(HttpCode::code_e error_code, config::Config const &config);
	~HttpExceptionWithConfig() throw();
	HttpExceptionWithConfig(HttpExceptionWithConfig const &rhs);
	Response generateResponse(void) const;
};
