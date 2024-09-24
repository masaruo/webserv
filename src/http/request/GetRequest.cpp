#include "GetRequest.hpp"
#include "GetResponse.hpp"
#include "string.hpp"

ft::str_map	GetRequest::parseQuery(std::string const &uri)
{
	ft::str_map	query;

	std::string::size_type	loc_of_questionmark = uri.find("?");
	if (loc_of_questionmark == std::string::npos)
		return (query);
	std::string	query_str = uri.substr(loc_of_questionmark + 1);
	ft::string to_split(query_str);
	ft::string::string_vector	split_by_ampasand = to_split.split("&");
	ft::string::string_vector_const_iterator iter = split_by_ampasand.begin();
	ft::string::string_vector_const_iterator end = split_by_ampasand.end();
	while (iter != end)
	{
		ft::string::string_vector	split_by_equal = iter->split("=");
		query.insert(std::make_pair(split_by_equal.at(0), split_by_equal.at(1)));
		iter++;
	}
	return (query);
}

GetRequest::GetRequest(RequestLine const &line, HttpHeader const &header, config::Config const &config)
:ARequest(line, header, config)
,query_(parseQuery(line.getUri()))
{
	return ;
}

GetRequest::~GetRequest()
{
	return ;
}

GetRequest::GetRequest(GetRequest const &rhs)
:ARequest(rhs)
{

}

GetRequest &GetRequest::operator=(GetRequest const &rhs)
{
	if (this != &rhs)
	{
		ARequest::operator=(rhs);
	}
	return (*this);
}

GetResponse	*GetRequest::createResponse(void) const
{
	ft::unique_ptr<ARequest>tmp(new GetRequest(*this));
	return (new GetResponse(tmp));
}
