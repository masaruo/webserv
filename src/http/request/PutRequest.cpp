#include "PutRequest.hpp"
#include "PutResponse.hpp"
#include <fstream>

PutRequest::PutRequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body)
:ARequest(line, header, body)
{
	return ;
}

PutRequest::~PutRequest()
{
	return ;
}

PutRequest::PutRequest(PutRequest const &rhs)
:ARequest(rhs.getLine(), rhs.getHeader(), rhs.getBody())
{
	return ;
}

PutRequest &PutRequest::operator=(PutRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator=(rhs);
	}
	return (*this);
}

AResponse	*PutRequest::createResponse(void) const
{
	saveBody();
	ft::unique_ptr<ARequest>tmp(new PutRequest(*this));
	// return (new PutResponse(getLine().getUri(), getHeader(), body_));
	return (new PutResponse(tmp));
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

	ofs.write(getBody().str().c_str(), getBody().getSize());
	if (!ofs)
	{
		//todo error
	}
}
