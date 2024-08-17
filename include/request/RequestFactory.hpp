#pragma once
#include "unique_ptr.hpp"
#include <string>

class ARequest;
// class GetRequest;
// class Post;
// class Delete;
// class HttpLine;

class RequestFactory
{
private:
	RequestFactory();
	RequestFactory(RequestFactory const &rhs);
	RequestFactory &operator=(RequestFactory const &rhs);
	~RequestFactory();
public:
	// static ft::unique_ptr<ARequest>	createRequest(HttpLine const &line);
	static	ARequest	*createRequest(std::string const &raw_request);
	// static ft::unique_ptr<ARequest> createRequest(std::string const &raw_request);
};
