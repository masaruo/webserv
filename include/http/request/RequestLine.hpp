#pragma once
#include <string>
#include <stdexcept>
#include "HttpStatus.hpp"
#include "HttpUri.hpp"

class RequestLine
{
private:
	std::size_t const	URI_MAX_LEN = 1024;//? from config?
	std::string	method_;
	HttpUri		uri_;
	// std::string	uri_;
	std::string	version_;
	void	setMethod(std::string const &inMethod);
	void	setVersion(std::string const &inVer);
	RequestLine();//=delete
public:
	explicit RequestLine(std::istringstream &iss);
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
