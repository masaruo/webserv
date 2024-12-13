#pragma once
#include "Config.hpp"
#include <fstream>

namespace config
{
class ConfigFactory
{
private:
	std::vector<Config>	configs_;
	ConfigFactory();//=delete
public:
	ConfigFactory(std::string const &config_path);
	ConfigFactory(ConfigFactory const &rhs);
	ConfigFactory &operator=(ConfigFactory const &rhs);
	~ConfigFactory();
	Config	getDefaultConfig(void) const;
	Config	getConfig(std::string const &server_name, std::size_t port) const;
	std::vector<std::size_t> getAcceptedPorts(void) const;
};
} // namespace config
