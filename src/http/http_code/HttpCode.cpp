#include "HttpCode.hpp"
#include "define.hpp"

std::map<HttpCode::code_e, std::string> HttpCode::msg_map_;
bool	HttpCode::is_initialized_ = false;

void	HttpCode::initialize() {
	if (!is_initialized_)
	{
		// 1xx: Informational
		msg_map_[CONTINUE] = "Continue";
		msg_map_[SWITCHING_PROTOCOLS] = "Switching Protocols";
		msg_map_[PROCESSING] = "Processing";
		msg_map_[EARLY_HINTS] = "Early Hints";

		// 2x:x: Successful
		msg_map_[OK] = "OK";
		msg_map_[CREATED] = "Created";
		msg_map_[ACCEPTED] = "Accepted";
		msg_map_[NON_AUTHORITATIVE_INFORMATION] = "Non-Authoritative Information";
		msg_map_[NO_CONTENT] = "No Content";
		msg_map_[RESET_CONTENT] = "Reset Content";
		msg_map_[PARTIAL_CONTENT] = "Partial Content";
		msg_map_[MULTI_STATUS] = "Multi-Status";
		msg_map_[ALREADY_REPORTED] = "Already Reported";
		msg_map_[IM_USED] = "IM Used";

		// 3xx: Redirection
		msg_map_[MULTIPLE_CHOICES] = "Multiple Choices";
		msg_map_[MOVED_PERMANENTLY] = "Moved Permanently";
		msg_map_[FOUND] = "Found";
		msg_map_[SEE_OTHER] = "See Other";
		msg_map_[NOT_MODIFIED] = "Not Modified";
		// msg_map_[USE_PROXY] = "Use Proxy";
		msg_map_[TEMPORARY_REDIRECT] = "Temporary Redirect";
		msg_map_[PERMANENT_REDIRECT] = "Permanent Redirect";

		// 4xx: Client Error
		msg_map_[BAD_REQUEST] = "Bad Request";
		msg_map_[UNAUTHORIZED] = "Unauthorized";
		msg_map_[PAYMENT_REQUIRED] = "Payment Required";
		msg_map_[FORBIDDEN] = "Forbidden";
		msg_map_[NOT_FOUND] = "Not Found";
		msg_map_[METHOD_NOT_ALLOWED] = "Method Not Allowed";
		msg_map_[NOT_ACCEPTABLE] = "Not Acceptable";
		msg_map_[PROXY_AUTHENTICATION_REQUIRED] = "Proxy Authentication Required";
		msg_map_[REQUEST_TIMEOUT] = "Request Timeout";
		msg_map_[CONFLICT] = "Conflict";
		msg_map_[GONE] = "Gone";
		msg_map_[LENGTH_REQUIRED] = "Length Required";
		msg_map_[PRECONDITION_FAILED] = "Precondition Failed";
		msg_map_[CONTENT_TOO_LARGE] = "Content Too Large";
		msg_map_[URI_TOO_LONG] = "URI Too Long";
		msg_map_[UNSUPPORTED_MEDIA_TYPE] = "Unsupported Media Type";
		msg_map_[RANGE_NOT_SATISFIABLE] = "Range Not Satisfiable";
		msg_map_[EXPECTATION_FAILED] = "Expectation Failed";
		msg_map_[MISDIRECTED_REQUEST] = "Misdirected Request";
		msg_map_[UNPROCESSABLE_CONTENT] = "Unprocessable Content";
		msg_map_[LOCKED] = "Locked";
		msg_map_[FAILED_DEPENDENCY] = "Failed Dependency";
		msg_map_[TOO_EARLY] = "Too Early";
		msg_map_[UPGRADE_REQUIRED] = "Upgrade Required";
		msg_map_[PRECONDITION_REQUIRED] = "Precondition Required";
		msg_map_[TOO_MANY_REQUESTS] = "Too Many Requests";
		msg_map_[REQUEST_HEADER_FIELDS_TOO_LARGE] = "Request Header Fields Too Large";
		msg_map_[UNAVAILABLE_FOR_LEGAL_REASONS] = "Unavailable For Legal Reasons";

		// 5xx: Server Error
		msg_map_[INTERNAL_SERVER_ERROR] = "Internal Server Error";
		msg_map_[NOT_IMPLEMENTED] = "Not Implemented";
		msg_map_[BAD_GATEWAY] = "Bad Gateway";
		msg_map_[SERVICE_UNAVAILABLE] = "Service Unavailable";
		msg_map_[GATEWAY_TIMEOUT] = "Gateway Timeout";
		msg_map_[HTTP_VERSION_NOT_SUPPORTED] = "HTTP Version Not Supported";
		msg_map_[VARIANT_ALSO_NEGOTIATES] = "Variant Also Negotiates";
		msg_map_[INSUFFICIENT_STORAGE] = "Insufficient Storage";
		msg_map_[LOOP_DETECTED] = "Loop Detected";
		msg_map_[NOT_EXTENDED] = "Not Extended";
		msg_map_[NETWORK_AUTHENTICATION_REQUIRED] = "Network Authentication Required";

		is_initialized_ = true;
	}
}

std::string	HttpCode::getMessage(code_e code)
{
	initialize();
	std::string	const	msg = msg_map_.at(code);
	return (msg);
}

std::string	HttpCode::str(code_e code)
{
	std::string const	codeStr = ft::to_string<int>(code);
	std::string	const	msg = getMessage(code);

	return (codeStr + " " + msg + "\r\n");
}
