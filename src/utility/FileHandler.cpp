#include "FileHandler.hpp"
#include <fstream>

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
