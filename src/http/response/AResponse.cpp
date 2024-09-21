#include "AResponse.hpp"
#include "string.hpp"

AResponse::AResponse(ft::unique_ptr<ARequest> request)
:request_(request)
{

}

AResponse::~AResponse()
{
	return ;
}

AResponse::AResponse(AResponse const &rhs)
:code_(rhs.code_)
,header_(rhs.header_)
,body_(rhs.body_)
{
	request_.reset(RequestFactory::createRequest(rhs.request_.get()));
}

AResponse &AResponse::operator=(AResponse const &rhs)
{
	if (this != &rhs)
	{
		request_.reset(RequestFactory::createRequest(rhs.request_.get()));
		code_ = rhs.code_;
		header_ = rhs.header_;
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
	header_ = header;
}

void	AResponse::setBody(HttpBody const &body)
{
	body_ = body;
}

RequestLine	AResponse::getRequestLine(void) const
{
	return (request_->getLine());
}

HttpHeader	AResponse::getRequestHeader(void) const
{
	return (request_->getHeader());
}

HttpBody	AResponse::getRequestBody(void) const
{
	return (request_->getBody());
}

std::string	AResponse::getUri(void) const
{
	return (request_->getLine().getUri());
}

StatusCode	AResponse::getCode(void) const
{
	return (code_);
}

HttpHeader	AResponse::getHeader(void) const
{
	return (header_);
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
	if (body.getSize() != 0)
		res += body.str();
	return (res.to_binary());
}

AResponse::ResponseException::ResponseException(std::string const &msg)
:std::runtime_error(msg)
{
	return ;
}
