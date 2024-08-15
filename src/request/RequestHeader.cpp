#include "RequestHeader.hpp"
#include <utility>

RequestHeader::RequestHeader()
:headers_()
{
	return ;
}

RequestHeader::RequestHeader(ft::string::string_vector const &str_vec)
:headers_()
{
	make_headers(str_vec);
	return ;
}

RequestHeader::~RequestHeader()
{
	return ;
}

RequestHeader::RequestHeader(RequestHeader const &rhs)
:headers_(rhs.headers_)
{
	return ;
}

RequestHeader &RequestHeader::operator=(RequestHeader const &rhs)
{
	if (this != &rhs)
	{
		headers_ = rhs.headers_;
	}
	return (*this);
}

void	RequestHeader::make_headers(ft::string::string_vector const &str_vec)
{
	ft::string::string_vector_const_iterator iter = str_vec.begin();
	ft::string::string_vector_const_iterator end = str_vec.end();

	while (iter != end)
	{
		if (iter->str() == ft::string::CR)
		{
			iter++;
			continue ;
		}
		ft::string	to_split(iter->str());
		to_split.trim(ft::string::CRLF);
		std::string::size_type	found_idx = to_split.str().find_first_of(':');
		std::string	first = to_split.str().substr(0, found_idx);
		std::string	second = to_split.str().substr(found_idx + 2);
		headers_.insert(std::make_pair(first, second));
		iter++;
	}
}

RequestHeader::const_iterator RequestHeader::get_pair(std::string const &key) const
{
	RequestHeader::const_iterator	found;

	found = headers_.find(key);
	return (found);
}

RequestHeader::iterator	RequestHeader::get_pair(std::string const &key)
{
	RequestHeader::iterator	found;

	found = headers_.find(key);
	return (found);
}

std::string	RequestHeader::printHeader(void) const
{
	const_iterator	it = headers_.begin();
	const_iterator	end = headers_.end();
	std::string		res = "";

	while (it != end)
	{
		res += "first " + it->first + " and ";
		res += "second " + it->second + "\n";
		it++;
	}
	return (res);
}
