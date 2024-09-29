#pragma once
#include <AResponse.hpp>

class GetResponse : public Response
{
private:
	GetResponse();//=delete
public:
	// explicit GetResponse(std::string const &uri, HttpHeader const &req_header);
	explicit GetResponse(ft::unique_ptr<ARequest>request);
	~GetResponse();
	GetResponse(GetResponse const &rhs);
	GetResponse &operator=(GetResponse const &rhs);
	void	generateResponse(void);
};
