#pragma once
#include "ARequest.hpp"

class Response;
class CgiSocket;

class PostRequest : public ARequest
{
private:
	CgiSocket	*cgi_socket_;
	std::string	setLocalPath(void) const;
	PostRequest();//=delete
public:
	explicit PostRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config, Server &server);
	PostRequest(PostRequest const &rhs);
	PostRequest &operator=(PostRequest const &rhs);
	~PostRequest();
	void	generateResponseData(void);
};
