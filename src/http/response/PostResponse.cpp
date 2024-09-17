#include "PostResponse.hpp"
#include "FileHandler.hpp"

PostResponse::PostResponse(std::string const &target, HttpHeader const &req_header)
:AResponse(target, req_header)
{
	return ;
}

PostResponse::~PostResponse()
{
	return ;
}

PostResponse::PostResponse(PostResponse const &rhs)
:AResponse(rhs)
{
	return ;
}

PostResponse &PostResponse::operator=(PostResponse const &rhs)
{
	if (this != &rhs)
	{
		AResponse::operator=(rhs);
	}
	return (*this);
}

#include <sstream>
void	PostResponse::generateResponse(void)
{
	std::string mockPath("/webserv/www/index.html");
	// if (path == "/test")
	// 	mockPath = "/webserv/www/test.html";
	// else if (path == "/cgi")
	// 	mockPath = "/webserv/www/hello.cgi";
	std::string body = FileReader::readTextFile(mockPath);

	std::ostringstream response;
	response << "HTTP/1.1 200 OK\r\n";
	response << "Content-Type: text/html; charset=UTF-8\r\n";
	response << "Content-Length: " << body.length() << "\r\n";
	// response << "Connection: keep-alive\r\n";
	response << "\r\n";  // ヘッダーとボディを区切る空行
	response << body;

	setBody(response.str());
}
