#pragma once
#include <string>
#include <define.hpp>

class HttpUri
{
public:
	struct Cgi_s
	{
		bool		isCgi_;
		bool		hasPathInfo_;
		std::string	pathBeforeScript_;
		std::string	scriptName_;
		std::string	ext_;
		std::string	pathInfo_;
		Cgi_s();
	};

	struct Query_s
	{
		bool		hasQuery_;
		ft::str_map	QueryMap_;
		Query_s();
	};
	
private:
	static std::size_t const	URI_MAX_LEN = 8000;
	std::string	initial_uri_;
	std::string	host_;
	std::size_t	port_;
	std::string	path_;
	Query_s		query_;
	Cgi_s		cgi_;

	void		parseAbsoluteFormUri(void);
	void		parseOriginFormUri(std::string const &host);
	void		parseUriAndExtractPath(std::string const &after_scheme);
	std::string	extractHost(std::string const &uri_after_scheme);
	std::string	extractQuery(std::string const &uri_after_host);
	std::string	extractPort(std::string const &path_wo_query);
	std::string	extractPathAndCgi(std::string const &path);
	void		parseAuthority(void);
	void		parseExtAndPathInfo(void);
	void		parseQueryWithDecodePercent(std::string const &query);
	void		formatEachComponentsExQuery(void);
	void		assertFinalData(void) const;
public:
	HttpUri();
	~HttpUri();
	HttpUri(HttpUri const &rhs);
	HttpUri &operator=(HttpUri const &rhs);
	void		init(std::string const &raw);
	void		updateWithHostHeader(std::string const &host);
	std::string	getHost(void) const;
	std::size_t	getPort(void) const;
	std::string	getPortStr(void) const;
	std::string	getPath(void) const;
	Query_s		getQuery(void) const;
	ft::str_map	getQueryMap(void) const;
	std::string	getQueryValue(std::string const &key) const;
	std::string	getRawQueryString(void) const;
	Cgi_s		getCgi(void) const;
	bool		IsCgi(void) const;
};
