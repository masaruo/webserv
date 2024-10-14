#pragma once
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
public:
	// consturctor and destructor
	Config(int flag);//todo delete mock only = mogawa to delete
	Config(std::string const &block);//todo = add default path
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
};
}
