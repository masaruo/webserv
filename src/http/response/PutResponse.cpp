#include "PutResponse.hpp"
#include "FileHandler.hpp"

// PutResponse::PutResponse(std::string const &uri, HttpHeader const &header, HttpBody const &body)
// :AResponse(uri, header)
// ,request_body_(body)
// {
// 	return ;
// }

PutResponse::PutResponse(ft::unique_ptr<ARequest>request)
:Response(request)
{
	return ;
}

PutResponse::~PutResponse()
{
	return ;
}

PutResponse::PutResponse(PutResponse const &rhs)
:Response(rhs)
{
	return ;
}

PutResponse &PutResponse::operator=(PutResponse const &rhs)
{
	if (this != &rhs)
	{
		Response::operator=(rhs);
	}
	return (*this);
}

void	PutResponse::generateResponse(void)
{
	std::string path = "/webserv/www/upload_success.html";
	HttpBody body(FileReader::readTextFile(path));
	//todo try catch : error handling

	setStatus(HttpCode::OK);

	HttpHeader	header;
	header.setHeader("Content-Type", " text/html\r\n");
	std::string size_str = ft::to_string<std::size_t>(body.getSize());
	header.setHeader("Content-Length", size_str + "\r\n");
	header.setHeader("Connection", " keep-alive\r\n");
	setHeader(header);

	setBody(body);
	return ;
}
