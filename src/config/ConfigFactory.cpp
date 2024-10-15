#include "../../include/config/ConfigFactory.hpp"

config::ConfigFactory::ConfigFactory(std::string const &config_path)
{
	// config_pathから読み取ってConfigに入れる
	std::ifstream ifs(config_path);
	std::istreambuf_iterator<char> it(ifs);
    std::istreambuf_iterator<char> last;
    std::string str(it, last);

	Parser parse(str);
	// while (parse.get_token() != "\0")
	// {
		Config config(parse);
		configs_.push_back(config);
	// }
	configs_[0].getServerName();
	//todo codes
	(void) config_path;
	return ;
}

config::ConfigFactory::ConfigFactory(int flag)//todo delete mock only
{
	(void) flag;
	Config	mockdefault(1);
	Config	mockexample(2);
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

int main()
{
	config::ConfigFactory("simple.conf");
}
