#pragma once
#include "AResponse.hpp"

class PostResponse : public AResponse
{
private:

public:
	PostResponse();
	~PostResponse();
	PostResponse(PostResponse const &rhs);
	PostResponse &operator=(PostResponse const &rhs);
	void		createBody(std::string const &path);
	std::string	str(void) const;
};
