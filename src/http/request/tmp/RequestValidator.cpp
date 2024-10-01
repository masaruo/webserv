#include "RequestValidator.hpp"
#include "HttpStatus.hpp"

static void	assertRequestLine(RequestLine const &line, config::Config const &config)
{
	std::string const	method = line.getMethod();
	// std::string const	uri = line.getUri();
	HttpUri const		uri = line.getUri();
	std::string const	version = line.getVersion();

	if (!config.isAllowedMethod(uri.getPath(), method))
		throw (HttpStatus::HttpStatusException(HttpCode::METHOD_NOT_ALLOWED));
	if (version != "HTTP/1.1")
		throw (HttpStatus::HttpStatusException(HttpCode::HTTP_VERSION_NOT_SUPPORTED));
}

static void	assertRequestHeader(HttpHeader const &header, RequestLine const &line, config::Config const &config)
{
	if (!header.hasHeader("Host"))
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	std::string const	method = line.getMethod();
	if (method == "POST" || method == "PUT")
	{
		if (!header.hasHeader("Content-Length"))
			throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
		try
		{
			ft::stonum<std::size_t>(header.getFirstValue("Content-Length"));
		}
		catch(std::invalid_argument const &e)
		{
			throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
		}
		// if (!header.hasHeader("Transfer-Encoding"))
		// 	throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	}

}

static void	assertRequestBody(HttpBody const &body, RequestLine const &line, HttpHeader const &header, config::Config const &config)
{
	if (body.getSize() != header.getContentLen())
	//todo throw
}

void	RequestValidator::assertRequest(ARequest const &request)
{
	RequestLine const		&line = request.getLine();
	HttpHeader const		&header = request.getHeader();
	HttpBody const			&body = request.getBody();
	config::Config const	&config = request.getConfig();

	assertRequestLine(line, config);
	assertRequestHeader(header, line, config);
	assertRequestBody(body, line, header, config);
}
