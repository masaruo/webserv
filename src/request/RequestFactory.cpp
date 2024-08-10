#include "RequestFactory.hpp"
#include "RequestLine.hpp"
#include "define.hpp"
#include "Get.hpp"

// ft::unique_ptr<ARequest>	RequestFactory::createRequest(RequestLine const &line)
// {
// 	ft::http_method_t			type = line.get_method();
// 	ft::unique_ptr<ARequest>	ptr;

// 	switch (type)
// 	{		
// 		case (ft::GET):
// 			ptr.reset(new Get(line));
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

ft::unique_ptr<ARequest>	RequestFactory::createRequest(std::string const &raw_request)
{
	ft::string					tmp(raw_request);
	ft::string::string_vector	split_by_lf = tmp.split(ft::string::LF);
	std::string const			method = split_by_lf.at(0).str();
	ft::unique_ptr<ARequest>	ptr;

	if (method == "GET")
		ptr.reset(new Get(raw_request));
	else if (method == "POST")
		;//todo
	else if (method == "DELETE")
		;//todo
	else
		;
	return (ptr); 
}
