#include "GetResponse.hpp"
#include "FileHandler.hpp"
#include "define.hpp"

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
	//todo need to make it dynamic
	std::string mockPath("/webserv/www/upload.html");//! hardcoded route
	//!try - catch readTextFile
	std::string	body = FileReader::readTextFile(mockPath);

	StatusLine	line;
	line.setStatusCode(StatusCode::OK);
	line.setVersion("HTTP/1.1");
	setLine(line);

	HttpHeader	header;
	header.setHeader("Content-Type:", " text/html\r\n");
	header.setHeader("Content-Length", body.size() + "\r\n");
	header.setHeader("Connection", " keep-alive\r\n");

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
