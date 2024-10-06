#pragma once
#include <string>
#include <map>
#include <set>
#include <vector>
#include <stdexcept>
#include "HttpCode.hpp"

namespace config
{
class Config
{
public:
	struct location_s
	{
		std::string				index_;
		std::set<std::string>	allowed_methods_;
		bool					is_autoindex_;
		bool					is_cgi_;
		std::string				cgi_root_;
		std::string				upload_store_;
	};
	//! todo implement map str
private:
	std::string								server_name_;
	std::size_t								port_;
	std::string								root_;
	std::size_t								max_body_size_;
	std::map<HttpCode::code_e, std::string>	error_pages_;
	std::size_t								keep_alive_timeout_;
	std::map<std::string, location_s>		locations_;
	Config();//=delete
public:
	// consturctor and destructor
	Config(int flag);//todo delete mock only = mogawa to delete
	Config(std::string const &block);//todo = add default path
	Config(Config const &rhs);
	Config &operator=(Config const &rhs);
	~Config();

	// getter for attributes (ex location)
	std::string	getServerName(void) const;
	std::size_t	getPort(void) const;
	std::string	getRoot(std::string const &path = "/") const;
	std::size_t	getMaxBodySize(void) const;
	std::string	getErrorPage(HttpCode::code_e error_code) const;
	std::size_t	getKeepAliveTimeout(void) const;
	location_s	getLocation(std::string const &path) const;

	// getter for location directives
	std::string	getIndex(std::string const &path) const;
	bool		isAllowedMethod(std::string const &path, std::string const &method) const;
	bool		isAutoIndex(std::string const &path) const;
	bool		isCgi(std::string const &path) const;
	std::string	getCgiRoot(std::string const &path) const;
	std::string	getUploadStore(std::string const &path) const;
};
}
