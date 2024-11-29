#include "Request.hpp"
#include "Config.hpp"

Request::Request(RequestLine const &line, HttpHeader const &header, Server &server)
:line_(line), header_(header), server_(server),hasBody_(false)
{
	return ;
}

Request::Request(RequestLine const &line, HttpHeader const &header, HttpBody const &body, Server &server)
:line_(line), header_(header), body_(body), server_(server), hasBody_(true)
{
	return ;
}

Request::Request(Request const &rhs)
:line_(rhs.line_), header_(rhs.header_), body_(rhs.body_), server_(rhs.server_), hasBody_(rhs.hasBody_)
{
	return ;
}

Request::~Request()
{
	return ;
}

// Request	&Request::operator=(Request const &rhs)
// {
// 	if (this != &rhs)
// 	{
// 		line_ = rhs.line_;
// 		header_ = rhs.header_;
// 		body_ = rhs.body_;
// 		server_ = rhs.server_;
// 		hasBody_ = rhs.hasBody_;
// 	}
// 	return (*this);
// }

// void	Request::assertAllowedMethod(void) const
// {
// 	std::string const &method = getLine().getMethod();
// 	std::string const &path = getLine().getUri().getPath();
// 	config::Config::LocationConfig const &loc = server_.getConfigFactory().getConfig().getConfigLocation(path);
// 	if (line_.getMethod() != "GET" && line_.getMethod() != "POST")
// 		throw (HttpException(HttpCode::METHOD_NOT_ALLOWED));
// }

config::Config const	Request::getConfig(void) const
{
	return (server_.getConfigFactory().getConfig(line_.getUri().getHost()));
}

bool	Request::hasBody(void) const
{
	return (hasBody_);
}

RequestLine const	&Request::getLine(void) const
{
	return (line_);
}

HttpHeader const	&Request::getHeader(void) const
{
	return (header_);
}

HttpBody const		&Request::getBody(void) const
{
	return (body_);
}
