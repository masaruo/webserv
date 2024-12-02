#include "CgiBuilder.hpp"

CgiBuilder::CgiBuilder(CgiSocket *socket)
:AResponseBuilder()
,socket_(socket)
{
	return ;
}

CgiBuilder::~CgiBuilder()
{
	return ;
}

CgiBuilder &CgiBuilder::setScriptPath(std::string const &script_path)
{
	script_path_ = script_path;
	return (*this);
}

void	CgiBuilder::buildStatusLine()
{
	return ;
}

void	CgiBuilder::buildHeader()
{
	return ;
}

void	CgiBuilder::buildBody()
{
	return ;
}

void	CgiBuilder::parseCgiOutput(std::string const &cgi_output)
{
	return ;
}
