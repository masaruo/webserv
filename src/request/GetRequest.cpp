#include "GetRequest.hpp"
#include "GetResponse.hpp"

GetRequest::GetRequest()
:ARequest()
{
	return ;
}

GetRequest::GetRequest(std::string const &raw_request)
:ARequest(raw_request)
{
	return ;
}

GetRequest::~GetRequest()
{
	return ;
}

GetRequest::GetRequest(GetRequest const &rhs)
:ARequest(rhs)
{

}

GetRequest &GetRequest::operator=(GetRequest const &rhs)
{
	if (this != &rhs)
	{
		*this = rhs;
	}
	return (*this);
}

#include <sstream>
void GetRequest::createMockResponse(int sockfd)
{
	(void)sockfd; // 未使用の引数を無視

	std::string body;
	body = "リクエスト情報:\n";
	body += std::string("メソッド: ") + line_.get_methodStr() + "\n";
	body += std::string("URI: ") + line_.get_uri() + "\n";
	body += std::string("バージョン: ") + line_.get_ver() + "\n";
	body += std::string("ヘッダー:\n") + header_.printHeader() + "\n";

	std::ostringstream response;
	response << "HTTP/1.1 200 OK\r\n";
	response << "Content-Type: text/plain\r\n";
	response << "Content-Length: " << body.length() << "\r\n";
	response << "\r\n"; // ヘッダーとボディの区切り
	response << body;

	dummy_res = response.str();
}

AResponse	*GetRequest::createResponse(int sockfd) const
{
	return (new GetResponse());
}

std::string	GetRequest::get_path(void) const
{
	return (line_.get_uri());
}
