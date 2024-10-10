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
	// void	generateEnv(RequestLine const &line, HttpHeader const &header, std::string const &local_path);
	void	generateEnv(RequestLine const &line, HttpHeader const &header, HttpBody const &body, std::string const &local_path);
	ft::str_map	getEnviron(void) const;
	void	addEnvItem(std::string const &key, std::string const &value);
	Env();//=delete
public:
	// explicit Env(RequestLine const &line, HttpHeader const &header, std::string const &local_path);
	explicit Env(RequestLine const &line, HttpHeader const &header, HttpBody const &body, std::string const &local_path);
	~Env();
	Env(Env const &rhs);
	Env &operator=(Env const &rhs);
	char	**c_env(void) const;
};
