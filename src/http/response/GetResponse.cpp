#include "GetResponse.hpp"
#include "FileHandler.hpp"
#include "define.hpp"

GetResponse::GetResponse(ft::unique_ptr<ARequest>request)
:Response(request)
{
	return ;
}

GetResponse::~GetResponse()
{
	return ;
}

GetResponse::GetResponse(GetResponse const &rhs)
:Response(rhs)
{
	return ;
}

GetResponse &GetResponse::operator=(GetResponse const &rhs)
{
	if (this != &rhs)
	{
		Response::operator=(rhs);
	}
	return (*this);
}

#include "mockpath.hpp"//todo delete
void	GetResponse::generateResponse(void)
{
	std::string	path = getResource().getNormalizedPath();
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
