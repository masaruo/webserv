#include "../../include/config/Config.hpp"
#include "../../include/http/common/HttpStatus.hpp"
#include <iostream>

config::Config::Config(int flag)//!this is MOCK!
{
	if (flag == 1)
	{
		server_name_ = "_";
		port_ = 8888;
		root_ = "/webserv/www/html";
		max_body_size_ = 10000000;
		error_pages_.insert(std::make_pair(HttpCode::NOT_FOUND, "/404.html"));
		error_pages_.insert(std::make_pair(HttpCode::INTERNAL_SERVER_ERROR, "/50x.html"));
		error_pages_.insert(std::make_pair(HttpCode::BAD_GATEWAY, "/50x.html"));
		error_pages_.insert(std::make_pair(HttpCode::SERVICE_UNAVAILABLE, "/50x.html"));
		error_pages_.insert(std::make_pair(HttpCode::GATEWAY_TIMEOUT, "/50x.html"));

//location /
		location_s tmp;
		tmp.index_ = "index.html";
		tmp.allowed_methods_.insert("GET");
		tmp.allowed_methods_.insert("POST");
		tmp.allowed_methods_.insert("DELETE");
		tmp.is_autoindex_ = true;
		tmp.is_cgi_ = false;
		tmp.cgi_root_ = "";
		tmp.cgi_upload_path_ = "";
		locations_.insert(std::make_pair("/", tmp));

//location uploads
		tmp.allowed_methods_.insert("PUT");
		tmp.is_autoindex_ = false;
		tmp.is_cgi_ = false;
		tmp.cgi_root_ = "";
		tmp.cgi_upload_path_ = "/webserv/www/save";
		locations_.insert(std::make_pair("/uploads", tmp));

//location cgi
		tmp.allowed_methods_.insert("");
		tmp.is_autoindex_ = false;
		tmp.is_cgi_ = true;
		tmp.cgi_root_ = "/webserv/cgi-bin";
		tmp.cgi_upload_path_ = "";
		locations_.insert(std::make_pair(".py", tmp));
	}
	else
	{
		server_name_ = "example.com";
		port_ = 7777;
		root_ = "/webserv/www/example";
		max_body_size_ = 5000000;
		error_pages_.insert(std::make_pair(HttpCode::NOT_FOUND, "/404.html"));
		error_pages_.insert(std::make_pair(HttpCode::INTERNAL_SERVER_ERROR, "/50x.html"));
		error_pages_.insert(std::make_pair(HttpCode::BAD_GATEWAY, "/50x.html"));
		error_pages_.insert(std::make_pair(HttpCode::SERVICE_UNAVAILABLE, "/50x.html"));
		error_pages_.insert(std::make_pair(HttpCode::GATEWAY_TIMEOUT, "/50x.html"));

//location /
		location_s tmp;
		tmp.index_ = "index.html";
		tmp.allowed_methods_.insert("GET");
		tmp.is_autoindex_ = true;
		tmp.is_cgi_ = false;
		tmp.cgi_root_ = "";
		tmp.cgi_upload_path_ = "";
		locations_.insert(std::make_pair("/", tmp));
	}
}

config::Config::~Config()
{
	return ;
}

config::Config::Config(Config const &rhs)
:server_name_(rhs.server_name_)
,port_(rhs.port_)
,root_(rhs.root_)
,max_body_size_(rhs.max_body_size_)
,error_pages_(rhs.error_pages_)
,locations_(rhs.locations_)
{
	return ;
}

config::Config &config::Config::operator=(Config const &rhs)
{
	if (this != &rhs)
	{
		server_name_ = rhs.server_name_;
		port_ = rhs.port_;
		root_ = rhs.root_;
		max_body_size_ = rhs.max_body_size_;
		error_pages_ = rhs.error_pages_;
		locations_ = rhs.locations_;
	}
	return (*this);
}

//todo getter
std::string	config::Config::getServerName(void) const
{
	return (server_name_);
}

std::size_t	config::Config::getPort(void) const
{
	return (port_);
}

std::string	config::Config::getRoot(void) const
{
	return (root_);
}

std::size_t	config::Config::getMaxBodySize(void) const
{
	return (max_body_size_);
}

std::string	config::Config::getErrorPage(HttpCode::code_e error_code) const
{
	std::string const	error_path = error_pages_.at(error_code);
	return (error_path);
}

std::size_t	config::Config::getKeepAliveTimeout(void) const
{
	return (keep_alive_timeout_);
}

config::Config::location_s	config::Config::getLocation(std::string const &path) const
{
	if (locations_.find(path) == locations_.end())
		throw (HttpStatus::HttpStatusException(HttpCode::NOT_FOUND));
	location_s loc = locations_.at(path);
	return (loc);
}

std::string	config::Config::getIndex(std::string const &path) const
{
	return (getLocation(path).index_);
}

bool	config::Config::isAllowedMethod(std::string const &path, std::string const &method) const
{
	location_s	loc = getLocation(path);
	if (loc.allowed_methods_.find(method) == loc.allowed_methods_.end())
		return (false);
	else
		return (true);
}

bool	config::Config::isAutoIndex(std::string const &path) const
{
	return (getLocation(path).is_autoindex_);
}

bool	config::Config::isCgi(std::string const &path) const
{
	return (getLocation(path).is_cgi_);
}

std::string	config::Config::getCgiRoot(std::string const &path) const
{
	return (getLocation(path).cgi_root_);
}

std::string	config::Config::getCgiUploadPath(std::string const &path) const
{
	return (getLocation(path).cgi_upload_path_);
}

config::Config::Config(Parser& parse)
{
	Config::setConfig(parse);
}

void	config::Config::setConfig(Parser& parse)
{
	if (parse.consume_token() != "server")
        throw std::runtime_error("invalid config");
    if (parse.consume_token() != "{")
        throw std::runtime_error("invalid config");
    while (parse.get_token() != "}" && parse.get_token() != "\0")
    {
		if (!isPort(parse) \
			&& !isServerName(parse) \
			&& !isRoot(parse) \
			&& !isMaxBodySize(parse) \
			&& !isTimeout(parse) \
			&& !isErrorPage(parse))
			throw std::runtime_error("invalid config");
    }
    if (parse.consume_token() != "}")
        throw std::runtime_error("invalid config");
}

void	config::Config::setServerName(std::string name)
{
	server_name_ = name;
}

void	config::Config::setPort(size_t port)
{
	port_ = port;
}

void	config::Config::setRoot(std::string root)
{
	root_ = root;
}

void	config::Config::setMaxBodySize(size_t size)
{
	max_body_size_ = size;
}

void	config::Config::setErrorPage(HttpCode::code_e code, std::string page)
{
	error_pages_.insert(std::make_pair(code, page));
}

void	config::Config::setKeepAliveTimeout(size_t time)
{
	keep_alive_timeout_ = time;
}

bool	config::Config::isPort(Parser& parse)
{
    if (parse.get_token() != "listen")
        return false;
    parse.consume_token();
    std::stringstream ss;
	size_t port;
    ss << parse.consume_token();
    ss >> port;
	setPort(port);
    if (parse.consume_token() != ";")
        return false;
    return true;
}

bool	config::Config::isServerName(Parser& parse)
{
    if (parse.get_token() != "server_name")
        return false;
    parse.consume_token();
    setServerName(parse.consume_token());
    if (parse.consume_token() != ";")
        return false;
    return true;
}

bool	config::Config::isRoot(Parser& parse)
{
    if (parse.get_token() != "root")
        return false;
    parse.consume_token();
	if (!isnums(parse.get_token()))
		return false;
    setRoot(parse.consume_token());
    if (parse.consume_token() != ";")
        return false;
    return true;
}

bool	config::Config::isMaxBodySize(Parser& parse)
{
    if (parse.get_token() != "max_body_size")
        return false;
    parse.consume_token();
	if (!isnums(parse.get_token()))
		return false;
    std::stringstream ss;
	size_t size;
    ss << parse.consume_token();
    ss >> size;
	setMaxBodySize(size);
    if (parse.consume_token() != ";")
        return false;
    return true;
}

bool	config::Config::isTimeout(Parser& parse)
{
    if (parse.get_token() != "keep_alive_timeout")
        return false;
    parse.consume_token();
	if (!isnums(parse.get_token()))
		return false;
    std::stringstream ss;
	size_t time;
    ss << parse.consume_token();
    ss >> time;
	setKeepAliveTimeout(time);
    if (parse.consume_token() != ";")
        return false;
    return true;
}

bool	config::Config::isErrorPage(Parser& parse)
{
    if (parse.get_token() != "error_page")
        return false;
    parse.consume_token();
	if (!isnums(parse.get_token()))
		return false;
    std::stringstream ss;
    int code;
    ss << parse.consume_token();
    ss >> code;
    std::string error_page = parse.consume_token();
    setErrorPage(HttpCode::code_e(code), error_page);
    if (parse.consume_token() != ";")
        return false;
    return true;
}
