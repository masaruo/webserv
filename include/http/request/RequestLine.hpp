#pragma once
#include <string>

class RequestLine
{
private:
	std::string	method_;
	std::string	uri_;
	std::string	version_;
public:
	RequestLine();
	RequestLine(std::string const &line);//todo
	~RequestLine();
	RequestLine(RequestLine const &rhs);
	RequestLine &operator=(RequestLine const &rhs);
	void	setMethod(std::string const &inMethod);
	void	setUri(std::string const &inUri);
	void	setVersion(std::string const &inVer);
	std::string	getMethod(void) const;
	std::string	getUri(void) const;
	std::string	getVersion(void) const;
};
