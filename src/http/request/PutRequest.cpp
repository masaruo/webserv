#include "PutRequest.hpp"
#include "PutResponse.hpp"
#include <fstream>

PutRequest::PutRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body)
:ARequest(line, header)
,body_(body)
{
	return ;
}

PutRequest::~PutRequest()
{
	return ;
}

PutRequest::PutRequest(PutRequest const &rhs)
:ARequest(rhs.getLine(), rhs.getHeader())
,body_(rhs.body_)
{
	return ;
}

PutRequest &PutRequest::operator=(PutRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator=(rhs);
		body_ = rhs.body_;
	}
	return (*this);
}

AResponse	*PutRequest::createResponse(void) const
{
	saveBody();
	return (new PutResponse(getLine().getUri(), getHeader(), body_));
}

void	PutRequest::saveBody(void) const
{
	std::string	savePath = "/webserv/save/";
	std::string	name = getHeader().getHeader("X-File-Name");
	std::string	fullPath = savePath + name;
	std::ofstream	ofs(fullPath.c_str() , std::ios_base::trunc | std::ios_base::binary);
	if (!ofs)
	{
		//todo error
		return ;
	}
	std::string const	&dataStr = body_.str();
	Binary				binary(dataStr);
	std::streamsize		size = binary.data().size();

	ofs.write(binary.toStr().c_str(), size);
	if (!ofs)
	{
		//todo error
	}
}
