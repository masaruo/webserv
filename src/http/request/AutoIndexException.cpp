#include "AutoIndexException.hpp"
#include "Response.hpp"
#include "string.hpp"
#include <dirent.h>//opendir, readdir, closedir

AutoIndexException::AutoIndexException(HttpCode::StatusCode statuscode, std::string const &path)
:AResponseException(statuscode, path)
{
	return ;
}

AutoIndexException::~AutoIndexException()
{
	return ;
}

AutoIndexException::AutoIndexException(AutoIndexException const &rhs)
:AResponseException(rhs)
{
	return ;
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
	if (closedir(dirp) == -1)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	return (files);
}

Response	AutoIndexException::generateResponse(void) const
{
	std::string const	&path = getPath();
	ft::str_vec const	&fileNamesVec = getFileNames(path);
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

	ResponseHeader header;
	// header.addValue(HttpHeader::CONTENT_TYPE, "text/plain");
	// header.addValue(HttpHeader::CONTENT_LENGTH, body.size());
	// header.addValue(HttpHeader::CONNECTION, "close");

	Response	r(status, header, body);
	return (r);
}
