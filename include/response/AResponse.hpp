#pragma once
#include <string>
#include <map>
#include "HttpLine.hpp"
#include "HttpHeader.hpp"

class ARequest;

class AResponse
{
public:
	// typedef std::map<std::string, std::string>	uri_map_t;
	// typedef uri_map_t::iterator					iterator;
	// typedef uri_map_t::const_iterator			const_iterator;
protected:
	int					status_code_;
	HttpLine			line_;
	HttpHeader		header_;
	std::string			body_;
	// static uri_map_t	uri_map_;
public:
	AResponse();
	virtual ~AResponse();
	AResponse(AResponse const &rhs);
	AResponse &operator=(AResponse const &rhs);
	virtual	void		createBody(std::string const &path) = 0;
	virtual	std::string	str(void) const = 0;

	//setter

	//getter
};
