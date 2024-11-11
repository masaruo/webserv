#pragma once
#include "ARequest.hpp"

class Response;

class PostRequest : public ARequest
{
private:
	std::string	setLocalPath(void) const;
	PostRequest();//=delete
public:
	explicit PostRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config, Server &server);
	PostRequest(PostRequest const &rhs);
	PostRequest &operator=(PostRequest const &rhs);
	~PostRequest();
	void	generateResponseData(void);
};
