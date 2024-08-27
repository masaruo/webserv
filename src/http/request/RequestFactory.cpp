#include "RequestFactory.hpp"
#include "ARequest.hpp"
#include "GetRequest.hpp"
#include "PostRequest.hpp"
// #include "DeleteRequest.hpp"
#include "CgiRequest.hpp"
#include "string.hpp"
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include <sstream>
#include "AHttpBody.hpp"
#include "string.hpp"
#include "define.hpp"

ARequest	*RequestFactory::createRequest(int fd, std::string const &raw_request)
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
		//クエリがあるか？
		std::string 			uri = requestLine.getUri();
		std::string::size_type	question_pos = uri.find("?");
		if (question_pos != std::string::npos)
		{
			std::string query(uri.substr(question_pos + 1));
			header.setHeader("Content-Type", "application/x-www-form-urlencoded");
			header.setHeader("Content-Length", ft::to_string<std::string::size_type>(query.length()));
			std::istringstream	queryStream(query);
			AHttpBody body(queryStream, header);
			return (new CgiRequest(requestLine, header, body));
		}
		else
		{
			return (new GetRequest(requestLine, header));
		}

	}
	else if (method == "POST")
	{
		//body
		// return (new PostRequest(requestline, header, body));
		AHttpBody body(requestStream, header);
		return (new PostRequest(requestLine, header, body));
		// return (new CgiRequest(requestLine, header, body));//todoe delete

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
