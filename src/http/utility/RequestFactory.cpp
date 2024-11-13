#include "RequestFactory.hpp"
#include "define.hpp"
#include "HttpHeader.hpp"
#include "GetRequest.hpp"
#include "PostRequest.hpp"
#include "DeleteRequest.hpp"
#include "RequestLine.hpp"
#include "PutRequest.hpp"
// #include "IO.class.hpp"
#include "HttpException.hpp"
#include <sstream>

// int const	RequestFactory::HASCHUNK = 1;
// int const	RequestFactory::HASBODY = 2;
// int const	RequestFactory::NOBODY = 0;

ARequest	*RequestFactory::createRequest(int fd, config::ConfigFactory const &config_factory)
{
	// io::IO	input(fd);
	// std::string	raw_request = input.recv();
	// std::istringstream	requestStream(raw_request);
	// // RequestLine	requestLine(requestStream);
	// HttpHeader	header(requestStream);

	// std::string	host_value = header.getFirstValue("host");
	// config::Config	config = config_factory.getConfig(host_value);

	// HttpException::loadErrorPageMap(config);

	// HttpUri &uri = requestLine.getUriReference();
	// uri.updateWithHostHeader(host_value);

	// std::string	const	method = requestLine.getMethod();
	// if (method == "GET")
	// {
	// 	return (new GetRequest(requestLine, header, config));
	// }
	// else if (method == "DELETE")
	// {
	// 	return (new DeleteRequest(requestLine, header, config));
	// }
	// else if (method == "POST" || method == "PUT")
	// {
	// 	std::string bodyStr;
	// 	if (header.hasKey("transfer-encoding") && header.getLastValue("transfer-encoding") == "chunked")
	// 		bodyStr = input.recv("chunked");//* chunkの読み取り
	// 	else
	// 		bodyStr = input.recv(header.getContentLen());
	// 	HttpBody	body(bodyStr);
	// 	if (method == "POST")
	// 	{
	// 		return (new PostRequest(requestLine, header, body, config));
	// 	}
	// 	else
	// 		return (new PutRequest(requestLine, header, body, config));
	// }
	// else
	// {
	// 	throw (HttpException(HttpCode::BAD_REQUEST));
	// }
}

void	RequestFactory::createRequestLineAndHeader(int fd, RequestLine &line, HttpHeader &header)
{
	// io::IO				input(fd);
	// std::string			raw_request = input.recv();
	// std::istringstream	requestStream(raw_request);
	// RequestLine			tmpline(requestStream);
	// HttpHeader			tmpheader(requestStream);

	// std::string	host_value = tmpheader.getFirstValue("host");

	// //todo error page
	// // config::Config	config = config_factory.getConfig(host_value);
	// // HttpException::loadErrorPageMap(config);

	// HttpUri &uri = tmpline.getUriReference();
	// uri.updateWithHostHeader(host_value);

	// line = tmpline;
	// header = tmpheader;
}

// int	RequestFactory::hasBody(HttpHeader const &header)
// {
// 	if (header.hasKey("transfer-encoding") && header.getLastValue("transfer-encoding") == "chunked")
// 		return (RequestFactory::HASCHUNK);
// 	else if (header.hasKey("content-length") && header.getContentLen() > 0)
// 		return (RequestFactory::HASBODY);
// 	else 
// 		return (RequestFactory::NOBODY);
// }

