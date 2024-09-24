#pragma once
#include "Config.hpp"

namespace config
{
class ConfigFactory
{
private:
	std::vector<Config>	configs_;
	ConfigFactory();//=delete
public:
	ConfigFactory(std::string const &config_path);//todo = default path
	ConfigFactory(int flag);//todo delete: mock purpose only
	ConfigFactory(ConfigFactory const &rhs);
	ConfigFactory &operator=(ConfigFactory const &rhs);
	~ConfigFactory();
	Config	getDefaultConfig(void) const;
	Config	getConfig(std::string const &server_name) const;
	std::vector<std::size_t> getAcceptedPorts(void) const;//! at init to set up listen ports

	class ConfigFactoryException : public std::runtime_error
	{
	public:
		ConfigFactoryException(std::string const &msg)
		:std::runtime_error(msg)
		{
			return ;
		};
	};
};
} // namespace config
