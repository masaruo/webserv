#pragma once
#include <string>

class FileReader
{
private:
	FileReader(){};
	~FileReader(){};
	FileReader(FileReader const &rhs);
	FileReader &operator=(FileReader const &rhs){ (void) rhs; };
public:
	static std::string	readTextFile(std::string const &path);
	//todo error
};
