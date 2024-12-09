#include <AHeader.hpp>
#include "string.hpp"

AHeader::AHeader()
:fields_()
,toEnum_(initStringToEnum())
,toString_(initEnumToString())
{
	return ;
}

AHeader::~AHeader()
{
	return ;
}

AHeader::AHeader(AHeader const &rhs)
:fields_(rhs.fields_)
,toEnum_(rhs.toEnum_)
,toString_(rhs.toString_)
{
	return ;
}

AHeader	&AHeader::operator=(AHeader const &rhs)
{
	if (this != &rhs)
	{
		fields_ = rhs.fields_;
		toEnum_ = rhs.toEnum_;
		toString_ = rhs.toString_;
	}
	return (*this);
}

AHeader::HeaderField AHeader::strToEnum(std::string const &key) const
{
	ft::string lowerKey(key);
	lowerKey.to_lower();
	map_strToEnum::const_iterator	iter = toEnum_.find(lowerKey.str());
	if (iter == toEnum_.end())
		return (FAIL);
	else
		return (iter->second);
}

std::string	AHeader::enumToStr(HeaderField key) const
{
	map_enumToStr::const_iterator	iter = toString_.find(key);
	if (iter == toString_.end())
		return ("");
	else
		return (iter->second);
}

void	AHeader::add(HeaderField field, std::string const &value)
{
	fields_.addValue(field, value);
}

void	AHeader::del(HeaderField field)
{
	fields_.removeKey(field);
}

bool	AHeader::hasKey(HeaderField field) const
{
	return (fields_.hasKey(field));
}

std::string	AHeader::getFirstValue(HeaderField field) const
{
	return (fields_.getFirstValue(field));
}

std::string	AHeader::getLastValue(HeaderField field) const
{
	return (fields_.getLastValue(field));
}

std::size_t	AHeader::size(void) const
{
	std::size_t	size = static_cast<std::size_t>(fields_.size());
	return (size);
}

std::string	AHeader::to_string(void) const
{
	vecmap::const_iterator	iter = fields_.cbegin();
	vecmap::const_iterator	end = fields_.cend();
	std::stringstream	ss;
	while (iter != end)
	{
		ss << enumToStr(iter->first) << ":";
		ft::str_vec					values = iter->second;
		ft::str_vec::const_iterator	it = values.begin();
		while (it != values.end())
		{
			ss << *it;
			if (it +1 != values.end())
				ss << ",";
			it++;
		}
		ss << ft::string::CRLF;
		iter++;
	}
	return (ss.str());
}

AHeader::map_strToEnum const	AHeader::initStringToEnum(void)
{
	map_strToEnum	m;
	
	// General Headers
	m["cache-control"] = CACHE_CONTROL;
	m["connection"] = CONNECTION;
	m["date"] = DATE;
	m["pragma"] = PRAGMA;
	m["trailer"] = TRAILER;
	m["transfer-encoding"] = TRANSFER_ENCODING;
	m["upgrade"] = UPGRADE;
	m["via"] = VIA;
	m["warning"] = WARNING;

	// Request Headers
	m["accept"] = ACCEPT;
	m["accept-charset"] = ACCEPT_CHARSET;
	m["accept-encoding"] = ACCEPT_ENCODING;
	m["accept-language"] = ACCEPT_LANGUAGE;
	m["authorization"] = AUTHORIZATION;
	m["expect"] = EXPECT;
	m["from"] = FROM;
	m["host"] = HOST;
	m["if-match"] = IF_MATCH;
	m["if-modified-since"] = IF_MODIFIED_SINCE;
	m["if-none-match"] = IF_NONE_MATCH;
	m["if-range"] = IF_RANGE;
	m["if-unmodified-since"] = IF_UNMODIFIED_SINCE;
	m["max-forwards"] = MAX_FORWARDS;
	m["proxy-authorization"] = PROXY_AUTHORIZATION;
	m["range"] = RANGE;
	m["referer"] = REFERER;
	m["te"] = TE;
	m["user-agent"] = USER_AGENT;

	// Response Headers
	m["accept-ranges"] = ACCEPT_RANGES;
	m["age"] = AGE;
	m["etag"] = ETAG;
	m["location"] = LOCATION;
	m["proxy-authenticate"] = PROXY_AUTHENTICATE;
	m["retry-after"] = RETRY_AFTER;
	m["server"] = SERVER;
	m["vary"] = VARY;
	m["www-authenticate"] = WWW_AUTHENTICATE;

	// Entity Headers
	m["allow"] = ALLOW;
	m["content-encoding"] = CONTENT_ENCODING;
	m["content-language"] = CONTENT_LANGUAGE;
	m["content-length"] = CONTENT_LENGTH;
	m["content-location"] = CONTENT_LOCATION;
	m["content-md5"] = CONTENT_MD5;
	m["content-range"] = CONTENT_RANGE;
	m["content-type"] = CONTENT_TYPE;
	m["expires"] = EXPIRES;
	m["last-modified"] = LAST_MODIFIED;

	// CGI Meta-Headers
	m["status"] = STATUS;
	m["fail"] = FAIL;
	
	return (m);
}

AHeader::map_enumToStr const AHeader::initEnumToString(void)
{
   map_enumToStr m;
   m[ACCEPT] = "accept";
   m[ACCEPT_CHARSET] = "accept-charset";
   m[ACCEPT_ENCODING] = "accept-encoding";
   m[ACCEPT_LANGUAGE] = "accept-language";
   m[ACCEPT_RANGES] = "accept-ranges";
   m[AGE] = "age";
   m[ALLOW] = "allow";
   m[AUTHORIZATION] = "authorization";
   m[CACHE_CONTROL] = "cache-control";
   m[CONNECTION] = "connection";
   m[CONTENT_ENCODING] = "content-encoding";
   m[CONTENT_LANGUAGE] = "content-language";
   m[CONTENT_LENGTH] = "content-length";
   m[CONTENT_LOCATION] = "content-location";
   m[CONTENT_MD5] = "content-md5";
   m[CONTENT_RANGE] = "content-range";
   m[CONTENT_TYPE] = "content-type";
   m[DATE] = "date";
   m[ETAG] = "etag";
   m[EXPECT] = "expect";
   m[EXPIRES] = "expires";
   m[FROM] = "from";
   m[HOST] = "host";
   m[IF_MATCH] = "if-match";
   m[IF_MODIFIED_SINCE] = "if-modified-since";
   m[IF_NONE_MATCH] = "if-none-match";
   m[IF_RANGE] = "if-range";
   m[IF_UNMODIFIED_SINCE] = "if-unmodified-since";
   m[LAST_MODIFIED] = "last-modified";
   m[LOCATION] = "location";
   m[MAX_FORWARDS] = "max-forwards";
   m[PRAGMA] = "pragma";
   m[PROXY_AUTHENTICATE] = "proxy-authenticate";
   m[PROXY_AUTHORIZATION] = "proxy-authorization";
   m[RANGE] = "range";
   m[REFERER] = "referer";
   m[RETRY_AFTER] = "retry-after";
   m[SERVER] = "server";
   m[TE] = "te";
   m[TRAILER] = "trailer";
   m[TRANSFER_ENCODING] = "transfer-encoding";
   m[UPGRADE] = "upgrade";
   m[USER_AGENT] = "user-agent";
   m[VARY] = "vary";
   m[VIA] = "via";
   m[WARNING] = "warning";
   m[WWW_AUTHENTICATE] = "www-authenticate";
   m[STATUS] = "status";
   m[FAIL] = "fail";
   return m;
}
