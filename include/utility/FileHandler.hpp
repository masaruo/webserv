#pragma once
#include <string>
#include "unistd.h"// for access mode and access / read in cpp

class FileHandler
{
private:
	FileHandler(){};
	~FileHandler(){};
	FileHandler(FileHandler const &rhs);//=delete
	FileHandler &operator=(FileHandler const &rhs);//=delete
public:
	static std::string	read(std::string const &path);
	// static bool			checkPathExist(std::string const &path);
	static bool			isDir(std::string const &path, int mode = F_OK);
	static bool			isFile(std::string const &path, int mode = F_OK);
	// static bool			assertAccess(std::string const &path, int mode);
	static bool			isExist(std::string const &path);
	static bool			isR_OK(std::string const &path);
	static bool			isX_OK(std::string const &path);
	static bool			isW_OK(std::string const &path);
	static bool			isOK(std::string const &path, int mode);
};
