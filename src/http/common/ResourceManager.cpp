#include "ResourceManager.hpp"
#include "HttpStatus.hpp"
#include <sys/stat.h>
#include <algorithm>
#include <string.hpp>
#include <define.hpp>
#include <sstream>
#include <iterator>

ResourceManager::ResourceManager(HttpUri const &uri, config::Config const &config)
:uri_(uri)
,config_(config)
,location_()
,raw_path_()
,normalized_path_()
,is_directory_(false)
{
	initializeResource();
	return ;
}

ResourceManager::~ResourceManager()
{
	return ;
}

ResourceManager::ResourceManager(ResourceManager const &rhs)
:uri_(rhs.uri_)
,config_(rhs.config_)
,location_(rhs.location_)
,raw_path_(rhs.raw_path_)
,normalized_path_(rhs.normalized_path_)
,is_directory_(rhs.is_directory_)
{
	return ;
}

ResourceManager &ResourceManager::operator=(ResourceManager const &rhs)
{
	if (this != &rhs)
	{
		uri_ = rhs.uri_;
		config_ = rhs.config_;
		location_ = rhs.location_;
		raw_path_ = rhs.raw_path_;
		normalized_path_ = rhs.normalized_path_;
		is_directory_ = rhs.is_directory_;
	}
	return (*this);
}

void	ResourceManager::initializeResource(void)
{
	std::string path = uri_.getPath();
	try
	{
		location_ = config_.getLocation(path);
	}
	catch(HttpStatus::HttpStatusException const &e)
	{
		location_ = config_.getLocation("/");
	}
	raw_path_ = config_.getRoot() + path;
	checkResourceType();
	// normalizeResourcePath();re
}

void	ResourceManager::checkResourceType(void)
{
	struct stat	st;
	if (stat(raw_path_.c_str(), &st) == 0)
	{
		is_directory_ = S_ISDIR(st.st_mode);
	}
	else
	{
		throw (HttpStatus::HttpStatusException(HttpCode::NOT_FOUND));
	}
}

std::string	ResourceManager::getNormalizedPath(void) const
{
	return (normalized_path_);
}

bool	ResourceManager::isDirectory(void) const
{
	return (is_directory_);
}

bool	ResourceManager::isMethodAllowed(std::string const &method) const
{
	bool is_allowd = config_.isAllowedMethod(uri_.getPath(), method);
	return (is_allowd);
}

bool	ResourceManager::isAutoIndexEnabled(void) const
{
	return (config_.isAutoIndex(uri_.getPath()));
}

std::string	ResourceManager::getIndexFile(void) const
{
	return (config_.getIndex(uri_.getPath()));
}
