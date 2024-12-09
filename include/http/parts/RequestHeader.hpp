#pragma once
#include "AHeader.hpp"

class RequestHeader : public AHeader
{
private:
	headerSet	noDup_;
	void		parseHeaderStr(std::string const &request);
	void		assertHeader(void) const;
public:
	RequestHeader();
	explicit RequestHeader(std::string const &request);
	~RequestHeader();
	RequestHeader(RequestHeader const &rhs);
	RequestHeader &operator=(RequestHeader const &rhs);
	void	add(std::string const &line);
};
