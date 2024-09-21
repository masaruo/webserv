#include "ConfigFactory.hpp"

config::ConfigFactory::ConfigFactory(std::string const &config_path)
{
	Config	mockdefault("default");
	Config	mockexample("example");
	configs_.push_back(mockdefault);
	configs_.push_back(mockexample);
	return ;
}

config::ConfigFactory::~ConfigFactory()
{
	return ;
}

config::ConfigFactory::ConfigFactory(ConfigFactory const &rhs)
:configs_(rhs.configs_)
{
	return ;
}

config::ConfigFactory &config::ConfigFactory::operator=(ConfigFactory const &rhs)
{
	if (this != &rhs)
	{
		configs_ = rhs.configs_;
	}
	return (*this);
}

config::Config	config::ConfigFactory::getDefaultConfig(void) const
{
	return (configs_.front());
}

config::Config	config::ConfigFactory::getConfig(std::string const &server_name) const
{
	std::vector<Config>::const_iterator	iter = configs_.begin();
	std::vector<Config>::const_iterator	end = configs_.end();

	while (iter != end)
	{
		std::string	this_server_name = iter->getServerName();
		if (this_server_name == server_name)
		{
			return (*iter);
			break ;
		}
		iter++;
	}
	return (configs_.front());
}
