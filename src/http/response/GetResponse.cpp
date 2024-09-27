#include "GetResponse.hpp"
#include "FileHandler.hpp"
#include "define.hpp"

GetResponse::GetResponse(ft::unique_ptr<ARequest>request)
:AResponse(request)
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

#include "mockpath.hpp"//todo delete
void	GetResponse::generateResponse(void)
{
	// std::string	path = getUri();
	// MockPath	mock;
	// std::string	path = mock.getPath(getUri());
	std::string	path = getUri();
	HttpBody body(FileReader::readTextFile(path));
	//todo try catch : error handling

	setStatus(HttpCode::OK);

	HttpHeader	header;
	header.setHeader("Content-Type", " text/html\r\n");
	std::string size_str = ft::to_string<std::size_t>(body.getSize());
	header.setHeader("Content-Length", size_str + "\r\n");
	// header.setHeader("Connection", " keep-alive\r\n");
	setHeader(header);

	setBody(body);
}
