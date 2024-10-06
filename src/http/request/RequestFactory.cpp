#include "RequestFactory.hpp"
#include "ARequest.hpp"
#include "GetRequest.hpp"
#include "PostRequest.hpp"
#include "DeleteRequest.hpp"
#include "CgiRequest.hpp"
#include "string.hpp"
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include "PutRequest.hpp"
#include "define.hpp"
#include "ConnectionHandler.hpp"
#include "HttpException.hpp"
#include <sstream>

ARequest	*RequestFactory::createRequest(int fd, config::ConfigFactory const &config_factory)
{
	std::string	raw_request = ConnectionHandler::recvData(fd, 6000);//todo buff size
	std::istringstream	requestStream(raw_request);
	RequestLine	requestLine(requestStream);
	HttpHeader	header(requestStream);

	std::string	host_value = header.getFirstValue("host");

	config::Config	config = config_factory.getConfig(host_value);

	HttpUri &uri = requestLine.getUriReference();
	uri.updateWithHostHeader(host_value);

	std::string	const	method = requestLine.getMethod();
	if (method == "GET")
	{
		return (new GetRequest(requestLine, header, config));
	}
	else if (method == "DELETE")
	{
		return (new DeleteRequest(requestLine, header, config));
	}
	else if (method == "POST" || method == "PUT")
	{
		std::string bodyStr = raw_request.substr(raw_request.rfind("\r\n\r\n") + 4);
		bodyStr += ConnectionHandler::recvData(fd, 6000, header.getContentLen() - bodyStr.size());
		std::istringstream	bodyStream(bodyStr);
		HttpBody body(bodyStream, header);
		if (method == "POST")
		{
			return (new PostRequest(requestLine, header, body, config));
		}
		else
			return (new PutRequest(requestLine, header, body, config));
	}
	else
	{
		throw (HttpException(HttpCode::BAD_REQUEST));
	}
}
