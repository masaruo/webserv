#include "ARequest.hpp"
#include "string.hpp"
#include "HttpLine.hpp"
#include "HttpHeader.hpp"

ARequest::ARequest()
:line_()
,header_()
{
	return ;
}

ARequest::ARequest(std::string const &raw_request)
:line_()
,header_()
{
	parse(raw_request);
}

ARequest::ARequest(ARequest const &rhs)
:line_(rhs.line_)
,header_(rhs.header_)
{
	return ;
}

ARequest::~ARequest()
{
	return ;
}

ARequest	&ARequest::operator=(ARequest const &rhs)
{
	if (this != &rhs)
	{
		line_ = rhs.line_;
		header_ = rhs.header_;
	}
	return (*this);
}

void	ARequest::parse(std::string const &raw_data)
{
	ft::string					tmp(raw_data);
	ft::string::string_vector	split_by_lf = tmp.split(ft::string::LF);

	HttpLine new_line(split_by_lf.at(0).str());
	line_ = new_line;
	split_by_lf.erase(split_by_lf.begin());
	//? error if split_by_lf.size() == 0?
	HttpHeader new_header(split_by_lf);
	header_ = new_header;
}

HttpLine const &ARequest::getRequestLine(void) const
{
	return (line_);
}

HttpHeader const &ARequest::getRequestHeader(void) const
{
	return (header_);
}
