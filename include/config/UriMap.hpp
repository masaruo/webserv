#pragma once
#include <map>
#include <string>
#include <unique_ptr.hpp>

//todo incomplete

class UriMap
{
public:
	typedef std::map<std::string, std::string>	uri_map_t;
	typedef uri_map_t::iterator					iterator;
	typedef uri_map_t::const_iterator			const_iterator;
private:
	static ft::unique_ptr<UriMap>	instance_;
	uri_map_t						uri_map_;
	UriMap(){};
	UriMap(UriMap const &rhs){};
	UriMap &operator=(UriMap const &rhs){(void)rhs;};
	~UriMap(){};
public:
	static UriMap	&getInstance(void);
	std::string		getAbsPath(std::string const &path) const;
};
