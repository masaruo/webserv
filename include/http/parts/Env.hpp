#pragma once
#include "define.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"
#include "RequestLine.hpp"
#include <string>

class Env
{
private:
	ft::str_map	env_;

	ft::str_map	getEnviron(void) const;
	void	addCGIEnv(RequestLine const &line, HttpHeader const &header, HttpBody const &body);
public:
	explicit Env(RequestLine const &line, HttpHeader const &header, HttpBody const &body);
	Env();//=delete
	~Env();
	Env(Env const &rhs);
	Env &operator=(Env const &rhs);
	void	addEnvItem(std::string const &key, std::string const &value);
	char	**c_env(void) const;
};
