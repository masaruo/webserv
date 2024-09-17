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
	static	ARequest	*createRequest(int fd);
};
