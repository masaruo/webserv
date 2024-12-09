#include "RequestLine.hpp"
#include "string.hpp"
#include "HttpException.hpp"

static void	assertRequestLine(std::string const &buf)
{
	ft::string	line(buf);
	bool		is_badReqeust = false;

	if (line.empty())
		is_badReqeust = true;
	if (!line.end_with_str(ft::string::CRLF))
		is_badReqeust = true;
	line.pop_back();
	line.pop_back();
	if (line.empty() || line.has(ft::string::CR))// CR in the middle of line
		is_badReqeust = true;

	if (is_badReqeust)
		throw (HttpException(HttpCode::BAD_REQUEST));
}

RequestLine::RequestLine(std::string const &line)
{
	assertRequestLine(line);
	ft::string	to_split(line);
	to_split.trim(ft::string::CRLF);
	ft::string::string_vector	split_by_sp = to_split.split(ft::string::WS);

	std::string method, uri, version;
	if (split_by_sp.size() == 2 && !split_by_sp.at(0).empty() && !split_by_sp.at(1).empty())
	{
		method = split_by_sp.at(0);
		uri = "/";
		version = split_by_sp.at(1);
	}
	else if (split_by_sp.size() == 3 && !split_by_sp.at(0).empty() && !split_by_sp.at(1).empty() && !split_by_sp.at(2).empty())
	{
		method = split_by_sp.at(0);
		uri = split_by_sp.at(1);
		version = split_by_sp.at(2);
	}
	else
		throw (HttpException(HttpCode::BAD_REQUEST));

	setMethod(method);
	setUri(uri);
	setVersion(version);	
}

RequestLine::RequestLine()
:method_()
,uri_()
,version_()
{
	return ;
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
		throw (HttpException(HttpCode::BAD_REQUEST));
	method_ = inMethod;
}

void	RequestLine::setUri(std::string const &inUri)
{
	uri_.init(inUri);
}

void	RequestLine::setVersion(std::string const &inVer)
{
	if (inVer != "HTTP/1.1")
		throw (HttpException(HttpCode::HTTP_VERSION_NOT_SUPPORTED));
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
