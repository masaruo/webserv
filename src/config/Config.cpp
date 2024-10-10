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
	directive_map_t	slash;
	slash.addValue(INDEX, "index.html");
	slash.addValue(ALLOWED_METHOD, "GET");
	slash.addValue(ALLOWED_METHOD, "POST");
	slash.addValue(ALLOWED_METHOD, "DELETE");
	slash.addValue(AUTOINDEX, "on");
	Location_s	root;
	root.type_ = ROOT;
	root.directive_ = slash;
	location_.insert(std::make_pair("/", root));

	directive_map_t	upload;
	upload.addValue(ALLOWED_METHOD, "PUT");
	upload.addValue(ALLOWED_METHOD, "DELETE");
	upload.addValue(ALLOWED_METHOD, "GET");
	upload.addValue(AUTOINDEX, "on");
	upload.addValue(UPLOAD_ROOT, "/webserv/www/uploads");
	Location_s	uploader;
	uploader.type_ = CGI;
	uploader.directive_ = upload;
	location_.insert(std::make_pair("/upload", uploader));

	directive_map_t	cgi;
	cgi.addValue(ALLOWED_METHOD, "GET");
	cgi.addValue(ALLOWED_METHOD, "POST");
	cgi.addValue(AUTOINDEX, "off");
	cgi.addValue(CGI_ROOT, "/webserv/cgi-bin");
	Location_s cgier;
	cgier.type_ = CGI;
	cgier.directive_ = cgi;
	location_.insert(std::make_pair("/py", cgier));

	directive_map_t	re;
	re.addValue(ALLOWED_METHOD, "GET");
	re.addValue(ALLOWED_METHOD, "PUT");
	re.addValue(ALLOWED_METHOD, "POST");
	re.addValue(ALLOWED_METHOD, "DELETE");
	re.addValue(REDIRECT_TO, "301");
	re.addValue(REDIRECT_TO, "http://example.com");
	Location_s redir;
	redir.type_ = REDIRECT;
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

Config &cConfig::operator=(Config const &rhs)
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
	Location_s const &loc = getLocation(path);

	if (loc.type_ == CGI)
		return (loc.directive_.getFirstValue(CGI_ROOT));
	else if (loc.type_ == UPLOAD)
		return (loc.directive_.getFirstValue(UPLOAD_ROOT));
	else
		return (root_);
}

std::string	Config::getErrorPage(HttpCode::code_e error_code) const
{
	std::map<HttpCode::code_e, std::string>::size_type	findCount;
	findCount = error_pages_.count(error_code);

	if (findCount == 0)
		return ("");

	std::string const	error_path = error_pages_.at(error_code);
	return (error_path);
}

Config::Location_s	Config::getLocation(std::string const &path) const
{
	Location_s	loc;
	ft::string const	ftpath(path);

	if (ftpath.end_with_str(".py"))
		loc = location_.at("/py");
	else if (location_.find(path) == location_.end())
		loc = location_.at("/");
	else
		loc = location_.at(path);
	return (loc);
}

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
}// end of namespace config
