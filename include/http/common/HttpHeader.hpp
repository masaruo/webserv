#pragma once
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include "define.hpp"
#include "Binary.hpp"

class HttpHeader
{
public:
	typedef std::map<std::string, std::vector<std::string> >	map_vec_t;
	typedef map_vec_t::iterator									iterator;
	typedef map_vec_t::const_iterator							const_iterator;
	typedef map_vec_t::size_type								size_type;
	typedef map_vec_t::difference_type							difference_type;
private:
	map_vec_t	headers_;
	void		setHeader(std::string const &line);
public:
	HttpHeader();
	explicit HttpHeader(std::istringstream &iss);
	~HttpHeader();
	HttpHeader(HttpHeader const &rhs);
	HttpHeader &operator=(HttpHeader const &rhs);
	void		setHeader(std::string const &key, std::string const &value);
	std::string	getValue(std::string const &key) const;
	map_vec_t	data(void) const;
	bool		hasHeader(std::string const &key) const;
	ft::string	str(void) const;
};
