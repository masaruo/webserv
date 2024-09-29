#include "Response.hpp"
#include "string.hpp"
#include <sstream>

Response::Response(HttpStatus const &status, HttpHeader const &header)
:status_(status)
,header_(header)
,body_()
,has_body_(false)
{
	return ;
}

Response::Response(HttpStatus const &status, HttpHeader const &header, HttpBody const &body)
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

void	Response::setHeader(HttpHeader const &header)
{
	header_ = header;
}

void	Response::setBody(HttpBody const &body)
{
	body_ = body;
}

HttpStatus	Response::getStatus(void) const
{
	return (status_);
}

HttpHeader	Response::getHeader(void) const
{
	return (header_);
}

HttpBody	Response::getBody(void) const
{
	return (body_);
}

std::string	Response::generateResponse(void) const
{
	std::ostringstream	oss;

	oss << status_.to_stdstring();
	oss << header_.to_stdstring();
	oss << ft::string::CR +ft::string::LF;
	if (has_body_)
		oss << body_.to_stdstring();
	// ft::string	res;
	// HttpStatus	status_code = getStatus();
	// std::string	code_num = ft::to_string<int>(status_code.getCode());

	// std::string statusStr = status_code.to_stdstring();
	// res += statusStr;

	// HttpHeader header = getHeader();
	// res += header.str();

	// res += ft::string::CR + ft::string::LF;

	// HttpBody	body = getBody();
	// if (body.getSize() != 0)
	// 	res += body.data();
	// return (res.str());

}
