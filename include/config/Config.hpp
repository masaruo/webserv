#pragma once
#include <string>
#include <map>
#include <set>
#include <vector>
#include <stdexcept>
#include "../http/common/HttpCode.hpp"
#include "Server.hpp"

class Parser;

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
		std::string				cgi_upload_path_;
	};
private:
	std::string								server_name_;
	std::size_t								port_;
	std::string								root_;
	std::size_t								max_body_size_;
	std::map<HttpCode::code_e, std::string>	error_pages_;
	std::size_t								keep_alive_timeout_;
	std::map<std::string, location_s>		locations_;
	location_s	getLocation(std::string const &path) const;
	Config();//=delete

	// setter
	void	setConfig(Parser& parse);
	void	setServerName(std::string name);
	void	setPort(size_t port);
	void	setRoot(std::string root);
	void	setMaxBodySize(size_t size);
	void	setErrorPage(HttpCode::code_e code, std::string page);
	void	setKeepAliveTimeout(size_t time);

	// bool
	bool	isPort(Parser& parse);
	bool	isServerName(Parser& parse);
	bool	isRoot(Parser& parse);
	bool	isMaxBodySize(Parser& parse);
	bool	isTimeout(Parser& parse);
	bool	isErrorPage(Parser& parse);
public:
	// consturctor and destructor
	Config(int flag);//todo delete mock only = mogawa to delete
	Config(std::string const &block);//todo = add default path
	Config(Parser& parse);
	Config(Config const &rhs);
	Config &operator=(Config const &rhs);
	~Config();

	// getter for attributes (ex location)
	std::string	getServerName(void) const;
	std::size_t	getPort(void) const;
	std::string	getRoot(void) const;
	std::size_t	getMaxBodySize(void) const;
	std::string	getErrorPage(HttpCode::code_e error_code) const;
	std::size_t	getKeepAliveTimeout(void) const;

	// getter for location directives
	std::string	getIndex(std::string const &path) const;
	bool		isAllowedMethod(std::string const &path, std::string const &method) const;
	bool		isAutoIndex(std::string const &path) const;
	bool		isCgi(std::string const &path) const;
	std::string	getCgiRoot(std::string const &path) const;
	std::string	getCgiUploadPath(std::string const &path) const;
};
}
