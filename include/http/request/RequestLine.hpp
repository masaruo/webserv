#pragma once
#include <string>
// #include <stdexcept>
#include "HttpStatus.hpp"
#include "HttpUri.hpp"

class RequestLine
{
private:
	std::string	method_;
	HttpUri		uri_;
	std::string	version_;
	void		setMethod(std::string const &inMethod);
	void		setVersion(std::string const &inVer);
public:
	RequestLine();
	// explicit RequestLine(std::istringstream &iss);
	explicit RequestLine(std::string const &line);
	~RequestLine();
	RequestLine(RequestLine const &rhs);
	RequestLine &operator=(RequestLine const &rhs);
	void		setUri(std::string const &inUri);
	void		constructUri(std::string const &host_value);
	std::string	getMethod(void) const;
	HttpUri		getUri(void) const;
	HttpUri		&getUriReference(void);
	std::string	getVersion(void) const;
};
