#pragma once
#include <map>
#include <string>

class RequestBody
{
public:
	typedef std::map<std::string, std::string>	form_map_t;
	typedef form_map_t::const_iterator				const_iterator;
	typedef form_map_t::iterator				iterator;
private:
	std::string	raw_body_;
	form_map_t	form_data_;
public:
	RequestBody();
	explicit RequestBody(std::string const &raw_body);
	~RequestBody();
	RequestBody(RequestBody const &rhs);
	RequestBody &operator=(RequestBody const &rhs);
};
