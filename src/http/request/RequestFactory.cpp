#include <sstream>
#include "RequestFactory.hpp"
#include "ARequest.hpp"
#include "GetRequest.hpp"
#include "PostRequest.hpp"
#include "string.hpp"
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include "PutRequest.hpp"
#include "define.hpp"
#include "DeleteRequest.hpp"

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
	else if (method == "POST" || method == "DELETE")
	{
		std::size_t len = ft::stonum<std::size_t>(header.getHeader("Content-Length"));
		HttpBody body(requestStream, len);
		if (method == "POST")
			return (new PostRequest(requestLine, header, body));
		else
			return (new DeleteRequest(requestLine, header, body));

	}
	else if (method == "PUT")
	{
		std::size_t len = ft::stonum<std::size_t>(header.getHeader("Content-Length"));
		HttpBody body(requestStream, len);
		return (new PutRequest(requestLine, header, body));	
	}
	else
	{
		return (NULL);
	}
}
