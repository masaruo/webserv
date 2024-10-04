#include "Env.hpp"
#include "string.hpp"
#include "cstring"
#include "HttpException.hpp"

Env::Env(RequestLine const &line, HttpHeader const &header, std::string const &local_path)
:env_(getEnviron())
{
	generateEnv(line, header, local_path);
	return ;
}

Env::Env(RequestLine const &line, HttpHeader const &header, HttpBody const &body, std::string const &local_path)
:env_(getEnviron())
{
	generateEnv(line, header, body, local_path);
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

void	Env::addEnvItem(std::string const &key, std::string const &value)
{
	env_.insert(std::pair<std::string, std::string>(key, value));
}

void	Env::generateEnv(RequestLine const &line, HttpHeader const &header, std::string const &local_path)
{
	HttpUri const	uri = line.getUri();
	std::string const	pathInfo = uri.getPathInfo();
	std::string const	pathTranslated = local_path + "/" + pathInfo;
	std::string const	scriptName = uri.getPath();

	addEnvItem("auth_type", "");
	addEnvItem("content_length", "0");
	addEnvItem("content_type", header.getFirstValue("content-type"));
	addEnvItem("gateway_interface", "CGI/1.1");
	addEnvItem("path_info", pathInfo);
	addEnvItem("path_translated", pathTranslated);
	addEnvItem("query_string", uri.getQueryString());
	addEnvItem("remote_addr", "");//!Must todo
	addEnvItem("remote_host", "");
	addEnvItem("remote_ident", "");
	addEnvItem("remote_user", "");
	addEnvItem("request_method", line.getMethod());
	addEnvItem("script_name", scriptName);
	addEnvItem("server_name", uri.getHost());
	addEnvItem("server_port", uri.getPortStr());
	addEnvItem("server_protocol", "HTTP/1.1");
	addEnvItem("server_software", "webserv");
}

void	Env::generateEnv(RequestLine const &line, HttpHeader const &header, HttpBody const &body, std::string const &local_path)
{
	HttpUri	const	uri = line.getUri();

	// env["auth_type"] = "";
	// env["content_length"] = body.getSizeStr();
	// env["content_type"] = header.getFirstValue("Content-Type");
	// env["gateway_interface"] = "CGI/1.1";
	// env["path_info"] = "";//todo fix
	// env["SERVER_SOFTWARE"] = "test/x.x";
	// env["SERVER_NAME"] = uri.getHost();
	// env["GATEWAY_INTERFACE"] = "testCGI/x.x";
	// env["SERVER_PROTOCOL"] = "testProtocol/x.x";
	// env["SERVER_PORT"] = uri.getPort();
	// env["REQUEST_METHOD"] = line.getMethod();
	// env["PATH_INFO"] = line.getUri().getPath();
	// env["PATH_TRANSLATED"] = "???";//?
	// env["SCRIPT_NAME"] = "echo.cgi";//!
	// env["QUERY_STRING"] = uri.getQueryString();
	// env["REMOTE_HOST"] = "REMOTE_ADDR";
	// env["REMOTE_ADDR"] = "???.???.???.???";//?
	// env["AUTH_TYPE"] = "TEST";//?
	// // env["REMOTE_USER"] = "Is it necessary?";//?
	// // env["REMOTE_IDENT"] = "Is it necessary?";//?
	// env["CONTENT_TYPE"] = header.getFirstValue("Content-Type");
	// env["CONTENT_LENGTH"] = header.getFirstValue("Content-Length");
	// return (env);
}

ft::str_map	Env::getEnviron(void) const
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

char	**Env::c_env(void) const
{
	char		**c_env = NULL;
	std::size_t	i = 0;
	ft::str_map::const_iterator	it = env_.begin();
	ft::str_map::const_iterator	end = env_.end();

	c_env = new char*[env_.size() + 1]();
	if (c_env == NULL)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	while (it != end)
	{
		std::string	line;
		line = it->first + "=" + it->second;
		c_env[i] = new char[line.size() + 1]();
		if (c_env[i] == NULL)
		{
			throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
		}
		std::strcpy(c_env[i], line.c_str());
		i++;
		it++;
	}
	c_env[i] = NULL;
	return (c_env);
}
