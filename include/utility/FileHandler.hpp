#pragma once
#include <string>
#include "unistd.h"// for access mode and access / read in cpp

class FileHandler
{
private:
	FileHandler(){};
	~FileHandler(){};
	FileHandler(FileHandler const &rhs);
	FileHandler &operator=(FileHandler const &rhs){ (void) rhs; };
public:
	static int const	INVALID_PATH = -1;
	static int const	ISDIR = 1;
	static int const	ISFILE = 2;
	static int const	FILE_EXIST = 3;
	static std::string	read(std::string const &path);
	static std::string	read(int fd);
	static bool			checkPathExist(std::string const &path);
	static bool			checkIfDirectory(std::string const &path);
	static bool			checkIfFile(std::string const &path);
	static void			assertAccess(std::string const &path, int mode);
};
