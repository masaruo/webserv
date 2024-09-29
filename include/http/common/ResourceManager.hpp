#pragma once
#include <string>
#include "HttpUri.hpp"
#include "Config.hpp"

class ResourceManager
{
private:
	HttpUri						uri_;
	config::Config				config_;
	config::Config::location_s	location_;
	std::string					raw_path_;
	std::string					normalized_path_;
	bool						is_directory_;
	ResourceManager();//=delete
	void	normalizeResourcePath(void);
	// void	assertResourcePath(void) const;
	void	handleDots(void);
	void	initializeResource(void);
	void	checkResourceType(void);
public:
	ResourceManager(HttpUri const &uri, config::Config const &config);
	~ResourceManager();
	ResourceManager(ResourceManager const &rhs);
	ResourceManager &operator=(ResourceManager const &rhs);

	std::string	getNormalizedPath(void) const;
	bool		isDirectory(void) const;
	bool		isMethodAllowed(std::string const &method) const;
	bool		isAutoIndexEnabled(void) const;
	std::string	getIndexFile(void) const;
};
