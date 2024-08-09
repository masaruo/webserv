#include "HttpRequestParser.hpp"
#include "ARequest.hpp"
#include "HttpHeaders.hpp"
#include "HttpRequestLine.hpp"

HttpRequestLine	parseRequestLine(ft::string const &line)
{
	ft::string::string_vector	split_by_sp = line.split(ft::string::WHITESPACE);

	if (split_by_sp.size() != 3)
	{
		//todo error
	}
	ft::string	method = split_by_sp.at(0);
	ft::string	uri = split_by_sp.at(1);
	ft::string	version = split_by_sp.at(2);
	if (method.empty() || uri.empty() || version.empty())
	{
		//todo error
	}
	HttpRequestLine	request_line(method, uri, version);
	return (request_line);
}

HttpHeaders	parseHeaders(ft::string::string_vector const &lines)
{
	HttpHeaders									headers;
	ft::string::string_vector_const_iterator	iter = lines.begin();
	ft::string::string_vector_const_iterator	end = lines.end();

	while (iter != end)
	{
		ft::string::string_vector	split_by_colon = iter->split(":");
		if (split_by_colon.size() != 2)
		{
			//todo error
		}
		ft::string	key = split_by_colon.at(0);
		ft::string	value = split_by_colon.at(1);
		if (key.empty() || value.empty() || !value.start_with(ft::string::SP))//? value empty
		{
			//todo error
		}
		headers.addHeader(key, value);
		iter++;
	}
	return (headers);
}
