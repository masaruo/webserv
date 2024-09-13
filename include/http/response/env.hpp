#pragma once
#include "define.hpp"
#include <string>
#include "HttpHeader.hpp"
#include "HttpBody.hpp"

class Env
{
private:
	ft::str_map	env_;
	ft::str_map	createEnv(std::string const &uri, HttpHeader const &req_header, HttpBody const &req_body);
	ft::str_map	to_cppenv(void) const;
	Env();//=delete
public:
	explicit Env(std::string const &uri, HttpHeader const &req_header, HttpBody const &req_body);//=default
	~Env();
	Env(Env const &rhs);
	Env &operator=(Env const &rhs);
	char		**to_cenv(void) const;
};
