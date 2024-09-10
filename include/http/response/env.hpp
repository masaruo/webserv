#pragma once
#include "define.hpp"
#include <string>
#include "HttpHeader.hpp"

class Env
{
private:
	ft::str_map	env_;
	ft::str_map	createEnv(std::string const &uri, HttpHeader const &req_header);
	ft::str_map	to_cppenv(void) const;
	Env();//=delete
public:
	explicit Env(std::string const &uri, HttpHeader const &req_header);//=default
	~Env();
	Env(Env const &rhs);
	Env &operator=(Env const &rhs);
	char		**to_cenv(void) const;
};
