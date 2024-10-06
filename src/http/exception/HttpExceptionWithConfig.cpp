#include "HttpExceptionWithConfig.hpp"
#include "Response.hpp"
#include "FileHandler.hpp"
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

HttpBody	HttpExceptionWithConfig::generateBody(std::string const &path) const
{
	std::string const	read = FileReader::readTextFile(path);
	HttpBody			resBody(read);
	return (resBody);
}

config::Config	HttpExceptionWithConfig::getConfig(void) const
{
	return (config_);
}

Response	HttpExceptionWithConfig::generateResponse(void) const
{
	HttpCode::code_e	error_code = HttpException::getErrorCode();
	HttpStatus	const	status(error_code);
	HttpHeader			header;
	HttpBody			body;

	bool				hasBody = false;
	std::string const	errorPath = config_.getErrorPage(error_code);
	if (!errorPath.empty())
	{
		std::string	absErrPath = config_.getRoot() + "/" + errorPath;
		body = generateBody(absErrPath);
		hasBody = true;
		header.setHeader("content-type", "text/html");
		header.setHeader("content-length", body.getSizeStr());
	}

	//todo send date
	//todo chunk = transfer-encording: chunked
	//201 created = location header
	//301 moved permantely. location header
	//302 found: location header
	//405 metdhot not allowed:: allow header
	//Connction header?

	if (hasBody)
	{
		Response	res(status, header, body);
		return (res);
	}
	else
	{
		Response	res(status, header);
		return (res);
	}
}
