#include "HttpBody.hpp"
#include "HttpException.hpp"
#include "define.hpp"

// static std::string	assertBodyLength_(std::string const &body)
// {
// 	if (body.size() > ft::MAX_BODY_SIZE)
// 		throw (HttpException(HttpCode::CONTENT_TOO_LARGE));
// 	else
// 		return (body);
// }

HttpBody::HttpBody()
:data_()
{
	return ;
}

HttpBody::HttpBody(std::string const &str)
:data_(str)
// :data_(assertBodyLength_(str))
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

HttpBody &HttpBody::operator+=(HttpBody const &rhs)
{
	if (this != &rhs)
	{
		data_ += rhs.data_;
	}
	return (*this);
}

std::string	HttpBody::to_string(void) const
{
	return (data_);
}

char	const *HttpBody::c_str(void) const
{
	return (data_.c_str());
}

std::size_t	HttpBody::getSize(void) const
{
	return (data_.size());
}

std::string	HttpBody::size(void) const
{
	std::size_t const	size = getSize();
	std::string sizeStr;

	try
	{
			sizeStr = ft::to_string<std::size_t>(size);
			return (sizeStr);
	}
	catch(const std::exception& e)
	{
		throw (HttpException(HttpCode::BAD_REQUEST));
	}
	
}

bool	HttpBody::empty(void) const
{
	return (data_.empty());
}
