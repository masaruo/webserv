#include "RequestFactory.hpp"
#include "ARequest.hpp"
#include "GetRequest.hpp"
#include "PostRequest.hpp"
// #include "DeleteRequest.hpp"
#include "string.hpp"
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include <sstream>
#include "AHttpBody.hpp"

ARequest	*RequestFactory::createRequest(std::string const &raw_request)
{
	std::istringstream	requestStream(raw_request);
	std::string			line;
	std::getline(requestStream, line);
	RequestLine	requestLine(line);
	HttpHeader	header;
	while (true)
	{
		std::getline(requestStream, line);
		if (line.empty() || line == ft::string::CR)
			break ;
		header.setHeader(line);
	}

	std::string	method = requestLine.getMethod();
	if (method == "GET")
	{
		return (new GetRequest(requestLine, header));
	}
	else if (method == "POST")
	{
		//body
		// return (new PostRequest(requestline, header, body));
		AHttpBody body(requestStream, header);
		return (new PostRequest(requestLine, header, body));
	}
	else if (method == "DELETE")
	{
		//body
		return (NULL);
	}
	else
	{
		return (NULL);
	}
}
