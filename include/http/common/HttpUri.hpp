#pragma once
#include <string>
#include <define.hpp>

class HttpUri
{
private:
	static std::size_t const	URI_MAX_LEN = 1024;
	std::string	raw_;
	std::string	authority_;
	std::string	host_;
	std::size_t	port_;
	std::string	path_;
	std::string	ext_;
	std::string	path_info_;
	ft::str_map	query_;
	bool		hasQuery_;
	void		parseUri(std::string const &authorityStart, std::string const &host);
	void		parseAbsolute(std::string const &host);
	void		parseOrigin(std::string const &host);
	void		parseAuthority(void);
	void		parsePort(void);
	void		parseExtAndPathInfo(void);
	void		parseQuery(std::string const &query);
	std::string	percentDecoder(std::string const &str);
public:
	HttpUri();
	~HttpUri();
	HttpUri(HttpUri const &rhs);
	HttpUri &operator=(HttpUri const &rhs);
	void		init(std::string const &raw);
	void		constructWithHostheader(std::string const &host);
	std::string	getAuthority(void) const;
	std::string	getHost(void) const;
	std::size_t	getPort(void) const;
	std::string	getPortStr(void) const;
	std::string	getPath(void) const;
	std::string	getExt(void) const;
	std::string	getPathInfo(void) const;
	ft::str_map	getQuery(void) const;
	std::string	getQueryValue(std::string const &key) const;
	std::string	getQueryString(void) const;
};
