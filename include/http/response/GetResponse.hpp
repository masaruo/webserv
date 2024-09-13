#pragma once
#include <AResponse.hpp>

class GetResponse : public AResponse
{
private:
	GetResponse();//=delete
public:
	explicit GetResponse(std::string const &uri, HttpHeader const &req_header);
	~GetResponse();
	GetResponse(GetResponse const &rhs);
	GetResponse &operator=(GetResponse const &rhs);
	void	generateResponse(void);
};
