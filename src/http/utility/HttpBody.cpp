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
:data_()
,size_(0)
{
	return ;
}

HttpBody::HttpBody(std::istringstream &iss)
:data_(parseBody(iss))
,size_(data_.data().size())
{
	return ;
}

HttpBody::HttpBody(std::string const &str)
:data_(parseBody(str))
,size_(str.size())
{
	return ;
}

HttpBody::HttpBody(Binary const &binary)
:data_(binary)
,size_(binary.data().size())
{
	return ;
}

HttpBody::~HttpBody()
{
	return ;
}

HttpBody::HttpBody(HttpBody const &rhs)
:data_(rhs.data_)
,size_(rhs.size_)
{
	return ;
}

HttpBody &HttpBody::operator=(HttpBody const &rhs)
{
	if (this != &rhs)
	{
		data_ = rhs.data_;
		size_ = rhs.size_;
	}
	return (*this);
}

std::string	HttpBody::str(void) const
{
	return (data_.toStr());
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
