#include "Response.hpp"
#include "string.hpp"
#include "Date.hpp"
#include <sstream>

Response::Response()
:status_()
,header_()
,body_()
,has_body_(false)
{
	return ;
}

Response::Response(HttpStatus const &status)
:status_(status)
,header_()
,body_()
,has_body_(false)
{
	return ;
}

Response::Response(HttpStatus const &status, ResponseHeader const &header)
:status_(status)
,header_(header)
,body_()
,has_body_(false)
{
	return ;
}

Response::Response(HttpStatus const &status, ResponseHeader const &header, HttpBody const &body)
:status_(status)
,header_(header)
,body_(body)
,has_body_(true)
{
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

void	Response::setHeader(ResponseHeader const &header)
{
	header_ = header;
}

void	Response::setBody(HttpBody const &body)
{
	body_ = body;
}

void	Response::addMandetaryHeader(void)
{
	header_.AHeader::add(AHeader::CONNECTION, "close");
	header_.AHeader::add(AHeader::SERVER, "42Webserv/1.0");

	std::string const &now = Date::time();
	header_.AHeader::add(AHeader::DATE, now);

	if (status_.getCode() == HttpCode::NO_CONTENT && header_.hasKey(AHeader::CONTENT_LENGTH))
		header_.del(AHeader::CONTENT_LENGTH);

	if (has_body_)
	{
		if (!header_.hasKey(AHeader::CONTENT_LENGTH))
			header_.AHeader::add(AHeader::CONTENT_LENGTH, body_.size());

		if (!header_.hasKey(AHeader::CONTENT_TYPE))
			header_.AHeader::add(AHeader::CONTENT_TYPE, "application/octet-stream");
	}
}

std::string	Response::to_string(void)
{
	addMandetaryHeader();

	std::stringstream	ss;

	ss << status_.to_string();
	ss << header_.to_string();
	ss << ft::string::CR +ft::string::LF;
	if (has_body_)
		ss << body_.to_string();
	return (ss.str());
}
