#include <sstream>
#include "RequestFactory.hpp"
#include "ARequest.hpp"
#include "GetRequest.hpp"
#include "PostRequest.hpp"
// #include "DeleteRequest.hpp"
// #include "CgiRequest.hpp"
#include "string.hpp"
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
// #include "AHttpBody.hpp"
#include "define.hpp"

ARequest	*RequestFactory::createRequest(int fd, std::string const &raw_request)
{
	std::istringstream	requestStream(raw_request);
	RequestLine	requestLine(requestStream);
	HttpHeader	header(requestStream);

	std::string	method = requestLine.getMethod();
	if (method == "GET")
	{
		return (new GetRequest(requestLine, header));
	}
	else if (method == "POST")
	{
		//body
		// return (new PostRequest(requestline, header, body));
		// AHttpBody body(requestStream, header);
		// return (new PostRequest(requestLine, header, body));
		std::size_t len = ft::stonum<std::size_t>(header.getHeader("Content-Length"));
		HttpBody body(requestStream, len);
		// return (new CgiRequest(requestLine, header, body));//todoe delete
		return (new PostRequest(requestLine, header, body));

	}
	else if (method == "DELETE")
	{
		//body
		//todo implement
		return (NULL);
	}
	else
	{
		return (NULL);
	}
}
