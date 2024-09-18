#include "HttpBody.hpp"

Binary	HttpBody::parseBody(std::istringstream &iss)
{
	std::string		str(iss.str().substr(iss.tellg()));
	Binary	bin(str);
	return (bin);
}

Binary	HttpBody::parseBody(std::string const &str)
{
	Binary	bin(str);
	return (bin);
}

HttpBody::HttpBody()
:body_()
,size_(0)
{
	return ;
}

HttpBody::HttpBody(std::istringstream &iss)
:body_(parseBody(iss))
,size_(body_.data().size())
{
	return ;
}

HttpBody::HttpBody(std::string const &str)
:body_(parseBody(str))
,size_(str.size())
{
	return ;
}

HttpBody::HttpBody(Binary const &binary)
:body_(binary)
,size_(binary.data().size())
{
	return ;
}

HttpBody::~HttpBody()
{
	return ;
}

HttpBody::HttpBody(HttpBody const &rhs)
:body_(rhs.body_)
,size_(rhs.size_)
{
	return ;
}

HttpBody &HttpBody::operator=(HttpBody const &rhs)
{
	if (this != &rhs)
	{
		body_ = rhs.body_;
		size_ = rhs.size_;
	}
	return (*this);
}

std::string	HttpBody::str(void) const
{
	return (body_.toStr());
}

std::size_t	HttpBody::getSize(void) const
{
	return (size_);
}

HttpBody::HttpBodyException::HttpBodyException(std::string const &msg)
:std::runtime_error(msg)
{
	return ;
}
