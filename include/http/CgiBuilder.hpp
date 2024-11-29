#pragma once
#include "AResponseBuilder.hpp"

class CgiBuilder : public AResponseBuilder
{
private:
	virtual void buildStatusLine();
	virtual void buildHeader();
	virtual void buildBody();
public:
	CgiBuilder();
	~CgiBuilder();
	CgiBuilder(CgiBuilder const &rhs);
	CgiBuilder &operator=(CgiBuilder const &rhs);
};
