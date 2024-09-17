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
#include "ConnectionHandler.hpp"

ARequest	*RequestFactory::createRequest(int fd)
{
	std::string	raw_request = ConnectionHandler::recvData(fd, 6000);//todo buff size
	std::istringstream	requestStream(raw_request);
	RequestLine	requestLine(requestStream);
	HttpHeader	header(requestStream);

	std::string	method = requestLine.getMethod();
	if (method == "GET")
	{
		return (new GetRequest(requestLine, header));
	}
	else if (method == "POST" || method == "DELETE" || method == "PUT")
	{
		std::size_t len = ft::stonum<std::size_t>(header.getHeader("Content-Length"));
		std::string bodyStr = ConnectionHandler::recvData(fd, 6000, len);
		std::istringstream	bodyStream(bodyStr);
		HttpBody body(bodyStream);
		if (method == "POST")
			return (new PostRequest(requestLine, header, body));
		else if (method == "DELETE")
			return (new DeleteRequest(requestLine, header, body));
		else
			return (new PutRequest(requestLine, header, body));
	}
	else
	{
		return (NULL);
	}
}
