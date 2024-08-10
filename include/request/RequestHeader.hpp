#pragma once
#include <map>
#include <string>

class RequestHeader
{
public:
	typedef std::map<std::string, std::string>	header_map;
	typedef header_map::const_iterator			const_iterator;
	typedef header_map::iterator				iterator;
private:
	header_map	headers_;
public:
	RequestHeader();
	~RequestHeader();
	RequestHeader(RequestHeader const &rhs);
	RequestHeader &operator=(RequestHeader const &rhs);

};
