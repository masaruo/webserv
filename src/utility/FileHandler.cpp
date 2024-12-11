#include "FileHandler.hpp"
#include "HttpException.hpp"
#include "define.hpp"
#include <fstream>
#include <sys/stat.h>// stat
#include <fcntl.h>

std::string FileHandler::read(std::string const &path)
{
	std::ifstream	ifs(path.c_str(), std::ios::binary);
	if(!ifs)
		throw (HttpException(HttpCode::NOT_FOUND));

	std::stringstream	ss;
	ss << ifs.rdbuf();

	return (ss.str());
}

bool	FileHandler::isDir(std::string const &path, int mode)
{
	struct stat buf;

	int res = stat(path.c_str(), &buf);

	if (res == 0 && S_ISDIR(buf.st_mode))
	{
		int perm = isOK(path, mode);
		if (perm == true)
			return (true);
	}
		return (false);
}

bool	FileHandler::isFile(std::string const &path, int mode)
{
	struct stat buf;

	int res = stat(path.c_str(), &buf);

	if (res == 0 && S_ISREG(buf.st_mode))
	{
		int perm = isOK(path, mode);
		if (perm == true)
			return (true);
	}
	return (false);
}

bool	FileHandler::isExist(std::string const &path)
{
	int res = access(path.c_str(), F_OK);
	if (res == -1)
		return (false);
	else
		return (true);
}

bool	FileHandler::isR_OK(std::string const &path)
{
	int res = access(path.c_str(), R_OK);
	if (res == -1)
		return (false);
	else
		return (true);
}

bool	FileHandler::isW_OK(std::string const &path)
{
	int res = access(path.c_str(), W_OK);
	if (res == -1)
		return (false);
	else
		return (true);
}

bool	FileHandler::isX_OK(std::string const &path)
{
	int res = access(path.c_str(), X_OK);
	if (res == -1)
		return (false);
	else
		return (true);
}

bool	FileHandler::isOK(std::string const &path, int mode)
{
	int res = access(path.c_str(), mode);
	if (res == -1)
		return (false);
	else
		return (true);
}
