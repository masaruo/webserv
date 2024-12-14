#pragma once
#include "HttpCode.hpp"
#include <stdexcept>

namespace config
{
	class Config;
}
class Response;
class HttpBody;

class HttpException : public std::runtime_error
{
public:
	typedef std::map<HttpCode::StatusCode, std::string> ErrorPageMap;
private:
	HttpCode::StatusCode 				errorCode_;
	static ErrorPageMap					errorPageMap_;
	static std::string					root_;
	static bool							isInitialized_;
	static std::string					default_error_page_;
	HttpException();//=delete
	HttpException &operator=(HttpException const &rhs);//=delete
public:
	explicit HttpException(HttpCode::StatusCode error_code);
	HttpException(HttpException const &rhs);
	~HttpException() throw();
	static void				loadErrorPageMap(config::Config const &config);
	HttpBody				generateBody(void) const;
	Response				generateResponse(void) const;
	HttpCode::StatusCode	getErrorCode(void) const;
};
