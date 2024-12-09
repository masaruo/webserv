#pragma once
#include <set>
#include "VecMap.hpp"
#include "HttpStatus.hpp"

class AHeader
{
public:

enum HeaderField
{
	// General Headers
	CACHE_CONTROL,
	CONNECTION,
	DATE,
	PRAGMA,
	TRAILER,
	TRANSFER_ENCODING,
	UPGRADE,
	VIA,
	WARNING,

	// Request Headers
	ACCEPT,
	ACCEPT_CHARSET, 
	ACCEPT_ENCODING,
	ACCEPT_LANGUAGE,
	AUTHORIZATION,
	EXPECT,
	FROM,
	HOST,
	IF_MATCH,
	IF_MODIFIED_SINCE,
	IF_NONE_MATCH,
	IF_RANGE,
	IF_UNMODIFIED_SINCE,
	MAX_FORWARDS,
	PROXY_AUTHORIZATION,
	RANGE,
	REFERER,
	TE,
	USER_AGENT,

	// Response Headers
	ACCEPT_RANGES,
	AGE,
	ETAG,
	LOCATION,
	PROXY_AUTHENTICATE,
	RETRY_AFTER,
	SERVER,
	VARY,
	WWW_AUTHENTICATE,

	// Entity Headers
	ALLOW,
	CONTENT_ENCODING,
	CONTENT_LANGUAGE,
	CONTENT_LENGTH,
	CONTENT_LOCATION,
	CONTENT_MD5,
	CONTENT_RANGE,
	CONTENT_TYPE,
	EXPIRES,
	LAST_MODIFIED,

	// CGI Meta-Headers
	STATUS,
	FAIL
};

typedef vm::VecMap<HeaderField, std::string>	vecmap;
typedef std::map<std::string, HeaderField>		map_strToEnum;
typedef std::map<HeaderField, std::string>		map_enumToStr;
typedef std::set<HeaderField>					headerSet;

protected:
	vecmap					fields_;
	map_strToEnum			toEnum_;
	map_enumToStr			toString_;
	// headerSet				noDupHeaders_;
	HeaderField				strToEnum(std::string const &key) const;
	std::string				enumToStr(HeaderField key) const;
	map_strToEnum const		initStringToEnum(void);
	map_enumToStr const		initEnumToString(void);
	void					assertParsedLine(void) const;
public:
	AHeader();
	virtual		~AHeader() = 0;
	AHeader(AHeader const &rhs);
	AHeader &operator=(AHeader const &rhs);
	void			add(HeaderField field, std::string const &value);
	void			del(HeaderField field);
	bool			hasKey(HeaderField field) const;
	std::string		getFirstValue(HeaderField field) const;
	std::string		getLastValue(HeaderField field) const;
	std::size_t		size(void) const;
	std::string		to_string(void) const;
};
