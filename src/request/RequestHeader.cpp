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
		ft::string::string_vector	split_by_doubleColon = iter->split(":");
		//todo ERROR and verfication
		split_by_doubleColon.at(1).trim(ft::string::SP);
		headers_.insert(std::make_pair(split_by_doubleColon.at(0), split_by_doubleColon.at(1)));
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
