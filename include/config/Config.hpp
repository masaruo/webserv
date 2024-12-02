#pragma once
#include <string>
#include <map>
#include <set>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "HttpCode.hpp"
#include "Parser.hpp"

class Parser;
#include "VecMap.hpp"
#include "HttpCode.hpp"

namespace config
{
class Config
{
public:
	enum	PathType
	{
		ROOT_PATH,
		STATIC_PATH,
		UPLOAD_PATH,
		CGI_PATH,
		REDIRECTION_PATH,
	};

	enum	DirectiveType
	{
		// LISTEN,
		// SERVER_NAME,
		// ERROR_PAGE,
		LOCATION,
		INDEX,
		ALLOWED_METHOD,
		AUTOINDEX,
		UPLOAD_ROOT,
		CGI_ROOT,
		REDIRECT_TO,
		MAX_BODY_SIZE,
	};

	typedef vm::VecMap<DirectiveType, std::string>	DirectiveMap;
	typedef std::map<HttpCode::StatusCode, std::string>	ErrorPageMap;

	struct LocationConfig
	{
		PathType		pathType_;
		DirectiveMap	directive_;
	};

	typedef std::map<std::string, LocationConfig>	LocationConfigMap;

private:
	std::size_t			port_;
	std::string			server_name_;
	std::string			root_;
	ErrorPageMap		error_pages_;
	DirectiveMap		others_;
	LocationConfigMap	location_;
	Config();//=delete

	// setter
	void	setConfig(Parser& parse);
	void	setServerName(std::string name);
	void	setPort(size_t port);
	void	setRoot(std::string root);
	void	setMaxBodySize(std::string size);
	void	setErrorPage(HttpCode::StatusCode code, std::string page);
	void	setLocation(Parser& parse, LocationConfig& location, std::string location_path);
	void	setIndex(std::string index, LocationConfig& location);
	void	setMethod(std::string method, LocationConfig& location);
	void	setAoutIndex(std::string aout_index, LocationConfig& location);
	void	setUploadRoot(std::string upload_root, LocationConfig& location);
	void	setCgiRoot(std::string cgi_root, LocationConfig& location);
	void	setRedirect(std::string redirect, LocationConfig& location);

	// bool
	bool	isPort(Parser& parse);
	bool	isServerName(Parser& parse);
	bool	isRoot(Parser& parse);
	bool	isMaxBodySize(Parser& parse);
	bool	isErrorPage(Parser& parse);
	bool	isLocation(Parser& parse);
	bool	isIndex(Parser& parse, LocationConfig& location);
	bool	isMethod(Parser& parse, LocationConfig& location);
	bool	isAoutIndex(Parser& parse, LocationConfig& location);
	bool	isUploadRoot(Parser& parse, LocationConfig& location);
	bool	isCgiRoot(Parser& parse, LocationConfig& location);
	bool	isRedirect(Parser& parse, LocationConfig& location);
public:
	// consturctor and destructor
	Config(int flag);//todo delete mock only = mogawa to delete
	Config(std::string const &block);//todo = add default path
	Config(Parser& parse);
	Config(Config const &rhs);
	Config &operator=(Config const &rhs);
	~Config();

	// getter for attributes (ex location)
	std::size_t		getPort(void) const;
	std::string		getServerName(void) const;
	std::string		getRoot(std::string const &path = "") const;
	ErrorPageMap	getErrorPageMap(void) const;
	std::string		getErrorPage(HttpCode::StatusCode error_code) const;
	std::string		getOtherDirective(DirectiveType type) const;
	LocationConfig	getConfigLocation(std::string const &path) const;

	// exception
	class ConfigErrorException : public std::exception {
		private:
			std::string msg_;
		public:
			~ConfigErrorException() throw() {};
			ConfigErrorException(size_t line);
			ConfigErrorException(size_t line, std::string msg);
			const char* what() const throw() { return msg_.c_str(); };
	};
};
}