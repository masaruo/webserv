#pragma once
#include "Request.hpp"
#include "Server.hpp"
#include "AResponseBuilder.hpp"

class ResponseFactory
{
private:
	Server				&server_;
	AResponseBuilder	*builder_;

	ResponseFactory();
	ResponseFactory(ResponseFactory const &rhs);
	ResponseFactory &operator=(ResponseFactory const &rhs);
public:
	ResponseFactory(Server &server);
	~ResponseFactory();
};
