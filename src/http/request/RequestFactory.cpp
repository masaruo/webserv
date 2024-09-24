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

ARequest	*RequestFactory::createRequest(int fd, config::ConfigFactory const &config_factory)
{
	std::string	raw_request = ConnectionHandler::recvData(fd, 6000);//todo buff size
	std::istringstream	requestStream(raw_request);
	RequestLine	requestLine(requestStream);
	HttpHeader	header(requestStream);
	config::Config	config = config_factory.getConfig(header.getHeader("Host"));

	std::string	method = requestLine.getMethod();
	if (method == "GET")
	{
		return (new GetRequest(requestLine, header, config));
	}
	else if (method == "POST" || method == "DELETE" || method == "PUT")
	{
		std::size_t len = ft::stonum<std::size_t>(header.getHeader("Content-Length"));
		std::string bodyStr = raw_request.substr(raw_request.rfind("\r\n\r\n") + 4);
		bodyStr += ConnectionHandler::recvData(fd, 6000, len);
		std::istringstream	bodyStream(bodyStr);
		HttpBody body(bodyStream);
		if (method == "POST")
			return (new PostRequest(requestLine, header, body, config));
		else if (method == "DELETE")
			return (new DeleteRequest(requestLine, header, body, config));
		else
			return (new PutRequest(requestLine, header, body, config));
	}
	else
	{
		return (NULL);
	}
}

ARequest	*RequestFactory::createRequest(ARequest *request)
{
	std::string const	method = request->getLine().getMethod();
	RequestLine const	line = request->getLine();
	HttpHeader const	header = request->getHeader();
	HttpBody const		body = request->getBody();
	config::Config const config = request->getConfig();

	if (method == "GET")
	{
		return (new GetRequest(line, header, config));
	}
	else if (method == "POST")
	{
		return (new PostRequest(line, header, body, config));
	}
	else if (method == "DELETE")
	{
		return (new DeleteRequest(line, header, body, config));
	}
	else if (method == "PUT")
	{
		return (new PutRequest(line, header, body, config));
	}
	else
	{
		return (NULL);
	}
}

// RequestFactory::RequestFactoryException::RequestFactoryException(std::string const &msg)
// :std::runtime_error(msg)
// {
// 	return ;
// }
