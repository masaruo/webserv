#pragma once
#include <map>
#include <string>

class MockPath
{
private:
	std::map<std::string, std::string> mockpath_;
public:
	MockPath()
	{
		mockpath_["/"] = "/webserv/www/index.html";
		mockpath_["/echo"] = "/webserv/cgi-bin/echo.cgi";
		mockpath_["/upload.cgi"] = "/webserv/cgi-bin/upload.cgi";
		mockpath_["/delete"] = "/webserv/cgi-bin/delete.cgi";
	}
	std::string getPath(std::string key)
	{
		return (mockpath_.at(key));
	}
};


