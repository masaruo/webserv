#pragma once
#include <string>
// #include "define.hpp"
#include "unistd.h"// for access mode and access / read in cpp

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
	static bool			checkIfDirectory(std::string const &path);
	static void			assertAccess(std::string const &path, int mode);
};
