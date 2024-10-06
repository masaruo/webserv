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
protected:
	config::Config	getConfig(void) const;
public:
	explicit HttpExceptionWithConfig(HttpCode::code_e error_code, config::Config const &config);
	virtual ~HttpExceptionWithConfig() throw();
	HttpExceptionWithConfig(HttpExceptionWithConfig const &rhs);
	virtual Response	generateResponse(void) const;
};
