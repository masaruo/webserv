#pragma once
#include <string>
#include <sstream>

class RequestLine
{
private:
	std::string	method_;
	std::string	uri_;
	std::string	version_;
	void	setMethod(std::string const &inMethod);
	void	setUri(std::string const &inUri);
	void	setVersion(std::string const &inVer);
	RequestLine();//=delete
public:
	RequestLine(std::istringstream &iss);
	~RequestLine();
	RequestLine(RequestLine const &rhs);
	RequestLine &operator=(RequestLine const &rhs);
	std::string	getMethod(void) const;
	std::string	getUri(void) const;
	std::string	getVersion(void) const;
	//todo exceptions
};
