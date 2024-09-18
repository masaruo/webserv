#include "env.hpp"
#include "string.hpp"
#include "cstring"

Env::Env(std::string const &uri, HttpHeader const &req_header, HttpBody const &req_body)
:env_(createEnv(uri, req_header, req_body))
{
	return ;
}

Env::~Env()
{
	return ;
}

Env::Env(Env const &rhs)
:env_(rhs.env_)
{
	return ;
}

Env	&Env::operator=(Env const &rhs)
{
	if (this != &rhs)
	{
		env_ = rhs.env_;
	}
	return (*this);
}

ft::str_map	Env::createEnv(std::string const &uri, HttpHeader const &req_header, HttpBody const &req_body)
{
	ft::str_map	env;

	env = to_cppenv();
	env["SERVER_SOFTWARE"] = "test/x.x";
	env["SERVER_NAME"] = "webserv";
	env["GATEWAY_INTERFACE"] = "testCGI/x.x";
	env["SERVER_PROTOCOL"] = "testProtocol/x.x";
	env["SERVER_PORT"] = "7777";
	// env["REQUEST_METHOD"] = req_header.getHeader("METHOD");//*
	env["REQUEST_METHOD"] = "POST";
	env["PATH_INFO"] = uri;
	env["PATH_TRANSLATED"] = uri;//?
	env["SCRIPT_NAME"] = "echo.cgi";
	env["QUERY_STRING"] = "???";//todo get from httpheader
	env["REMOTE_HOST"] = "REMOTE_ADDR";
	env["REMOTE_ADDR"] = "???.???.???.???";//?
	env["AUTH_TYPE"] = "TEST";//?
	env["REMOTE_USER"] = "Is it necessary?";//?
	env["REMOTE_IDENT"] = "Is it necessary?";//?
	env["CONTENT_TYPE"] = req_header.getHeader("Content-Type");
	env["CONTENT_LENGTH"] = req_header.getHeader("Content-Length");
	env["XBODY"] = req_body.str();
	return (env);
}

ft::str_map	Env::to_cppenv(void) const
{
	ft::str_map	env_map;
	extern char	**environ;
	std::size_t	i = 0;

	while (environ[i])
	{
		ft::string	line(environ[i]);
		ft::string::string_vector	split_by_equal = line.split("=");
		env_map.insert(std::make_pair(split_by_equal.at(0), split_by_equal.at(1)));
		i++;
	}
	return (env_map);
}

char	**Env::to_cenv(void) const
{
	char		**c_env = NULL;
	std::size_t	i = 0;
	ft::str_map::const_iterator	it = env_.begin();
	ft::str_map::const_iterator	end = env_.end();

	c_env = new char*[env_.size() + 1]();
	if (c_env == NULL)
	{
		//todo error
	}
	while (it != end)
	{
		std::string	line;
		line = it->first + "=" + it->second;
		c_env[i] = new char[line.size() + 1]();
		std::strcpy(c_env[i], line.c_str());
		if (c_env[i] == NULL)
		{
			//todo error
		}
		i++;
		it++;
	}
	c_env[i] = NULL;
	return (c_env);
}
