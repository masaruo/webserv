#pragma once
#include "HttpException.hpp"
#include "Config.hpp"
#include <stdexcept>

class HttpExceptionWithConfig : public HttpException
{
private:
	config::Config config_;
	HttpExceptionWithConfig();												//=delete
	HttpExceptionWithConfig &operator=(HttpExceptionWithConfig const &rhs); //=delete
public:
	explicit HttpExceptionWithConfig(HttpCode::code_e error_code, config::Config const &config);
	~HttpExceptionWithConfig() throw();
	HttpExceptionWithConfig(HttpExceptionWithConfig const &rhs);
	Response generateResponse(void) const;
};
