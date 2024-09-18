#include "RequestLine.hpp"
#include "string.hpp"

RequestLine::RequestLine(std::istringstream &iss)
:method_(), uri_(), version_()
{
	std::string	line;
	while (true)
	{
		std::getline(iss, line);
		if (line != ft::string::CRLF)
			break ;
	}
	if (line.empty())
	{
		RequestLineException("Failed to parse request line at 16");
	}
	ft::string	to_split(line);
	to_split.trim(ft::string::CRLF);
	ft::string::string_vector	split_by_sp = to_split.split(ft::string::WHITESPACE);
	if (split_by_sp.size() != 3)
	{
		RequestLineException("Failed to parse request line at 23");
	}
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
	if (inMethod != "GET" || inMethod != "POST" || inMethod != "DELETE" || inMethod != "PUT")
		throw (RequestLineException("Failed to parse method in requestline at 57."));
	method_ = inMethod;
}

void	RequestLine::setUri(std::string const &inUri)
{
	//todo verification
	uri_ = inUri;
}

void	RequestLine::setVersion(std::string const &inVer)
{
	if (inVer != "Http/1.1")
		throw(RequestLineException("Failed to parse version in requestline at 70."));
	version_ = inVer;
}

std::string	RequestLine::getMethod(void) const
{
	return (method_);
}

std::string	RequestLine::getUri(void) const
{
	return (uri_);
}

std::string RequestLine::getVersion(void) const
{
	return (version_);
}

RequestLine::RequestLineException::RequestLineException(std::string const &msg)
:std::runtime_error(msg)
{
	return ;
}
