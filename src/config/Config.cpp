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
	root_ = "www/html";
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
	upload.addValue(UPLOAD_ROOT, "www/storage");//? have to create folder?
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
		return (loc.directive_.getFirstValue(CGI_ROOT));
	else if (loc.pathType_ == UPLOAD_PATH)
		return (loc.directive_.getFirstValue(UPLOAD_ROOT));
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
}// end of namespace config
