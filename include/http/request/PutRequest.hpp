#pragma once
#include "ARequest.hpp"

class Response;

class PutRequest : public ARequest
{
private:
	std::string	setLocalPath(void) const;
	void		uploadFile(std::string const &abspath) const;
	PutRequest();//=delete
public:
	explicit PutRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config);
	explicit PutRequest(PutRequest const &rhs);
	PutRequest &operator=(PutRequest const &rhs);
	~PutRequest();
	void	generateResponseData(void);
};
