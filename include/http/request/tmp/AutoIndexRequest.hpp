#pragma once
#include <ARequest.hpp>

class AutoIndexRequest : public ARequest
{
private:
	AutoIndexRequest();//=delete

public:
	explicit	AutoIndexRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config);
	~AutoIndexRequest();
	AutoIndexRequest(AutoIndexRequest const &rhs);
	AutoIndexRequest &operator=(AutoIndexRequest const &rhs);
	Response	generateResponse(void) const;
};
