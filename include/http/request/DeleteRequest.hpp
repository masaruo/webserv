#pragma once
#include "ARequest.hpp"
#include "HttpBody.hpp"

class DeleteRequest : public ARequest
{
private:
	std::string	setLocalPath(void) const;
	void		removeFile(std::string const &abspath) const;
	DeleteRequest();//=delete
public:
	explicit DeleteRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config, Server &server);
	DeleteRequest(DeleteRequest const &rhs);
	DeleteRequest &operator=(DeleteRequest const &rsh);
	~DeleteRequest();

	void	generateResponseData(void);
};
