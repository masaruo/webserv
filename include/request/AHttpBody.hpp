#pragma once
#include "HttpHeader.hpp"
#include "define.hpp"
#include <sstream>

class AHttpBody
{
private:
protected:
	ft::str_map				bodies_;
public:
	AHttpBody();
	AHttpBody(std::istringstream &iss, HttpHeader const &headers);
	virtual ~AHttpBody();
	AHttpBody(AHttpBody const &rhs);
	AHttpBody &operator=(AHttpBody const &rhs);
	ft::str_map	parseBodies(std::istringstream &iss, HttpHeader const &headers);
	// virtual std::string	toString(void) const = 0;
	// virtual void		fromString(std::string const &str) = 0;
	// void				setBody(std::string const &key, std::string const &value);
	// std::string			getBody(std::string const &key) const;
	// ft::str_map const	&getBodies(void) const;
	// bool				hasBody(std::string const &key) const;
};
