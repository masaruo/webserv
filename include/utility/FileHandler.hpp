#pragma once
#include <string>
#include "define.hpp"

class FileHandler
{
private:
	FileHandler(){};
	~FileHandler(){};
	FileHandler(FileHandler const &rhs);
	FileHandler &operator=(FileHandler const &rhs){ (void) rhs; };
public:
	static std::string	read(std::string const &path);
	static std::string	read(int fd);
	static bool			isDir(std::string const &path);
};
