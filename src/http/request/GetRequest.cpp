#include "GetRequest.hpp"
#include "Response.hpp"
#include "CgiRequest.hpp"
#include "AutoIndexRequest.hpp"
#include "FileHandler.hpp"
#include <sys/stat.h>

GetRequest::GetRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:ARequest(line, header, config)
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
	return ;
}

GetRequest &GetRequest::operator=(GetRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator=(rhs);
	}
	return (*this);
}

static bool	is_dir(std::string const &path)
{
	struct stat	buf;

	int res = stat(path.c_str(), &buf);
	if (res == ft::err)
		return (false);

	if (S_ISDIR(buf.st_mode))
		return (true);
	else
		return (false);
}

//! todo auto indexを探すだけでなく、ないときにINDEXからサイトを取ってくる？
bool	GetRequest::isAutoIndex(std::string const &path) const
{
	bool const	isdir = is_dir(path);
	config::Config::LocationConfig	const &loc = getConfigLocation();
	if (loc.directive_.hasKey(config::Config::INDEX))
	{
		std::string const &index_directive = loc.directive_.getFirstValue(config::Config::INDEX);
		if (index_directive.empty())
			return (true);
		else
			return (false);
	}
	else
		return (true);
}

Response	GetRequest::generateResponse(void) const
{
	HttpUri const		uri = getLine().getUri();
	std::string const	path = uri.getPath();

	if (uri.IsCgi())
	{
		CgiRequest	cgi(getLine(), getHeader(), getConfig());
		Response	r(cgi.generateResponse());
		return (r);
	}
	else if (isAutoIndex(path))
	{
		AutoIndexRequest ai(getLine(), getHeader(), getConfig());
		Response	r(ai.generateResponse());
		return (r);
	}
	else
	{
		std::string	const	&path = uri.getPath();
		std::string const	&absPath = getLocalPath() + getConfigLocation().directive_.getFirstValue(config::Config::INDEX);

		HttpBody	body(FileHandler::read(absPath));//todo IOclass

		HttpHeader	header;
		header.addValue(HttpHeader::CONTENT_TYPE, "text/html");
		header.addValue(HttpHeader::CONTENT_LENGTH, body.getSizeStr());

		HttpStatus	status(HttpCode::OK);

		Response	r(status, header, body);
		return (r);
	}
}
