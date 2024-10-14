#include "HttpCode.hpp"
#include "define.hpp"

std::map<HttpCode::StatusCode, std::string> HttpCode::StatusCodeMap_;
bool	HttpCode::is_initialized_ = false;

void	HttpCode::initialize() {
	if (!is_initialized_)
	{
		// 1xx: Informational
		StatusCodeMap_[CONTINUE] = "Continue";
		StatusCodeMap_[SWITCHING_PROTOCOLS] = "Switching Protocols";
		StatusCodeMap_[PROCESSING] = "Processing";
		StatusCodeMap_[EARLY_HINTS] = "Early Hints";

		// 2x:x: Successful
		StatusCodeMap_[OK] = "OK";
		StatusCodeMap_[CREATED] = "Created";
		StatusCodeMap_[ACCEPTED] = "Accepted";
		StatusCodeMap_[NON_AUTHORITATIVE_INFORMATION] = "Non-Authoritative Information";
		StatusCodeMap_[NO_CONTENT] = "No Content";
		StatusCodeMap_[RESET_CONTENT] = "Reset Content";
		StatusCodeMap_[PARTIAL_CONTENT] = "Partial Content";
		StatusCodeMap_[MULTI_STATUS] = "Multi-Status";
		StatusCodeMap_[ALREADY_REPORTED] = "Already Reported";
		StatusCodeMap_[IM_USED] = "IM Used";

		// 3xx: Redirection
		StatusCodeMap_[MULTIPLE_CHOICES] = "Multiple Choices";
		StatusCodeMap_[MOVED_PERMANENTLY] = "Moved Permanently";
		StatusCodeMap_[FOUND] = "Found";
		StatusCodeMap_[SEE_OTHER] = "See Other";
		StatusCodeMap_[NOT_MODIFIED] = "Not Modified";
		// msg_map_[USE_PROXY] = "Use Proxy";
		StatusCodeMap_[TEMPORARY_REDIRECT] = "Temporary Redirect";
		StatusCodeMap_[PERMANENT_REDIRECT] = "Permanent Redirect";

		// 4xx: Client Error
		StatusCodeMap_[BAD_REQUEST] = "Bad Request";
		StatusCodeMap_[UNAUTHORIZED] = "Unauthorized";
		StatusCodeMap_[PAYMENT_REQUIRED] = "Payment Required";
		StatusCodeMap_[FORBIDDEN] = "Forbidden";
		StatusCodeMap_[NOT_FOUND] = "Not Found";
		StatusCodeMap_[METHOD_NOT_ALLOWED] = "Method Not Allowed";
		StatusCodeMap_[NOT_ACCEPTABLE] = "Not Acceptable";
		StatusCodeMap_[PROXY_AUTHENTICATION_REQUIRED] = "Proxy Authentication Required";
		StatusCodeMap_[REQUEST_TIMEOUT] = "Request Timeout";
		StatusCodeMap_[CONFLICT] = "Conflict";
		StatusCodeMap_[GONE] = "Gone";
		StatusCodeMap_[LENGTH_REQUIRED] = "Length Required";
		StatusCodeMap_[PRECONDITION_FAILED] = "Precondition Failed";
		StatusCodeMap_[CONTENT_TOO_LARGE] = "Content Too Large";
		StatusCodeMap_[URI_TOO_LONG] = "URI Too Long";
		StatusCodeMap_[UNSUPPORTED_MEDIA_TYPE] = "Unsupported Media Type";
		StatusCodeMap_[RANGE_NOT_SATISFIABLE] = "Range Not Satisfiable";
		StatusCodeMap_[EXPECTATION_FAILED] = "Expectation Failed";
		StatusCodeMap_[MISDIRECTED_REQUEST] = "Misdirected Request";
		StatusCodeMap_[UNPROCESSABLE_CONTENT] = "Unprocessable Content";
		StatusCodeMap_[LOCKED] = "Locked";
		StatusCodeMap_[FAILED_DEPENDENCY] = "Failed Dependency";
		StatusCodeMap_[TOO_EARLY] = "Too Early";
		StatusCodeMap_[UPGRADE_REQUIRED] = "Upgrade Required";
		StatusCodeMap_[PRECONDITION_REQUIRED] = "Precondition Required";
		StatusCodeMap_[TOO_MANY_REQUESTS] = "Too Many Requests";
		StatusCodeMap_[REQUEST_HEADER_FIELDS_TOO_LARGE] = "Request Header Fields Too Large";
		StatusCodeMap_[UNAVAILABLE_FOR_LEGAL_REASONS] = "Unavailable For Legal Reasons";

		// 5xx: Server Error
		StatusCodeMap_[INTERNAL_SERVER_ERROR] = "Internal Server Error";
		StatusCodeMap_[NOT_IMPLEMENTED] = "Not Implemented";
		StatusCodeMap_[BAD_GATEWAY] = "Bad Gateway";
		StatusCodeMap_[SERVICE_UNAVAILABLE] = "Service Unavailable";
		StatusCodeMap_[GATEWAY_TIMEOUT] = "Gateway Timeout";
		StatusCodeMap_[HTTP_VERSION_NOT_SUPPORTED] = "HTTP Version Not Supported";
		StatusCodeMap_[VARIANT_ALSO_NEGOTIATES] = "Variant Also Negotiates";
		StatusCodeMap_[INSUFFICIENT_STORAGE] = "Insufficient Storage";
		StatusCodeMap_[LOOP_DETECTED] = "Loop Detected";
		StatusCodeMap_[NOT_EXTENDED] = "Not Extended";
		StatusCodeMap_[NETWORK_AUTHENTICATION_REQUIRED] = "Network Authentication Required";

		// webserv custome error
		StatusCodeMap_[INVALID_IN_WEBSERV] = "Custome Error";
		is_initialized_ = true;
	}
}

std::string	HttpCode::getMessage(StatusCode code)
{
	initialize();
	std::string	const	&msg = StatusCodeMap_.at(code);
	return (msg);
}

std::string	HttpCode::str(StatusCode code)
{
	std::string const	codeStr = ft::to_string<int>(code);
	std::string	const	msg = getMessage(code);

	return (codeStr + " " + msg + "\r\n");
}

HttpCode::StatusCode	HttpCode::getStatusCode(std::size_t codeNum)
{
	std::map<StatusCode, std::string>::const_iterator	iter = StatusCodeMap_.begin();
	std::map<StatusCode, std::string>::const_iterator	end = StatusCodeMap_.end();

	while (iter != end)
	{
		if (codeNum == static_cast<std::size_t>(iter->first))
			return (iter->first);
		iter++;
	}
	return (HttpCode::INVALID_IN_WEBSERV);
}

HttpCode::StatusCode	HttpCode::getStatusCode(std::string const &codeNumStr)
{
	std::size_t	codeNum = ft::stonum<std::size_t>(codeNumStr);
	return (getStatusCode(codeNum));
}
