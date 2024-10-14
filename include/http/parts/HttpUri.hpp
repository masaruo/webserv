#pragma once
#include <string>
#include "define.hpp"
#include "VecMap.hpp"

class HttpUri
{
public:
	struct PathInfo
	{
		std::string	directory_;
		std::string	fileName_;
		std::string	cgiPathInfo_;
	};

	struct Query
	{
		ft::str_map	QueryMap_;
	};

private://! add parent_? which is just one / up of path?
	std::string	rawUri_;
	std::string	host_;
	std::size_t	port_;
	std::string	path_;
	bool		isCgi_;
	bool		hasQuery_;
	Query		query_;
	PathInfo	pathInfo_;

	void		parseAbsoluteFormUri(void);
	void		parseOriginFormUri(std::string const &host);
	void		parseUriAndExtractPath(std::string const &after_scheme);
	std::string	extractHost(std::string const &uri_after_scheme);
	std::string	extractQuery(std::string const &uri_after_host);
	std::string	extractPort(std::string const &path_wo_query);
	std::string	extractPathInfo(std::string const &path);
	std::string	extractCgiInfo(std::string const &path);
	void		parseQueryWithDecodePercent(std::string const &query);
	void		formatEachComponentsExQuery(void);
	void		assertFinalData(void) const;
public:
	HttpUri();
	~HttpUri();
	HttpUri(HttpUri const &rhs);
	HttpUri &operator=(HttpUri const &rhs);

	//setter
	void		init(std::string const &raw);
	void		updateWithHostHeader(std::string const &host);

	//getter
	std::string	getHost(void) const;
	std::size_t	getPort(void) const;
	std::string	getPortStr(void) const;
	std::string	getPath(void) const;
	Query		getQuery(void) const;
	ft::str_map	getQueryMap(void) const;
	std::string	getQueryValue(std::string const &key) const;
	std::string	getRawQueryString(void) const;
	PathInfo	getPathInfo(void) const;
	bool		IsCgi(void) const;
	bool		hasQuery(void) const;
};
