#include "FileHandler.hpp"
#include <fstream>
#include <unistd.h>

std::string FileReader::readTextFile(std::string const &path)
{
	std::ifstream	ifs(path.c_str(), std::ios::in | std::ios::binary);
	if(!ifs)
	{
		//todo error
	}
	std::string	buf;
	ifs.seekg(0, std::ios::end);
	std::streamsize	size = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	buf.resize(static_cast<std::size_t>(size));
	if (!ifs.read(&buf[0], buf.size()))
	{
		//todo error?
	}
	return (buf);
}

std::string	FileReader::readFdFile(int fd)
{
	const std::size_t BUFFSIZE = 4096;
		// ft::bytes_vec	buf(BUFFSIZE);//todo buffer size
		// ft::bytes_vec	result;
	std::string buf(BUFFSIZE, '\0');
	std::string	result;

	while (true)
	{
		ssize_t	bytesRead = read(fd, (void*)buf.data(), buf.size());
		if (bytesRead == ft::err)
		{
			//todo err
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
