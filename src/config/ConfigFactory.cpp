#include "ConfigFactory.hpp"

config::ConfigFactory::ConfigFactory(std::string const &config_path)
{
	// config_pathから読み取ってConfigに入れる
	std::ifstream ifs(config_path);
	if (!ifs)
		throw std::invalid_argument("can not open file.");
	std::istreambuf_iterator<char> it(ifs);
    std::istreambuf_iterator<char> last;
    std::string str(it, last);

	Parser parse(str);
	while (parse.get_token() != "\0")
	{
		Config config(parse);
		configs_.push_back(config);
	}
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

// int main()
// {
// 	config::ConfigFactory a("simple.conf");

// 	std::cout << a.getConfig("localhost").getServerName() << std::endl;
// 	std::cout << a.getConfig("2").getServerName() << std::endl;
// 	std::cout << std::endl;

// 	std::cout << a.getConfig("localhost").getConfigLocation("/").pathType_ << std::endl;
// 	std::cout << a.getConfig("localhost").getConfigLocation("/").directive_.getFirstValue(config::Config::INDEX) << std::endl;
// 	std::cout << a.getConfig("localhost").getConfigLocation("/").directive_.getFirstValue(config::Config::ALLOWED_METHOD) << std::endl;
// 	std::cout << a.getConfig("localhost").getConfigLocation("/").directive_.getLastValue(config::Config::ALLOWED_METHOD) << std::endl;
// 	std::cout << a.getConfig("localhost").getConfigLocation("/").directive_.getFirstValue(config::Config::AUTOINDEX) << std::endl;
	
// 	std::cout << std::endl;

// 	std::cout << a.getConfig("localhost").getConfigLocation("/uploads").pathType_ << std::endl;
// 	std::cout << a.getConfig("localhost").getConfigLocation("/uploads").directive_.getFirstValue(config::Config::ALLOWED_METHOD) << std::endl;
// 	std::cout << a.getConfig("localhost").getConfigLocation("/uploads").directive_.getFirstValue(config::Config::UPLOAD_ROOT) << std::endl;
	
// 	std::cout << std::endl;
	
// 	std::cout << a.getConfig("localhost").getConfigLocation("/redirect").pathType_ << std::endl;
// 	std::cout << a.getConfig("localhost").getConfigLocation("/redirect").directive_.getFirstValue(config::Config::REDIRECT_TO) << std::endl;
// 	std::cout << a.getConfig("localhost").getConfigLocation("/redirect").directive_.getLastValue(config::Config::REDIRECT_TO) << std::endl;

// }
