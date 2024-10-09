#include "AutoIndexRequest.hpp"
#include "dirent.h"
#include "Response.hpp"
#include "HttpException.hpp"

AutoIndexRequest::AutoIndexRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:ARequest(line, header, config)
{
	return ;
}

AutoIndexRequest::~AutoIndexRequest()
{
	return ;
}

AutoIndexRequest::AutoIndexRequest(AutoIndexRequest const &rhs)
:ARequest(rhs)
{
	return ;
}

AutoIndexRequest &AutoIndexRequest::operator=(AutoIndexRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator = (rhs);
	}
	return (*this);
}

static ft::str_vec	getFileNames(std::string const &path)
{
	struct dirent	*dp;
	DIR 			*dirp;
	ft::str_vec		files;

	dirp = opendir(path.c_str());
	if (dirp == NULL)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

	while ((dp = readdir(dirp)) != NULL)
	{
		files.push_back(dp->d_name);
	}
	if (closedir(dirp) == ft::err)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	return (files);
}

Response	AutoIndexRequest::generateResponse(void) const
{
	std::string const	path = getLocalPath();
	ft::str_vec const	fileNamesVec = getFileNames(path);
	ft::str_vec::const_iterator	iter = fileNamesVec.begin();
	ft::str_vec::const_iterator	end = fileNamesVec.end();
	std::string			fileNameStr = "";

	while (iter != end)	
	{
		fileNameStr += *iter;
		if (iter + 1 != end)
			fileNameStr += "\n";
		iter++;
	}

	HttpBody	body(fileNameStr);

	HttpStatus status(HttpCode::OK);

	HttpHeader header;
	header.addValue("Content-Type", "text/plain");
	header.addValue("Content-Length", body.getSizeStr());
	header.addValue("Connection", "close");

	Response	r(status, header, body);
	return (r);
}
