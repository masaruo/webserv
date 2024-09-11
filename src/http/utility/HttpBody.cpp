#include "HttpBody.hpp"

ft::bytes_vec	HttpBody::parseBody(std::istringstream &iss, std::size_t len)
{
	ft::bytes_vec	bytes;
	std::string		str(iss.str().substr(iss.tellg()));
	
	std::string::const_iterator it = str.begin();
	std::string::const_iterator end = str.end();
	std::size_t i = 0;

	while (it != end && i < len)
	{
		bytes.push_back(*it);
		it++, i++;
	}
	return (bytes);
}

HttpBody::HttpBody()
:body_()
{
	return ;
}

HttpBody::HttpBody(std::istringstream &iss, std::size_t len)
:body_(parseBody(iss, len))
{
	return ;
}

HttpBody::~HttpBody()
{
	return ;
}

HttpBody::HttpBody(HttpBody const &rhs)
:body_(rhs.body_)
{
	return ;
}

HttpBody &HttpBody::operator=(HttpBody const &rhs)
{
	if (this != &rhs)
	{
		body_ = rhs.body_;
	}
	return (*this);
}

ft::bytes_vec	HttpBody::getBody(void) const
{
	return (body_);
}
