#pragma once
// #include "unique_ptr.hpp"
#include "ConfigFactory.hpp"
// #include <string>
// #include <stdexcept>

class ARequest;
class RequestLine;
class HttpHeader;
class HttpBody;

class RequestFactory
{
public:
	static int const	HASCHUNK;
	static int const	HASBODY;
	static int const	NOBODY;
private:
	RequestFactory();
	RequestFactory(RequestFactory const &rhs);
	RequestFactory &operator=(RequestFactory const &rhs);
	~RequestFactory();
public:
	static ARequest	*createRequest(int fd, config::ConfigFactory const &config_factory);
	static void		createRequestLineAndHeader(int fd, RequestLine &line, HttpHeader &header);
	static int		hasBody(HttpHeader const &header);
};
