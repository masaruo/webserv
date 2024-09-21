#pragma once
#include "define.hpp"
#include <string>
#include "HttpHeader.hpp"
#include "HttpBody.hpp"
#include "RequestLine.hpp"

class Env
{
private:
	ft::str_map	env_;
	ft::str_map	createEnv(RequestLine const &line, HttpHeader const &header, HttpBody const &body);
	ft::str_map	to_cppenv(void) const;
	Env();//=delete
public:
	explicit Env(RequestLine const &line, HttpHeader const &header, HttpBody const &body);
	~Env();
	Env(Env const &rhs);
	Env &operator=(Env const &rhs);
	char	**to_cenv(void) const;
};
