#include "autoIndexException.hpp"
#include "Response.hpp"
#include "string.hpp"
#include <dirent.h>//opendir, readdir, closedir

AutoIndexException::AutoIndexException(HttpCode::StatusCode statuscode, std::string const &path)
:HttpException(statuscode)
,path_(path)
{
	return ;
}

AutoIndexException::~AutoIndexException() throw()
{
	return ;
}

AutoIndexException::AutoIndexException(AutoIndexException const &rhs)
:HttpException(rhs)
,path_(rhs.path_)
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
	if (closedir(dirp) == ft::err)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	return (files);
}

Response	AutoIndexException::generateResponse(void) const
{
	std::string const	&path = path_;
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

	HttpHeader header;
	header.addValue(HttpHeader::CONTENT_TYPE, "text/plain");
	header.addValue(HttpHeader::CONTENT_LENGTH, body.getSizeStr());
	header.addValue(HttpHeader::CONNECTION, "close");

	Response	r(status, header, body);
	return (r);
}
