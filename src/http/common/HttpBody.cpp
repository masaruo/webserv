#include "HttpBody.hpp"
#include "HttpException.hpp"

std::string	HttpBody::checkBodyLen(std::string const &body)
{
	bool	is_valid = true;

	if (body.size() > HttpBody::MAX_BODY_SIZE)
		is_valid = false;
	if (!is_valid)
		throw (HttpException(HttpCode::BAD_REQUEST));
	else
		return (body);

}

HttpBody::HttpBody()
:data_()
{
	return ;
}

HttpBody::HttpBody(std::istringstream &iss, HttpHeader const &header)
:data_(checkBodyLen(iss.str()))
{
	return ;
}

HttpBody::HttpBody(std::string const &str)
:data_(checkBodyLen(str))
{
	return ;
}

HttpBody::~HttpBody()
{
	return ;
}

HttpBody::HttpBody(HttpBody const &rhs)
:data_(rhs.data_)
{
	return ;
}

HttpBody &HttpBody::operator=(HttpBody const &rhs)
{
	if (this != &rhs)
	{
		data_ = rhs.data_;
	}
	return (*this);
}

std::string	HttpBody::to_string(void) const
{
	return (data_);
}

std::size_t	HttpBody::getSize(void) const
{
	return (data_.size());
}

std::string	HttpBody::getSizeStr(void) const
{
	std::size_t const	size = getSize();
	std::string sizeStr;

	sizeStr = ft::to_string<std::size_t>(size);
	return (sizeStr);
}
