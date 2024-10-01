#pragma once
#include <vector>
#include "string.hpp"
#include <ostream>
#include <stdint.h>

class Binary
{
public:
	typedef std::vector<uint8_t>		vec_bytes;
	typedef vec_bytes::const_iterator	const_iterator;
	typedef vec_bytes::iterator			iterator;
	typedef vec_bytes::size_type		size_type;
	typedef vec_bytes::difference_type	difference_type;
private:
	vec_bytes	data_;
	vec_bytes	fromStr(std::string const &str) const;
public:
	explicit Binary();
	explicit Binary(std::string const &str);
	explicit Binary(vec_bytes const &bytes);
	~Binary();
	Binary(Binary const &rhs);
	Binary	&operator=(Binary const &rhs);
	Binary	&operator<<(Binary const &rhs);
	std::string	toStr(void) const;
	vec_bytes	data(void) const;
};
