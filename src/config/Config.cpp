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
	error_pages_.insert(std::make_pair(HttpCode::INTERNAL_SERVER_ERROR, "/50x.html"));
	error_pages_.insert(std::make_pair(HttpCode::BAD_GATEWAY, "/50x.html"));
	error_pages_.insert(std::make_pair(HttpCode::SERVICE_UNAVAILABLE, "/50x.html"));
	error_pages_.insert(std::make_pair(HttpCode::GATEWAY_TIMEOUT, "/50x.html"));

	// locations
	DirectiveMap	slash;
	slash.addValue(INDEX, "index.html");
	slash.addValue(ALLOWED_METHOD, "GET");
	slash.addValue(ALLOWED_METHOD, "POST");
	slash.addValue(ALLOWED_METHOD, "DELETE");
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
	upload.addValue(UPLOAD_ROOT, "/webserv/www/uploads");
	LocationConfig	uploader;
	uploader.pathType_ = CGI_PATH;
	uploader.directive_ = upload;
	location_.insert(std::make_pair("/upload", uploader));

	DirectiveMap	cgi;
	cgi.addValue(ALLOWED_METHOD, "GET");
	cgi.addValue(ALLOWED_METHOD, "POST");
	cgi.addValue(AUTOINDEX, "off");
	cgi.addValue(CGI_ROOT, "/webserv/cgi-bin");
	LocationConfig cgier;
	cgier.pathType_ = CGI_PATH;
	cgier.directive_ = cgi;
	location_.insert(std::make_pair("/py", cgier));

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
	location_.insert(std::make_pair("/redirect", redir));
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
	LocationConfig	loc;
	ft::string const	ftpath(path);

	if (ftpath.end_with_str(".py"))
		loc = location_.at("/py");
	else if (location_.find(path) == location_.end())
		loc = location_.at("/");
	else
		loc = location_.at(path);
	return (loc);
}
}// end of namespace config

// std::string	Config::getIndex(std::string const &path) const
// {
// 	return (getLocation(path).index_);
// }

// bool	Config::isAllowedMethod(std::string const &path, std::string const &method) const
// {
// 	location_s	loc = getLocation(path);
// 	if (loc.allowed_methods_.find(method) == loc.allowed_methods_.end())
// 		return (false);
// 	else
// 		return (true);
// }

// bool	Config::isAutoIndex(std::string const &path) const
// {
// 	return (getLocation(path).is_autoindex_);
// }

// bool	Config::isCgi(std::string const &path) const
// {
// 	return (getLocation(path).is_cgi_);
// }

// std::string	Config::getCgiRoot(std::string const &path) const
// {
// 	return (getLocation(path).cgi_root_);
// }

// std::string	Config::getUploadStore(std::string const &path) const
// {
// 	return (getLocation(path).upload_store_);
// }
