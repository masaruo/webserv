#include "RequestValidator.hpp"
#include "HttpStatus.hpp"

// static void	assertRequestLineMethod(std::string const &method)

static void	assertRequestLine(RequestLine const &line, HttpHeader const &header, config::Config const &config)
{
	std::string const	method = line.getMethod();

	if ()

	std::string const	uri = line.getUri();
	std::string const	version = line.getVersion();
}

static void	assertRequestHeader(HttpHeader const &header, RequestLine const &line, config::Config const &config)
{

}

static void	assertRequestBody(HttpBody const &body, RequestLine const &line, HttpHeader const &header, config::Config const &config)
{

}

void	RequestValidator::assertRequest(ARequest const &request)
{
	RequestLine const		&line = request.getLine();
	HttpHeader const		&header = request.getHeader();
	HttpBody const			&body = request.getBody();
	config::Config const	&config = request.getConfig();

	assertRequestLine(line, header, config);
	assertRequestHeader(header, line, config);
	assertRequestBody(body, line, header, config);
}
