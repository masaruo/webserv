#pragma once
#include "ARequest.hpp"

class Response;

class PutRequest : public ARequest
{
private:
	void	upload(std::string const &path) const;
	PutRequest();//=delete
public:
	explicit PutRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config);
	explicit PutRequest(PutRequest const &rhs);
	PutRequest &operator=(PutRequest const &rhs);
	~PutRequest();
	Response	createResponse(void) const;
};
