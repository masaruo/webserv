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
void	GetResponse::createBody(void)
{
	// line_ = RequestLine(" GET / HTTP/1.1 \n");
	// std::string body;
	// body = "リクエスト情報:\n";
	// body += std::string("メソッド: ") + line_.get_methodStr() + "\n";
	// body += std::string("URI: ") + line_.get_uri() + "\n";
	// body += std::string("バージョン: ") + line_.get_ver() + "\n";
	// body += std::string("ヘッダー:\n") + header_.printHeader() + "\n";

	//! below is the real code
	std::string mockPath("/webserv/www/index.html");
	std::string body = FileReader::readTextFile(mockPath);

	std::ostringstream response;
	response << "HTTP/1.1 200 OK\r\n";
	response << "Content-Type: text/plain\r\n";
	response << "Content-Length: " << body.length() << "\r\n";
	response << "\r\n"; // ヘッダーとボディの区切り
	response << body;

	body_ = response.str();
	
}

std::string	GetResponse::str(void) const
{
	return (body_);
}
