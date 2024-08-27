#pragma once
#include <string>
#include "define.hpp"

class FileReader
{
private:
	FileReader(){};
	~FileReader(){};
	FileReader(FileReader const &rhs);
	FileReader &operator=(FileReader const &rhs){ (void) rhs; };
public:
	static std::string		readTextFile(std::string const &path);
	// static std::string	readFdFile(int fd);
	static ft::bytes_vec	readFdFile(int fd);

	//todo error
};
