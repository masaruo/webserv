#include "AResponse.hpp"

// AResponse::uri_map_t	uri_map_;

AResponse::AResponse()
// :status_code_(0), line_(), header_(), body_()
{
	return ;
}

AResponse::~AResponse()
{
	return ;
}

AResponse::AResponse(AResponse const &rhs)
:status_code_(rhs.status_code_)
// ,line_(rhs.line_)
// ,header_(rhs.header_)
// ,body_(rhs.body_)
{
	return ;
}

AResponse &AResponse::operator=(AResponse const &rhs)
{
	if (this != &rhs)
	{
		status_code_ = rhs.status_code_;
		// line_ = rhs.line_;
		// header_ = rhs.header_;
		// body_ = rhs.body_;
	}
	return (*this);
}
