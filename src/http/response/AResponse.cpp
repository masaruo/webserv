#include "AResponse.hpp"

AResponse::AResponse(std::string const &uri, HttpHeader const &req_header)
:uri_(uri)
,request_header_(req_header)
,line_()
,response_header_()
,body_()
{
	return ;
}

AResponse::~AResponse()
{
	return ;
}

AResponse::AResponse(AResponse const &rhs)
:uri_(rhs.uri_)
,request_header_(rhs.request_header_)
,line_(rhs.line_)
,response_header_(rhs.response_header_)
,body_(rhs.body_)
{
	return ;
}

AResponse &AResponse::operator=(AResponse const &rhs)
{
	if (this != &rhs)
	{
		uri_ = rhs.uri_;
		request_header_ = rhs.request_header_;
		line_ = rhs.line_;
		response_header_ = rhs.response_header_;
		body_ = rhs.body_;
	}
	return (*this);
}

void	AResponse::setLine(StatusLine const &inLine)
{
	line_ = inLine;
}

void	AResponse::setHeader(HttpHeader const &inHeader)
{
	response_header_ = inHeader;
}

void	AResponse::setBody(ft::bytes_vec const &body)
{
	body_ = body;
}

void	AResponse::setBody(std::string const &body)
{
	ft::bytes_vec	tmp(body.begin(), body.end());
	body_ = tmp;
}

StatusLine	AResponse::getLine(void) const
{
	return (line_);
}

HttpHeader	AResponse::getHeader(void) const
{
	return (response_header_);
}

ft::bytes_vec	AResponse::getBody(void) const
{
	ft::bytes_vec	res;
	return (body_);
}
