#include "HttpException.hpp"
#include "HttpStatus.hpp"
#include "Response.hpp"
#include "FileHandler.hpp"
#include "Config.hpp"
#include <sstream>

HttpException::ErrorPageMap	HttpException::errorPageMap_;
std::string					HttpException::root_ = "";
bool						HttpException::isInitialized_ = false;
std::string					HttpException::default_error_page_ = "/error.html";
std::string					HttpException::initial_error_page_ = "./www/error.html";

//! HttpException
HttpException::HttpException(HttpCode::StatusCode error_code)
:std::runtime_error(HttpCode::str(error_code))
,errorCode_(error_code)
{
	return ;
}

HttpException::~HttpException() throw ()
{
	return ;
}

HttpException::HttpException(HttpException const &rhs)
:std::runtime_error(rhs)
,errorCode_(rhs.errorCode_)
{
	return ;
}

void	HttpException::loadErrorPageMap(config::Config const &config)
{
	if (!isInitialized_)
	{
		root_ = config.getRoot();
		errorPageMap_ = config.getErrorPageMap();
		isInitialized_ = true;
	}
}

HttpBody	HttpException::generateBody(void) const
{
	std::string										errorPath = "";
	config::Config::ErrorPageMap::const_iterator	it = errorPageMap_.begin();
	config::Config::ErrorPageMap::const_iterator	end = errorPageMap_.end();
	it = errorPageMap_.find(errorCode_);

	if (it == end)
	{
		if (isInitialized_)
			errorPath = root_ + default_error_page_;
		else
			errorPath = initial_error_page_;
	}
	else
	{
		errorPath = root_ + errorPageMap_.at(errorCode_);
	}
	std::string contents = FileHandler::read(errorPath);//todo sstream
	HttpBody body(contents);
	return (body);
}

Response	HttpException::generateResponse(void) const
{

	HttpBody const &body = generateBody();

	HttpHeader	header;
	header.addValue("content-type", "text/html");
	header.addValue("content-length", body.getSizeStr());

	HttpStatus	status(errorCode_);

	Response	response(status, header, body);

	return (response);
}
