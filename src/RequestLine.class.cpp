#include "RequestLine.class.hpp"

RequestLine::RequestLine(ft::string const &line)
{
	parse_line(line);
	// if (line.size() > 8000)
	// {
	// 	//todo 501 error
	// }
	return ;
}

RequestLine::method_t RequestLine::get_method(ft::string const &word) const
{
	if (word == "GET")
		return (GET);
	else if (word == "POST")
		return (POST);
	else if (word == "DELETE")
		return (DELETE);
	else
	{
		return (ERROR);
		//todo ERROR CODE
	}
}

void	RequestLine::parse_line(ft::string const &line)
{
	ft::string::string_vector	split;

	split = line.split(" ");

	method_ = get_method(split[0]);
	target_ = split[1];
	version_ = split[2];
}

RequestLine::method_t	RequestLine::getMethod(void) const
{
	return (method_);
}
