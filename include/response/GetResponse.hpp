#pragma once
#include <AResponse.hpp>

class GetResponse : public AResponse
{
private:

public:
	GetResponse();
	~GetResponse();
	GetResponse(GetResponse const &rhs);
	GetResponse &operator=(GetResponse const &rhs);
	void		createBody();
	std::string	str(void) const;
};
