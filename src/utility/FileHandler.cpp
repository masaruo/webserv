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

static int	xstat(std::string const &path)
{
	struct stat	buf;

	int res = stat(path.c_str(), &buf);

	if (res == -1)
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

bool	FileHandler::assertAccess(std::string const &path, int mode)
{
	if (::access(path.c_str(), mode) == -1)
		return (false);
	else
		return (true);
}
