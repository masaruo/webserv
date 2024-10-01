#include "RequestLine.hpp"
#include "string.hpp"
#include "HttpStatus.hpp"

static void	assertRequestLine(std::string const &buf)
{
	ft::string	line(buf);
	bool		is_badReqeust = false;

	if (line.empty())
		is_badReqeust = true;
	if (!line.end_with(ft::string::CR))// CR not at the end of the linst
		is_badReqeust = true;
	line.pop_back();// get rid of CR at the end of the line
	if (line.has(ft::string::CR))// CR in the middle of line
		is_badReqeust = true;
}

RequestLine::RequestLine(std::istringstream &iss)
:method_(), uri_(), version_()
{
	std::string	buf;
	std::getline(iss, buf);
	assertRequestLine(buf);
	ft::string	to_split(buf);
	to_split.trim(ft::string::CR);
	ft::string::string_vector	split_by_sp = to_split.split(ft::string::WS);
	if (split_by_sp.size() != 3 || split_by_sp.at(0).empty() || split_by_sp.at(1).empty() || split_by_sp.at(2).empty())
		throw (HttpStatus::HttpException(HttpCode::BAD_REQUEST));
	setMethod(split_by_sp.at(0));
	setUri(split_by_sp.at(1));
	setVersion(split_by_sp.at(2));
}

RequestLine::~RequestLine()
{
	return ;
}

RequestLine::RequestLine(RequestLine const &rhs)
:method_(rhs.method_)
,uri_(rhs.uri_)
,version_(rhs.version_)
{
	return ;
}

RequestLine &RequestLine::operator=(RequestLine const &rhs)
{
	if (this != &rhs)
	{
		method_ = rhs.method_;
		uri_ = rhs.uri_;
		version_ = rhs.version_;
	}
	return (*this);
}

void	RequestLine::setMethod(std::string const &inMethod)
{
	if (inMethod != "GET" && inMethod != "POST" && inMethod != "DELETE" && inMethod != "PUT")
		throw (HttpStatus::HttpException(HttpCode::BAD_REQUEST));
	method_ = inMethod;
}

void	RequestLine::setUri(std::string const &inUri)
{
	uri_.init(inUri);
}

void	RequestLine::setVersion(std::string const &inVer)
{
	if (inVer != "HTTP/1.1")
		throw (HttpStatus::HttpException(HttpCode::BAD_REQUEST));
	version_ = inVer;
}

std::string	RequestLine::getMethod(void) const
{
	return (method_);
}

HttpUri	RequestLine::getUri(void) const
{
	return (uri_);
}

HttpUri	&RequestLine::getUriReference(void)
{
	return (uri_);
}

std::string RequestLine::getVersion(void) const
{
	return (version_);
}
