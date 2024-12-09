#pragma once
#include "AHeader.hpp"

class ResponseHeader : public AHeader
{
private:
	void	parseHeaderStr(std::string const &request);

public:
	ResponseHeader();
	explicit ResponseHeader(std::string const &response);
	~ResponseHeader();
	ResponseHeader(ResponseHeader const &rhs);
	ResponseHeader &operator=(ResponseHeader const &rhs);
	void	add(std::string const &line);
};
