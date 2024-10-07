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

bool	GetRequest::is_autoIndex(std::string const &path) const
{
	bool const	isdir = is_dir(path);
	config::Config::location_s const	loc = getConfig().getLocation(path);
	std::string const index = loc.index_;
	if (index == "")
		return (true);
	else
		return (false);
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
	else if (is_autoIndex(path))
	{
		AutoIndexRequest ai(getLine(), getHeader(), getConfig());
		Response	r(ai.generateResponse());
		return (r);
	}
	else
	{
		std::string	const	path = uri.getPath();
		std::string const	absPath = getLocalPath() + getConfig().getIndex(path);

		HttpBody	body(FileReader::readTextFile(absPath));

		HttpHeader	header;
		header.setElem("content-type", "text/html");
		header.setElem("content-length", body.getSizeStr());
		header.setElem("Connection", "close");

		HttpStatus	status(HttpCode::OK);

		Response	r(status, header, body);
		return (r);
	}
}
