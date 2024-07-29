#include "RequestLine.class.hpp"

RequestLine::RequestLine(ft::string const &line)
{
	// if (line.size() > 8000)
	// {
	// 	//todo 501 error
	// }
	return ;
}

RequestLine::method_t RequestLine::get_methodt(ft::string const &word) const
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
	method_ = get_methodt(split[0]);
}

RequestLine::method_t	RequestLine::getMethod(void) const
{
	return (method_);
}
