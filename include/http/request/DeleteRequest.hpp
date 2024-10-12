#pragma once
#include "ARequest.hpp"
#include "HttpBody.hpp"

class DeleteRequest : public ARequest
{
private:
	std::string	setLocalPath(void) const;
	void		removeFile(void) const;
	DeleteRequest();//=delete
public:
	explicit DeleteRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config);
	DeleteRequest(DeleteRequest const &rhs);
	DeleteRequest &operator=(DeleteRequest const &rsh);
	~DeleteRequest();

	Response	generateResponse(void) const;
};
