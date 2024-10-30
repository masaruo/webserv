#include <iostream>
#include "Config.hpp"
#include "HttpException.hpp"
#include "string.hpp"

namespace config
{

Config::Config(int flag)//!this is MOCK!
{
	(void) flag;

	// main directives
	port_ = 80;
	server_name_ = "_";
	root_ = "/webserv/www/html";
	others_.addValue(MAX_BODY_SIZE, "60000000");
	error_pages_.insert(std::make_pair(HttpCode::NOT_FOUND, "/404.html"));
	error_pages_.insert(std::make_pair(HttpCode::METHOD_NOT_ALLOWED, "/405.html"));
	error_pages_.insert(std::make_pair(HttpCode::INTERNAL_SERVER_ERROR, "/50x.html"));
	error_pages_.insert(std::make_pair(HttpCode::BAD_GATEWAY, "/50x.html"));
	error_pages_.insert(std::make_pair(HttpCode::SERVICE_UNAVAILABLE, "/50x.html"));
	error_pages_.insert(std::make_pair(HttpCode::GATEWAY_TIMEOUT, "/50x.html"));

	// locations
	DirectiveMap	slash;
	slash.addValue(INDEX, "index.html");
	slash.addValue(ALLOWED_METHOD, "GET");
	// slash.addValue(ALLOWED_METHOD, "POST");
	// slash.addValue(ALLOWED_METHOD, "DELETE");
	slash.addValue(AUTOINDEX, "on");
	LocationConfig	root;
	root.pathType_ = ROOT_PATH;
	root.directive_ = slash;
	location_.insert(std::make_pair("/", root));

	DirectiveMap	upload;
	upload.addValue(ALLOWED_METHOD, "PUT");
	upload.addValue(ALLOWED_METHOD, "DELETE");
	upload.addValue(ALLOWED_METHOD, "GET");
	upload.addValue(AUTOINDEX, "on");
	upload.addValue(UPLOAD_ROOT, "/storage");//? have to create folder?
	LocationConfig	uploader;
	uploader.pathType_ = UPLOAD_PATH;
	uploader.directive_ = upload;
	location_.insert(std::make_pair("/uploads", uploader));

	DirectiveMap	cgi;
	cgi.addValue(ALLOWED_METHOD, "GET");
	cgi.addValue(ALLOWED_METHOD, "POST");
	cgi.addValue(AUTOINDEX, "off");
	cgi.addValue(CGI_ROOT, "cgi-bin");
	LocationConfig cgier;
	cgier.pathType_ = CGI_PATH;
	cgier.directive_ = cgi;
	location_.insert(std::make_pair("/cgi-bin", cgier));

	DirectiveMap	re;
	re.addValue(ALLOWED_METHOD, "GET");
	re.addValue(ALLOWED_METHOD, "PUT");
	re.addValue(ALLOWED_METHOD, "POST");
	re.addValue(ALLOWED_METHOD, "DELETE");
	re.addValue(REDIRECT_TO, "301");
	re.addValue(REDIRECT_TO, "http://example.com");
	LocationConfig redir;
	redir.pathType_ = REDIRECTION_PATH;
	redir.directive_ = re;
	location_.insert(std::make_pair("redirect", redir));
}

Config::~Config()
{
	return ;
}

Config::Config(Config const &rhs)
:port_(rhs.port_)
,server_name_(rhs.server_name_)
,root_(rhs.root_)
,error_pages_(rhs.error_pages_)
,others_(rhs.others_)
,location_(rhs.location_)
{
	return ;
}

Config &Config::operator=(Config const &rhs)
{
	if (this != &rhs)
	{
		port_ = rhs.port_;
		server_name_ = rhs.server_name_;
		root_ = rhs.root_;
		error_pages_ = rhs.error_pages_;
		others_ = rhs.others_;
		location_ = rhs.location_;
	}
	return (*this);
}

//getter
std::size_t	Config::getPort(void) const
{
	return (port_);
}

std::string	Config::getServerName(void) const
{
	return (server_name_);
}

std::string	Config::getRoot(std::string const &path) const
{
	LocationConfig const &loc = getConfigLocation(path);

	if (loc.pathType_ == CGI_PATH)
		return (root_ + loc.directive_.getFirstValue(CGI_ROOT));
	else if (loc.pathType_ == UPLOAD_PATH)
		return (root_ + loc.directive_.getFirstValue(UPLOAD_ROOT));
	else
		return (root_);
}

Config::ErrorPageMap	Config::getErrorPageMap(void) const
{
	return (error_pages_);
}

std::string	Config::getErrorPage(HttpCode::StatusCode error_code) const
{
	std::map<HttpCode::StatusCode, std::string>::size_type	findCount;
	findCount = error_pages_.count(error_code);

	if (findCount == 0)
		return ("");

	std::string const	error_path = error_pages_.at(error_code);
	return (error_path);
}

Config::LocationConfig	Config::getConfigLocation(std::string const &path) const
{
	LocationConfigMap::const_iterator	it = location_.begin();
	LocationConfigMap::const_iterator	end = location_.end();
	std::string							bestMatch = "";

	while (it != end)
	{
		if (path.compare(0, it->first.length(), it->first) == 0)
		{
			if (it->first.length() > bestMatch.length())
				bestMatch = it->first;
		}
		it++;
	}

	if (bestMatch.empty())
	{
		return (location_.at("/"));
	}
	else
	{
		return (location_.at(bestMatch));
	}

	// LocationConfig	loc;
	// ft::string const	ftpath(path);

	// if (ftpath.end_with_str(".py"))
	// 	loc = location_.at("/py");
	// else if (location_.find(path) == location_.end())
	// 	loc = location_.at("/");
	// else
	// 	loc = location_.at(path);
	// return (loc);
}

config::Config::Config(Parser& parse)
{
	Config::setConfig(parse);
}

void	config::Config::setConfig(Parser& parse)
{
	if (parse.consume_token() != "server")
        throw std::runtime_error("invalid config");
    if (parse.consume_token() != "{")
        throw std::runtime_error("invalid config");
    while (parse.get_token() != "}" && parse.get_token() != "\0")
    {
		if (!isPort(parse) \
			&& !isServerName(parse) \
			&& !isRoot(parse) \
			&& !isMaxBodySize(parse) \
			&& !isErrorPage(parse) \
			&& !isLocation(parse))
			throw std::runtime_error("invalid config");
    }
    if (parse.consume_token() != "}")
        throw std::runtime_error("invalid config");
}

void	config::Config::setServerName(std::string name)
{
	server_name_ = name;
}

void	config::Config::setPort(size_t port)
{
	port_ = port;
}

void	config::Config::setRoot(std::string root)
{
	root_ = root;
}

void	config::Config::setMaxBodySize(std::string size)
{
	others_.addValue(MAX_BODY_SIZE, size);
	// max_body_size_ = size;
}

void	config::Config::setErrorPage(HttpCode::StatusCode code, std::string page)
{
	error_pages_.insert(std::make_pair(code, page));
}

bool	config::Config::isPort(Parser& parse)
{
    if (parse.get_token() != "listen")
        return false;
    parse.consume_token();
    std::stringstream ss;
	size_t port;
    ss << parse.consume_token();
    ss >> port;
	setPort(port);
    if (parse.consume_token() != ";")
        return false;
    return true;
}

bool	config::Config::isServerName(Parser& parse)
{
    if (parse.get_token() != "server_name")
        return false;
    parse.consume_token();
    setServerName(parse.consume_token());
    if (parse.consume_token() != ";")
        return false;
    return true;
}

bool	config::Config::isRoot(Parser& parse)
{
    if (parse.get_token() != "root")
        return false;
    parse.consume_token();
	// std::cout << parse.get_token() << std::endl;
	// if (!isnums(parse.get_token()))
	// 	return false;
    setRoot(parse.consume_token());
    if (parse.consume_token() != ";")
        return false;
    return true;
}

bool	config::Config::isMaxBodySize(Parser& parse)
{
    if (parse.get_token() != "max_body_size")
        return false;
    parse.consume_token();
	if (!isnums(parse.get_token()))
		return false;
	std::string size;
    size = parse.consume_token();
	setMaxBodySize(size);
    if (parse.consume_token() != ";")
        return false;
    return true;
}

bool	config::Config::isErrorPage(Parser& parse)
{
    if (parse.get_token() != "error_page")
        return false;
    parse.consume_token();
	if (!isnums(parse.get_token()))
		return false;
    std::stringstream ss;
    int code;
    ss << parse.consume_token();
    ss >> code;
    std::string error_page = parse.consume_token();
    setErrorPage(HttpCode::StatusCode(code), error_page);
    if (parse.consume_token() != ";")
        return false;
    return true;
}

void	config::Config::setLocation(Parser& parse, LocationConfig& location, std::string location_path)
{
    while (parse.get_token() != "}" && parse.get_token() != "\0")
    {
		if (!isIndex(parse, location) \
			&& !isMethod(parse, location) \
			&& !isAoutIndex(parse, location) \
			&& !isUploadRoot(parse, location) \
			&& !isCgiRoot(parse, location) \
			&& !isRedirect(parse, location))
			throw std::runtime_error("invalid config");
    }
	location_.insert(std::make_pair(location_path, location));
}

void	config::Config::setIndex(std::string index, LocationConfig& location)
{
	location.directive_.addValue(INDEX, index);
}

void	config::Config::setMethod(std::string method, LocationConfig& location)
{
	location.directive_.addValue(ALLOWED_METHOD, method);
}

void	config::Config::setAoutIndex(std::string aout_index, LocationConfig& location)
{
	location.directive_.addValue(AUTOINDEX, aout_index);
}

void	config::Config::setUploadRoot(std::string upload_root, LocationConfig& location)
{
	location.directive_.addValue(UPLOAD_ROOT, upload_root);
	location.pathType_ = UPLOAD_PATH;
}

void	config::Config::setCgiRoot(std::string cgi_root, LocationConfig& location)
{
	location.directive_.addValue(CGI_ROOT, cgi_root);
	location.pathType_ = CGI_PATH;
}

void	config::Config::setRedirect(std::string redirect, LocationConfig& location)
{
	location.directive_.addValue(REDIRECT_TO, redirect);
	location.pathType_ = REDIRECTION_PATH;
}

bool	config::Config::isLocation(Parser& parse)
{
	if (parse.consume_token() != "location")
        return false;
	LocationConfig	location;
	std::string	location_path = parse.consume_token();
	location.pathType_ = STATIC_PATH;
    if (parse.consume_token() != "{")
        return false;
	setLocation(parse, location, location_path);
    if (parse.consume_token() != "}")
        return false;
	return true;
}

bool	config::Config::isIndex(Parser& parse, LocationConfig& location)
{
    if (parse.get_token() != "index")
        return false;
    parse.consume_token();
    setIndex(parse.consume_token(), location);
    if (parse.consume_token() != ";")
        return false;
    return true;
}

bool	config::Config::isMethod(Parser& parse, LocationConfig& location)
{
    if (parse.get_token() != "allowed_methods")
        return false;
    parse.consume_token();
	while (parse.get_token() != ";" && parse.get_token() != "\0")
    	setMethod(parse.consume_token(), location);
    if (parse.consume_token() != ";")
        return false;
	return true;
}

bool	config::Config::isAoutIndex(Parser& parse, LocationConfig& location)
{
    if (parse.get_token() != "autoindex")
        return false;
    parse.consume_token();
    setAoutIndex(parse.consume_token(), location);
    if (parse.consume_token() != ";")
        return false;
	return true;
}

bool	config::Config::isUploadRoot(Parser& parse, LocationConfig& location)
{
    if (parse.get_token() != "upload_store")
        return false;
    parse.consume_token();
    setUploadRoot(parse.consume_token(), location);
    if (parse.consume_token() != ";")
        return false;
	return true;
}

bool	config::Config::isCgiRoot(Parser& parse, LocationConfig& location)
{
    if (parse.get_token() != "cgi_root")
        return false;
    parse.consume_token();
    setCgiRoot(parse.consume_token(), location);
    if (parse.consume_token() != ";")
        return false;
	return true;
}

bool	config::Config::isRedirect(Parser& parse, LocationConfig& location)
{
    if (parse.get_token() != "return")
        return false;
    parse.consume_token();
    setRedirect(parse.consume_token(), location);
    setRedirect(parse.consume_token(), location);
    if (parse.consume_token() != ";")
        return false;
	return true;
}

}// end of namespace config
