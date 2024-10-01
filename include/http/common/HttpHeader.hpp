#pragma once
#include <map>
#include <vector>
#include <set>
#include <string>
#include "define.hpp"
#include "HttpStatus.hpp"

class HttpHeader
{
public:
	static std::size_t const	MAX_FIELD_LEN = 4096;
	static std::size_t const	MAX_HEADERS = 100;
	typedef std::map<std::string, std::vector<std::string> >	map_vec_t;
	typedef map_vec_t::iterator									iterator;
	typedef map_vec_t::const_iterator							const_iterator;
	typedef map_vec_t::size_type								size_type;
	typedef map_vec_t::difference_type							difference_type;
private:
	map_vec_t						headers_;
	static std::set<std::string>	noDupHeaderSet_;
	void							setHeader(std::string const &line);
	void							setupHeaderWithNoDuplication(void);
	void	assertDupHeaderName(std::string const &name) const;
	void	assertSemanticValue(void) const;
public:
	HttpHeader();
	explicit HttpHeader(std::istringstream &iss);
	~HttpHeader();
	HttpHeader(HttpHeader const &rhs);
	HttpHeader &operator=(HttpHeader const &rhs);
	void		setHeader(std::string const &name, std::string const &value);
	std::string	getFirstValue(std::string const &key) const;
	std::string	getLastValue(std::string const &key) const;
	ft::str_vec	getValues(std::string const &key) const;
	std::size_t	getContentLen(void) const;
	map_vec_t	data(void) const;
	bool		hasHeader(std::string const &key) const;
	std::string	to_string(void) const;
};
