#include "ConfigFactory.hpp"
#include <algorithm>

config::ConfigFactory::ConfigFactory(std::string const &config_path)
{
	// config_pathから読み取ってConfigに入れる
	std::ifstream ifs(config_path.c_str());
	if (!ifs)
		throw std::invalid_argument("can not open file.");
	std::istreambuf_iterator<char> it(ifs);
    std::istreambuf_iterator<char> last;
    std::string str(it, last);
	if (str == "\0")
		throw std::invalid_argument("config file is empty.");

	Parser parse(str);
	while (parse.get_token() != "\0")
	{
		Config config(parse);
		configs_.push_back(config);
	}
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

config::Config	config::ConfigFactory::getConfig(std::string const &server_name, std::size_t port) const
{
	std::vector<Config>::const_iterator	iter = configs_.begin();
	std::vector<Config>::const_iterator	wildcard_config = configs_.end();
	std::vector<Config>::const_iterator	default_config = configs_.end();

	while (iter != configs_.end())
	{
		std::string	const &this_name = iter->getServerName();
		if (iter->getPort() == port)
		{
			if (this_name == server_name)
				return (*iter);
			if (this_name == "_")
				wildcard_config = iter;
			if (default_config == configs_.end())
				default_config = iter;
		}
		iter++;
	}

	if (wildcard_config != configs_.end())
		return (*wildcard_config);
	if (default_config != configs_.end())
		return (*default_config);
	throw (HttpException(HttpCode::BAD_REQUEST));
}

std::vector<std::size_t> config::ConfigFactory::getAcceptedPorts(void) const
{
	std::vector<size_t>			ports;

	for(size_t i = 0; i < configs_.size(); i++)
		ports.push_back(configs_[i].getPort());
	std::vector<std::size_t>::iterator new_end = std::unique(ports.begin(), ports.end());
	ports.erase(new_end, ports.end());
	return (ports);
}

// int main()
// {
// 	try
// 	{
// 		config::ConfigFactory a("simple.conf");
// 		// std::cout << a.getConfig("localhost").getServerName() << std::endl;
// 		// std::cout << a.getConfig("2").getServerName() << std::endl;
// 		// std::cout << std::endl;

// 		// std::cout << a.getConfig("localhost").getConfigLocation("/").pathType_ << std::endl;
// 		// std::cout << a.getConfig("localhost").getConfigLocation("/").directive_.getFirstValue(config::Config::INDEX) << std::endl;
// 		// std::cout << a.getConfig("localhost").getConfigLocation("/").directive_.getFirstValue(config::Config::ALLOWED_METHOD) << std::endl;
// 		// std::cout << a.getConfig("localhost").getConfigLocation("/").directive_.getLastValue(config::Config::ALLOWED_METHOD) << std::endl;
// 		// std::cout << a.getConfig("localhost").getConfigLocation("/").directive_.getFirstValue(config::Config::AUTOINDEX) << std::endl;
		
// 		// std::cout << std::endl;

// 		// std::cout << a.getConfig("localhost").getConfigLocation("/uploads").pathType_ << std::endl;
// 		// std::cout << a.getConfig("localhost").getConfigLocation("/uploads").directive_.getFirstValue(config::Config::ALLOWED_METHOD) << std::endl;
// 		// std::cout << a.getConfig("localhost").getConfigLocation("/uploads").directive_.getFirstValue(config::Config::UPLOAD_ROOT) << std::endl;
		
// 		// std::cout << std::endl;
		
// 		// std::cout << a.getConfig("localhost").getConfigLocation("/redirect").pathType_ << std::endl;
// 		// std::cout << a.getConfig("localhost").getConfigLocation("/redirect").directive_.getFirstValue(config::Config::REDIRECT_TO) << std::endl;
// 		// std::cout << a.getConfig("localhost").getConfigLocation("/redirect").directive_.getLastValue(config::Config::REDIRECT_TO) << std::endl;

// 		std::vector<std::size_t> ports = a.getAcceptedPorts();
// 		for (int i = 0; i < ports.size(); i++)
// 			std::cout << ports[i] << std::endl;
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}
// }
