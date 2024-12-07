#pragma once
#include <set>
#include "VecMap.hpp"
#include "HttpStatus.hpp"

class HttpHeader : public vm::VecMap<std::string, std::string>
{
public:
	// よく使用されるHTTPヘッダーキーの静的定数
	static const std::string HOST;
	static const std::string CONTENT_TYPE;
	static const std::string CONTENT_LENGTH;
	static const std::string CONTENT_ENCODING;
	static const std::string TRANSFER_ENCODING;
	static const std::string CONNECTION;
	static const std::string USER_AGENT;
	static const std::string ACCEPT;
	static const std::string ACCEPT_ENCODING;
	static const std::string ACCEPT_LANGUAGE;
	static const std::string REFERER;
	static const std::string AUTHORIZATION;
	static const std::string COOKIE;
	static const std::string SERVER;
	static const std::string LOCATION;
	static const std::string DATE;
	static const std::string LAST_MODIFIED;
	static const std::string ETAG;
	static const std::string CACHE_CONTROL;
	static const std::string PRAGMA;
	static const std::string EXPIRES;
	// CGI関連のヘッダー
	static const std::string CONTENT_DISPOSITION;

private:
	static std::set<std::string>	noDupHeaderSet_;
	void	addValue(std::string const &line);
	void	setupNoDupHeaderSet(void);
	void	assertDupHeaderName(std::string const &name) const;
	void	assertSemanticValue(void) const;
public:
	HttpHeader();
	// explicit HttpHeader(std::istringstream &iss);
	explicit	HttpHeader(std::string const &str);
	~HttpHeader();
	HttpHeader(HttpHeader const &rhs);
	HttpHeader &operator=(HttpHeader const &rhs);
	void		addValue(std::string const &key, std::string const &value);
	void		delField(std::string const &key);
	std::size_t	getContentLen(void) const;
	std::string	to_string(void) const;
};
