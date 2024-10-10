#pragma once
#include "VecMap.hpp"
// #include "VecMap.hpp"
// #include <string>
// #include <map>
// #include <set>
// #include <vector>
#include "HttpCode.hpp"

using namespace vm;

namespace config
{
class Config
{
public:
	enum	PathType
	{
		ROOT,
		STATIC,
		UPLOAD,
		CGI,
		REDIRECT,
	};

	enum	DirectiveType
	{
		LISTEN,
		SERVER_NAME,
		ERROR_PAGE,
		LOCATION,
		INDEX,
		ALLOWED_METHOD,
		AUTOINDEX,
		UPLOAD_ROOT,
		CGI_ROOT,
		REDIRECT_TO,
		MAX_BODY_SIZE,
	};

	typedef vm::VecMap<DirectiveType, std::string>		directive_map_t;
	typedef std::map<HttpCode::code_e, std::string>		error_map_t;

	struct Location_s
	{
		PathType		type_;
		// vm::VecMap<DirectiveType, std::string> directive_;
		directive_map_t	directive_;
	};

	typedef std::map<std::string, Location_s>			location_map_t;

private:
	std::size_t		port_;
	std::string		server_name_;
	std::string		root_;
	error_map_t		error_pages_;
	directive_map_t	others_;
	// vm::VecMap<DirectiveType, std::string> others;
	location_map_t	location_;
	Config();//=delete
public:
	// consturctor and destructor
	Config(int flag);//todo delete mock only = mogawa to delete
	Config(std::string const &block);//todo = add default path
	Config(Config const &rhs);
	Config &operator=(Config const &rhs);
	~Config();

	// getter for attributes (ex location)
	std::size_t	getPort(void) const;
	std::string	getServerName(void) const;
	std::string	getRoot(std::string const &path = "") const;
	std::string	getErrorPage(HttpCode::code_e error_code) const;
	std::string	getOtherDirective(DirectiveType type) const;
	Location_s	getLocation(std::string const &path) const;

	// // getter for location directives
	// std::string	getIndex(std::string const &path) const;
	// bool		isAllowedMethod(std::string const &path, std::string const &method) const;
	// bool		isAutoIndex(std::string const &path) const;
	// bool		isCgi(std::string const &path) const;
	// std::string	getCgiRoot(std::string const &path) const;
	// std::string	getUploadStore(std::string const &path) const;
};
}
