#include "Config.hpp"

config::Config::Config(std::string const &block)//!this is MOCK!
{
	if (block == "default")
	{
		server_name_ = "_";
		port_ = 8888;
		root_ = "/webserv/www/html";
		index_ = "index.html";
		max_body_size_ = 10000000;
		error_pages_.insert(std::make_pair(404, "/404.html"));
		error_pages_.insert(std::make_pair(500, "/50x.html"));
		error_pages_.insert(std::make_pair(502, "/50x.html"));
		error_pages_.insert(std::make_pair(503, "/50x.html"));
		error_pages_.insert(std::make_pair(504, "/50x.html"));

//location /
		location_s tmp;
		tmp.allowed_methods_.insert("GET");
		tmp.allowed_methods_.insert("POST");
		tmp.allowed_methods_.insert("DELETE");
		tmp.is_autoindex_ = true;
		tmp.is_cgi_ = false;
		tmp.cgi_root_ = "";
		tmp.upload_path_ = "";
		locations_.insert(std::make_pair("/", tmp));

//location uploads
		tmp.allowed_methods_.insert("PUT");
		tmp.is_autoindex_ = false;
		tmp.is_cgi_ = false;
		tmp.cgi_root_ = "";
		tmp.upload_path_ = "/webserv/www/save";
		locations_.insert(std::make_pair("/uploads", tmp));

//location cgi
		tmp.allowed_methods_.insert("");
		tmp.is_autoindex_ = false;
		tmp.is_cgi_ = true;
		tmp.cgi_root_ = "/webserv/cgi-bin";
		tmp.upload_path_ = "";
		locations_.insert(std::make_pair(".py", tmp));
	}
	else
	{
		server_name_ = "example.com";
		port_ = 7777;
		root_ = "/webserv/www/example";
		index_ = "index.html";
		max_body_size_ = 5000000;
		error_pages_.insert(std::make_pair(404, "/404.html"));
		error_pages_.insert(std::make_pair(500, "/50x.html"));
		error_pages_.insert(std::make_pair(502, "/50x.html"));
		error_pages_.insert(std::make_pair(503, "/50x.html"));
		error_pages_.insert(std::make_pair(504, "/50x.html"));

//location /
		location_s tmp;
		tmp.allowed_methods_.insert("GET");
		tmp.is_autoindex_ = true;
		tmp.is_cgi_ = false;
		tmp.cgi_root_ = "";
		tmp.upload_path_ = "";
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
,index_(rhs.index_)
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
		index_ = rhs.index_;
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
