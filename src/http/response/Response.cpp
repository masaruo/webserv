#include "Response.hpp"
#include "string.hpp"
#include "Date.hpp"
#include <sstream>

Response::Response(HttpStatus const &status, HttpHeader const &header)
:status_(status)
,header_(header)
,body_()
,has_body_(false)
{
	addMandetaryHeader();
	return ;
}

Response::Response(HttpStatus const &status, HttpHeader const &header, HttpBody const &body)
:status_(status)
,header_(header)
,body_(body)
,has_body_(true)
{
	addMandetaryHeader();
	return ;
}

Response::~Response()
{
	return ;
}

Response::Response(Response const &rhs)
:status_(rhs.status_)
,header_(rhs.header_)
,body_(rhs.body_)
,has_body_(rhs.has_body_)
{
	return ;
}

Response &Response::operator=(Response const &rhs)
{
	if (this != &rhs)
	{
		status_ = rhs.status_;
		header_ = rhs.header_;
		body_ = rhs.body_;
		has_body_ = rhs.has_body_;
	}
	return (*this);
}

void	Response::setStatus(HttpStatus const &status)
{
	status_ = status;
}

void	Response::setHeader(HttpHeader const &header)
{
	header_ = header;
}

void	Response::setBody(HttpBody const &body)
{
	body_ = body;
}

void	Response::addMandetaryHeader(void)
{
	header_.addValue(HttpHeader::CONNECTION, "close");

	std::string const &now = Date::time();
	header_.addValue(HttpHeader::DATE, now);
}

std::string	Response::to_string(void) const
{
	std::stringstream	ss;

	ss << status_.to_string();
	ss << header_.to_string();
	ss << ft::string::CR +ft::string::LF;
	if (has_body_)
		ss << body_.to_string();
	return (ss.str());
}
