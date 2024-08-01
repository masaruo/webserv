#include "Request.class.hpp"
#include <stdexcept>
#include <iterator>

Request::Request()
{
	return ;
}

Request::Request(Request const &rhs)
:method_(rhs.method_)
,target_(rhs.target_)
,version_(rhs.version_)
,fields_(rhs.fields_)
{
	return ;
}

Request::~Request()
{
	return ;
}

Request::method_t Request::get_method(ft::string const &line) const
{
	if (line == "GET")
		return (GET);
	else if (line == "POST")
		return (POST);
	else if (line == "DELETE")
		return (DELETE);
	else
	{
		return (ERROR);
		//todo ERROR CODE
	}
}

static void	assert_valid_size(ft::string const &line)
{
	if (line.size() < 2)//CRLF
	{
		//todo request-line too short
	}
	else if (line.size() > 8000)
	{
		//todo error request-line too long
	}
}

static void	assert_end_with_CRLF(ft::string const &line)
{
	ft::string::const_reverse_iterator	lastChar = line.rbegin();
	ft::string::const_reverse_iterator	secondLastChar = line.rbegin();
	std::advance(secondLastChar, 1);
	if (*lastChar != '\n' || *secondLastChar != '\r')
	{
		throw (std::runtime_error("not end iwth crlf"));
		// todo assert fals
	}
}

void	Request::parse_start_line(ft::string &line)
{
	assert_valid_size(line);
	assert_end_with_CRLF(line);
	line.pop();//delete \n at the end
	line.trim(ft::string::WHITESPACE);
	ft::string::string_vector	split;
	split = line.split(ft::string::WHITESPACE);
	//todo assset by size

	method_ = get_method(split[0]);
	target_ = split[1];
	version_ = split[2];
}

Request::method_t	Request::getMethod(void) const
{
	return (method_);
}
