#include "GetResponse.hpp"
#include "FileHandler.hpp"

GetResponse::GetResponse(std::string const &uri, HttpHeader const &req_header)
:AResponse(uri, req_header)
{
	return ;
}

GetResponse::~GetResponse()
{
	return ;
}

GetResponse::GetResponse(GetResponse const &rhs)
:AResponse(rhs)
{
	return ;
}

GetResponse &GetResponse::operator=(GetResponse const &rhs)
{
	if (this != &rhs)
	{
		AResponse::operator=(rhs);
	}
	return (*this);
}

#include <sstream>
ft::bytes_vec	GetResponse::generateResponse(void)
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
    response << "Connection: keep-alive\r\n";
    response << "\r\n";  // ヘッダーとボディを区切る空行
	response << body;

	setBody(response.str());
	return (getBody());
}
