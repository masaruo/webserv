#include "GetResponse.hpp"
#include "FileHandler.hpp"

GetResponse::GetResponse()
{
	return ;
}

GetResponse::~GetResponse()
{
	return ;
}

GetResponse::GetResponse(GetResponse const &rhs)
{
	return ;
}

GetResponse &GetResponse::operator=(GetResponse const &rhs)
{
	return (*this);
}

#include <sstream>
void	GetResponse::createBody(std::string const &path)
{
	//! below is the real code
	std::string mockPath("/webserv/www/index.html");
	if (path == "/test")
		mockPath = "/webserv/www/test.html";
	else if (path == "/cgi")
		mockPath = "/webserv/www/hello.cgi";
	std::string body = FileReader::readTextFile(mockPath);

	std::ostringstream response;
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Type: text/html; charset=UTF-8\r\n";
    response << "Content-Length: " << body.length() << "\r\n";
    response << "Connection: keep-alive\r\n";
    response << "\r\n";  // ヘッダーとボディを区切る空行
	response << body;

	body_ = response.str();
	
}

std::string	GetResponse::str(void) const
{
	return (body_);
}
