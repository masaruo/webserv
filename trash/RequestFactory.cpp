#include "RequestFactory.hpp"
#include "HttpRequestLine.hpp"
#include "HttpHeaders.hpp"
#include "HttpGet.hpp"

std::auto_ptr<ARequest>	RequestFactory::createRequest(HttpRequestLine const &line, HttpHeaders const &header)
{
	HttpRequestLine::method_t	method = line.getMethod();

	switch (method)
	{		case HttpRequestLine::GET:
			return (std::auto_ptr<ARequest>(new HttpGet(line, header)));
		case HttpRequestLine::POST:
			//todo post
			break ;
		case HttpRequestLine::DELETE:
			//todo delete
			break ;
		default:
			//todo error
	}
}
