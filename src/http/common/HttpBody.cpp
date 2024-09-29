#include "HttpBody.hpp"

std::string	HttpBody::assertBodyLen(std::string const &body)
{
	bool	is_valid = true;

	if (body.size() > HttpBody::MAX_BODY_SIZE)
		is_valid = false;
	if (body.size() != header_.getContentLen())
		is_valid = false;
	if (!is_valid)
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	else
		return (body);

}

HttpBody::HttpBody()
:data_()
,header_()
{
	return ;
}

HttpBody::HttpBody(std::istringstream &iss, HttpHeader const &header)
:data_(assertBodyLen(iss.str()))
,header_(header)
{
	return ;
}

HttpBody::HttpBody(std::string const &str)
:data_(str)
,header_()//!~?
{
	return ;
}

HttpBody::~HttpBody()
{
	return ;
}

HttpBody::HttpBody(HttpBody const &rhs)
:data_(rhs.data_)
,header_(rhs.header_)
{
	return ;
}

HttpBody &HttpBody::operator=(HttpBody const &rhs)
{
	if (this != &rhs)
	{
		data_ = rhs.data_;
		header_ = rhs.header_;
	}
	return (*this);
}

std::string	HttpBody::data(void) const
{
	return (data_);
}

std::size_t	HttpBody::getSize(void) const
{
	return (data_.size());
}
