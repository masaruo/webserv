#pragma once
#include <memory>

class ARequest;
class HttpGet;
class HttpPost;
class HttpDelete;
class HttpRequestLine;
class HttpHeaders;

class RequestFactory
{
private:
	RequestFactory();
	RequestFactory(RequestFactory const &rhs);
	RequestFactory &operator=(RequestFactory const &rhs);
	~RequestFactory();
public:
	static std::auto_ptr<ARequest>	createRequest(HttpRequestLine const &line, HttpHeaders const &headers);
};
