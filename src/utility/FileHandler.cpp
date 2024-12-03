#include "FileHandler.hpp"
#include "HttpException.hpp"
#include "define.hpp"
#include <fstream>
#include <sys/stat.h>// stat

// std::string FileHandler::read(std::string const &path)
// {
// 	std::ifstream	ifs(path.c_str(), std::ios::binary);
// 	if(!ifs)
// 	{
// 		throw (HttpException(HttpCode::NOT_FOUND));
// 	}
// 	std::string	buf;
// 	ifs.seekg(0, std::ios::end);
// 	std::streamsize	size = ifs.tellg();
// 	ifs.seekg(0, std::ios::beg);
// 	buf.resize(static_cast<std::size_t>(size));
// 	if (!ifs.read(&buf[0], buf.size()))
// 	{
// 		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
// 	}
// 	return (buf);
// }

// std::string	FileHandler::read(int fd)
// {
// 	std::string buf(ft::READ_BUF_SIZE, '\0');
// 	std::string	result;

// 	while (true)
// 	{
// 		ssize_t	bytesRead = ::read(fd, (void*)buf.data(), buf.size());
// 		if (bytesRead == ft::err)
// 		{
// 			throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));//? error type
// 		}
// 		else if (bytesRead == ft::eof)
// 		{
// 			break ;
// 		}
// 		else
// 		{
// 			result.insert(result.end(), buf.begin(), buf.begin() + bytesRead);
// 		}
// 	}
// 	return (result);
// }

int	xstat(std::string const &path)
{
	struct stat	buf;

	int res = stat(path.c_str(), &buf);

	if (res == ft::err)
		return (FileHandler::INVALID_PATH);
	else if (S_ISDIR(buf.st_mode))
		return (FileHandler::ISDIR);
	else if (S_ISREG(buf.st_mode))
		return (FileHandler::ISFILE);
	else
		return (FileHandler::FILE_EXIST);

}

bool	FileHandler::checkPathExist(std::string const &path)
{
	int res = xstat(path);
	if (res != FileHandler::INVALID_PATH)
		return (true);
	else
		return (false);
}

bool	FileHandler::checkIfDirectory(std::string const &path)
{
	int res = xstat(path);
	if (res == FileHandler::ISDIR)
		return (true);
	else
		return (false);
}

bool	FileHandler::checkIfFile(std::string const &path)
{
	int res = xstat(path);
	if (res == FileHandler::ISFILE)
		return (true);
	else
		return (false);
}

void	FileHandler::assertAccess(std::string const &path, int mode)
{
	if (::access(path.c_str(), mode) == ft::err)
		throw (HttpException(HttpCode::NOT_FOUND));
}
