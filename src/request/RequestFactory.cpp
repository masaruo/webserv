#include "RequestFactory.hpp"
#include "HttpLine.hpp"
#include "define.hpp"
#include "GetRequest.hpp"

// ft::unique_ptr<ARequest>	RequestFactory::createRequest(RequestLine const &line)
// {
// 	ft::http_method_t			type = line.get_method();
// 	ft::unique_ptr<ARequest>	ptr;

// 	switch (type)
// 	{		
// 		case (ft::GET):
// 			ptr.reset(new GetRequest(line));
// 			break ;
// 		case (ft::POST):
// 			//todo post
// 			break ;
// 		case (ft::DELETE):
// 			//todo delete
// 			break ;		default:
// 			//todo error
// 	}
// 	return (ptr);
// }

ARequest	*RequestFactory::createRequest(std::string const &raw_request)
{
	ft::string					tmp(raw_request);
	ft::string::string_vector	split_by_spaces = tmp.split(ft::string::WHITESPACE);
	std::string const			method = split_by_spaces.at(0).str();

	if (method == "GET")
		return (new GetRequest(raw_request));
	else if (method == "POST")
		return (NULL);
	else if (method == "DELETE")
		return (NULL);
	else
		return (NULL);
}
