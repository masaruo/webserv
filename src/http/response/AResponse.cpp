#include "AResponse.hpp"
#include "string.hpp"

AResponse::AResponse(std::string const &uri, HttpHeader const &req_header)
:uri_(uri)
,request_header_(req_header)
,code_()
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
,code_(rhs.code_)
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
		code_ = rhs.code_;
		response_header_ = rhs.response_header_;
		body_ = rhs.body_;
	}
	return (*this);
}

void	AResponse::setCode(StatusCode const &code)
{
	code_ = code;
}

void	AResponse::setHeader(HttpHeader const &header)
{
	response_header_ = header;
}

void	AResponse::setBody(HttpBody const &body)
{
	body_ = body;
}

std::string	AResponse::getUri(void) const
{
	return (uri_);
}

StatusCode	AResponse::getCode(void) const
{
	return (code_);
}

HttpHeader	AResponse::getHeader(void) const
{
	return (response_header_);
}

HttpBody	AResponse::getBody(void) const
{
	return (body_);
}

Binary::vec_bytes	AResponse::getResponse(void) const
{
	ft::string	res;
	StatusCode	status_code = getCode();
	std::string	code_num = ft::to_string<int>(status_code.getCode());
	std::string	code_str = status_code.getMessage();
	res += "HTTP/1.1 " + code_num + " " + code_str;

	HttpHeader header = getHeader();
	res += header.str();

	res += ft::string::CR + ft::string::LF;

	HttpBody	body = getBody();
	res += body.str();
	return (res.to_binary());
}
