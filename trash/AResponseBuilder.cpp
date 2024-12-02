#include "AResponseBuilder.hpp"

AResponseBuilder::AResponseBuilder()
:status_(), header_(), body_(), has_body_(false)
{
	return ;
}

AResponseBuilder::AResponseBuilder(AResponseBuilder const &rhs)
:status_(rhs.status_), header_(rhs.header_), body_(rhs.body_), has_body_(rhs.has_body_)
{
	return ;
}

AResponseBuilder &AResponseBuilder::operator=(AResponseBuilder const &rhs)
{
	if (this != &rhs)
	{
		status_ = rhs.status_;
		header_ = rhs.header_;
		body_ = rhs.body_;
		has_body_ = rhs.has_body_;
	}
	return (*this);
}

AResponseBuilder::~AResponseBuilder()
{
	return ;
}

AResponseBuilder	&AResponseBuilder::setStatusCode(HttpStatus const &status)
{
	status_ = status;
	return (*this);
}

AResponseBuilder	&AResponseBuilder::setHeader(std::string const &key, std::string const &value)
{
	header_.addValue(key, value);
	return (*this);
}

AResponseBuilder	&AResponseBuilder::setBody(std::string const &body)
{
	body_ = HttpBody(body);
	has_body_ = true;
	return (*this);
}

std::string	AResponseBuilder::build()
{
	std::string	res;

	buildStatusLine();
	buildHeader();
	buildBody();
	res = status_.to_string() + "\r\n" + header_.to_string() + "\r\n" + body_.to_string();
	return (res);
}
