#include "FileHandler.hpp"
#include "HttpException.hpp"
#include <fstream>
#include <unistd.h>// read
#include <sys/stat.h>// stat

std::string FileHandler::read(std::string const &path)
{
	std::ifstream	ifs(path.c_str(), std::ios::in | std::ios::binary);
	if(!ifs)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));//? error type
	}
	std::string	buf;
	ifs.seekg(0, std::ios::end);
	std::streamsize	size = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	buf.resize(static_cast<std::size_t>(size));
	if (!ifs.read(&buf[0], buf.size()))
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));//? error type
	}
	return (buf);
}

std::string	FileHandler::read(int fd)
{
	const std::size_t BUFFSIZE = 4096;
	std::string buf(BUFFSIZE, '\0');
	std::string	result;

	while (true)
	{
		ssize_t	bytesRead = ::read(fd, (void*)buf.data(), buf.size());
		if (bytesRead == ft::err)
		{
			throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));//? error type
		}
		else if (bytesRead == ft::eof)
		{
			break ;
		}
		else
		{
			result.insert(result.end(), buf.begin(), buf.begin() + bytesRead);
		}
	}
	return (result);
}

bool	FileHandler::isDir(std::string const &path)
{
	struct stat	buf;

	int res = stat(path.c_str(), &buf);
	if (res == ft::err)
		return (false);
	else if (S_ISDIR(buf.st_mode))
		return (true);
	else
		return (false);
}
