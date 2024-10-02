#include "Config.hpp"
#include "HttpException.hpp"

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
		tmp.upload_store_ = "";
		locations_.insert(std::make_pair("/", tmp));

//location uploads
		location_s tmp2;
		tmp2.allowed_methods_.insert("PUT");
		tmp2.allowed_methods_.insert("DELETE");
		tmp2.is_autoindex_ = false;
		tmp2.is_cgi_ = false;
		tmp2.cgi_root_ = "";
		tmp2.upload_store_ = "/webserv/www/save";
		// locations_.insert(std::make_pair("/uploads", tmp));
		locations_.insert(std::make_pair("/uploads", tmp2));//! no / at first

//location cgi
		location_s tmp3;
		tmp3.allowed_methods_.insert("");
		tmp3.is_autoindex_ = false;
		tmp3.is_cgi_ = true;
		tmp3.cgi_root_ = "/webserv/cgi-bin";
		tmp3.upload_store_ = "";
		locations_.insert(std::make_pair("/.py", tmp3));
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
		tmp.upload_store_ = "";
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
	std::map<HttpCode::code_e, std::string>::size_type	findCount;
	findCount = error_pages_.count(error_code);

	if (findCount == 0)
		return ("");

	std::string const	error_path = error_pages_.at(error_code);
	return (error_path);
}

std::size_t	config::Config::getKeepAliveTimeout(void) const
{
	return (keep_alive_timeout_);
}

config::Config::location_s	config::Config::getLocation(std::string const &path) const
{
	location_s	loc;
	if (locations_.find(path) == locations_.end())
		loc = locations_.at("/");
	else
		loc = locations_.at(path);
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

std::string	config::Config::getUploadStore(std::string const &path) const
{
	return (getLocation(path).upload_store_);
}
