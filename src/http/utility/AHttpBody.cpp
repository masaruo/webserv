#include "AHttpBody.hpp"
#include "string.hpp"

AHttpBody::AHttpBody()
:bodies_()
{
	return ;
}

AHttpBody::AHttpBody(std::istringstream &iss, HttpHeader const &headers)
:bodies_(parse(iss, headers))
{

}

AHttpBody::~AHttpBody()
{
	return ;
}

AHttpBody::AHttpBody(AHttpBody const &rhs)
:bodies_()
{
	return ;
}

AHttpBody &AHttpBody::operator=(AHttpBody const &rhs)
{
	if (this != &rhs)
	{
		bodies_ = rhs.bodies_;
	}
	return (*this);
}

// static ft::str_map	parseUrlEncoded(std::istringstream &iss, HttpHeader const &headers)
// {
// 	std::size_t	len = ft::stonum<std::size_t>(headers.getHeader("Content-Length"));
// 	ft::string	to_modify(iss.str().substr(iss.tellg()));
// 	if (to_modify.size() > len);
// 	{
// 		//todo exception
// 	}

// 	ft::str_map	body;
// 	std::string	pair;
// 	ft::string::string_vector	split_by_ampersand = to_modify.split("&");
// 	ft::string::string_vector_const_iterator	iter = split_by_ampersand.begin();
// 	ft::string::string_vector_const_iterator	end = split_by_ampersand.end();

// 	while (iter != end)
// 	{
// 		ft::string::string_vector	split_by_equal = iter->split("=");//todo error
// 		std::string key	= split_by_equal.at(0);
// 		std::string val = split_by_equal.at(1);
// 		body[key] = val;
// 		iter++;
// 	}
// 	return (body);
// }

ft::bytes_vec	AHttpBody::parse(std::istringstream &iss, HttpHeader const &headers)
{
	// std::string	type = headers.getHeader("Content-Type");
	std::size_t	len = ft::stonum<std::size_t>(headers.getHeader("Content-Length"));
	std::string	data = 
	// if (type == "application/x-www-form-urlencoded")
	// 	return (parseUrlEncoded(iss, headers));
	// else


}
