#include "HttpExceptionWithConfig.hpp"
#include "Response.hpp"
#include <sstream>

HttpExceptionWithConfig::HttpExceptionWithConfig(HttpCode::code_e error_code, config::Config const &config)
:HttpException(error_code)
,config_(config)
{
	return ;
}

HttpExceptionWithConfig::~HttpExceptionWithConfig() throw ()
{
	return ;
}

HttpExceptionWithConfig::HttpExceptionWithConfig(HttpExceptionWithConfig const &rhs)
:HttpException(rhs)
,config_(rhs.config_)
{
	return ;
}

static HttpBody	generateBody(std::string const &path)
{
	//todo 
}

static HttpHeader	generateHeader(std::size_t body_length)
{
	//todo
}

Response	HttpExceptionWithConfig::generateResponse(void) const
{
	HttpCode::code_e	error_code = HttpException::getErrorCode();


	//todo 401 error et al = create body
	//todo create header according to error code
}
