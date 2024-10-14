#include "HttpUri.hpp"
#include "HttpException.hpp"
#include "string.hpp"
#include "UriNormalizer.hpp"
#include "HttpRedirection.hpp"
#include <sstream>

HttpUri::Cgi_s::Cgi_s()
:isCgi_(false)
,hasPathInfo_(false)
,pathBeforeScript_()
,scriptName_()
,ext_()
,pathInfo_()
{
	return ;
}

HttpUri::Query_s::Query_s()
:hasQuery_(false)
,QueryMap_()
{
	return ;
}

HttpUri::HttpUri()
:rawUri_()
,host_()
,port_(80)
,path_()
,query_()
,cgi_()
{
	return ;
}

HttpUri::~HttpUri()
{
	return ;
}

HttpUri::HttpUri(HttpUri const &rhs)
:rawUri_(rhs.rawUri_)
,host_(rhs.host_)
,port_(rhs.port_)
,path_(rhs.path_)
,query_(rhs.query_)
,cgi_(rhs.cgi_)
{
	return ;
}

HttpUri &HttpUri::operator=(HttpUri const &rhs)
{
	if (this != &rhs)
	{
		rawUri_ = rhs.rawUri_;
		host_ = rhs.host_;
		port_ = rhs.port_;
		path_ = rhs.path_;
		query_ = rhs.query_;
		cgi_ = rhs.cgi_;
	}
	return (*this);
}

void	HttpUri::init(std::string const &raw)
{
	if (raw.size() > ft::URI_MAX_LEN)
		throw (HttpException(HttpCode::URI_TOO_LONG));
	else if (raw.empty())
		throw (HttpException(HttpCode::BAD_REQUEST));

	std::string slashUniformStr = UriNormalizer::uniformSlash(raw);// windows type \ -> /
	std::string dotsDecodedStr = UriNormalizer::decodeDots(slashUniformStr);// ../などを対応
	rawUri_ = dotsDecodedStr;
}

void	HttpUri::parseQueryWithDecodePercent(std::string const &query)
{
	ft::string					ft_query(query);
	ft::string::string_vector	split_by_and = ft_query.split("&");
	if (split_by_and.empty())
		throw (HttpException(HttpCode::BAD_REQUEST));
	ft::string::string_vector_const_iterator	iter = split_by_and.begin();
	ft::string::string_vector_const_iterator	end = split_by_and.end();

	while (iter != end)
	{
		ft::string::string_vector	split_by_equal = iter->split("=");
		if (split_by_equal.empty() || split_by_equal.size() != 2)
			throw (HttpException(HttpCode::BAD_REQUEST));
		std::string	key(UriNormalizer::decodePercent(split_by_equal.at(0)));
		std::string	value(UriNormalizer::decodePercent(split_by_equal.at(1)));
		ft::string ftkey(key);
		ft::string ftvalue(value);
		if (ftkey.has(ft::string::CTL_EX_NUL_HTAB_CR_LF) || ftvalue.has(ft::string::CTL_EX_NUL_HTAB_CR_LF))
			throw (HttpException(HttpCode::BAD_REQUEST));
		query_.QueryMap_[key] = value;
		iter++;
	}
}

// 4
std::string	HttpUri::extractHost(std::string const &after_scheme)
{
	std::string::size_type	hostEndPos = after_scheme.find_first_of("/?");
	std::string	host = "";
	std::string	afterHost = "";

	if (hostEndPos == std::string::npos)
	{
		host = after_scheme;
		afterHost = "/";
	}
	else
	{
		host = after_scheme.substr(0, hostEndPos);
		afterHost = after_scheme.substr(hostEndPos);
	}
	host_ = extractPort(host);
	return (afterHost);
}

// 6
std::string	HttpUri::extractQuery(std::string const &after_host)
{
	std::string::size_type	queryStartPos = after_host.find("?");
	std::string	pathWoutQuery = "";
	std::string	query = "";

	if (queryStartPos == std::string::npos)
	{
		pathWoutQuery = after_host;
		query = "";
		query_.hasQuery_ = false;
	}
	else
	{
		pathWoutQuery = after_host.substr(0, queryStartPos);
		query = after_host.substr(queryStartPos + 1);
		query_.hasQuery_ = true;
		parseQueryWithDecodePercent(query);
	}
	return (pathWoutQuery);
}

// 5
std::string	HttpUri::extractPort(std::string const &host)
{
	std::string::size_type	portStartPos = host.find(':');
	std::string				hostWoutPort = "";

	if (portStartPos == std::string::npos)
	{
		hostWoutPort = host;
		port_ = 80;
	}
	else
	{
		hostWoutPort = host.substr(0, portStartPos);
		std::string	portStr = host.substr(portStartPos + 1);
		try
		{
			port_ = ft::stonum<std::size_t>(portStr);
		}
		catch(std::invalid_argument const &e)
		{
			throw (HttpException(HttpCode::BAD_REQUEST));
		}
	}
	return (hostWoutPort);
}

std::string	HttpUri::extractPathAndCgi(std::string const &pathWoutQuery)
{
	std::string::size_type	scriptEndPos = pathWoutQuery.find(".py");//! ONLY PYTHON
	if (scriptEndPos == std::string::npos)
	{
		cgi_.isCgi_ = false;
		return (pathWoutQuery);
	}

	ft::string									ftpath(pathWoutQuery);
	ft::string::string_vector					split_by_slash = ftpath.split("/");
	ft::string::string_vector::const_iterator	iter = split_by_slash.begin();
	ft::string::string_vector::const_iterator	end = split_by_slash.end();
	ft::string::string_vector					pathBeforeScriptVec;
	std::string									scriptName;
	ft::string::string_vector					pathInfoVec;
	bool										isPathInfo = false;

	while (iter != end)
	{
		std::string::size_type	hasScript = iter->str().find(".py");
		if (hasScript == std::string::npos)
		{
			if (isPathInfo)
			{
				pathInfoVec.push_back(*iter);
			}
			else
			{
				pathBeforeScriptVec.push_back(*iter);
			}
			iter++;
		}
		else
		{
			scriptName = *iter;
			isPathInfo = true;
			iter++;
		}
	}

	Cgi_s	cgi;
	cgi.isCgi_ = true;
	cgi.hasPathInfo_ = isPathInfo;
	cgi.pathBeforeScript_ = ft::reverse_split(pathBeforeScriptVec, '/');
	cgi.scriptName_ = scriptName;
	cgi.ext_ = "py";
	cgi.pathInfo_ = ft::reverse_split(pathInfoVec, '/');

	cgi_ = cgi;
	return (cgi.pathBeforeScript_ + "/" + cgi.scriptName_);
}

// 3
void	HttpUri::parseUriAndExtractPath(std::string const &after_scheme)
{
	std::string const	afterHost = extractHost(after_scheme);
	std::string const	pathStartWoQuery = extractQuery(afterHost);
	std::string const	path = extractPathAndCgi(pathStartWoQuery);
	
	path_ = path;
}

// 2b
void	HttpUri::parseAbsoluteFormUri(void)
{
	std::string	scheme(rawUri_, 0, 4);
	ft::string	ft_scheme(scheme);
	ft_scheme.to_lower();
	if (ft_scheme.str() != "http")
		throw (HttpException(HttpCode::BAD_REQUEST));

	std::string::size_type	hostStartPos = rawUri_.find("://");
	if (hostStartPos == std::string::npos || rawUri_.size() < 8)// 8 = http://
		throw (HttpException(HttpCode::BAD_REQUEST));

	hostStartPos += 3;// :// = 3
	std::string	raw_after_scheme = rawUri_.substr(hostStartPos);
	std::string	raw_after_scheme_dup_slash_removed = ft::removeConsecutiveDelim(raw_after_scheme, '/');
	parseUriAndExtractPath(raw_after_scheme_dup_slash_removed);
}

// 2a
void	HttpUri::parseOriginFormUri(std::string const &hostHeader)
{
	std::string	concatinated = hostHeader + rawUri_;
	std::string	concatinated_dup_slash_removed = ft::removeConsecutiveDelim(concatinated, '/');
	parseUriAndExtractPath(concatinated_dup_slash_removed);
}

// 1. 
void	HttpUri::updateWithHostHeader(std::string const &hostValue)
{
	if (rawUri_.empty() || hostValue.empty())
		throw (HttpException(HttpCode::BAD_REQUEST));
	if (rawUri_.at(0) == '/')
		parseOriginFormUri(hostValue);
	else
		parseAbsoluteFormUri();
	formatEachComponentsExQuery();
	assertFinalData();
}

void	HttpUri::formatEachComponentsExQuery(void)
{
	// to lower
	ft::string	fthost(host_);
	fthost.to_lower();
	host_ = fthost.str();

	// % decode
	// authority_ = UriNormalizer::decodePercent(authority_);
	host_ = UriNormalizer::decodePercent(host_);
	path_ = UriNormalizer::decodePercent(path_);
	cgi_.pathBeforeScript_ = UriNormalizer::decodePercent(cgi_.pathBeforeScript_);
	cgi_.scriptName_ = UriNormalizer::decodePercent(cgi_.scriptName_);
	cgi_.pathInfo_ = UriNormalizer::decodePercent(cgi_.pathInfo_);

	// expand dots
	host_ = UriNormalizer::decodeDots(host_);
	path_ = UriNormalizer::decodeDots(path_);
	cgi_.pathBeforeScript_ = UriNormalizer::decodeDots(cgi_.pathBeforeScript_);
	cgi_.scriptName_ = UriNormalizer::decodeDots(cgi_.scriptName_);
	cgi_.pathInfo_ = UriNormalizer::decodeDots(cgi_.pathInfo_);
}

void	HttpUri::assertFinalData(void) const
{
	ft::string	const	&host(host_);
	ft::string const	&path(path_);
	ft::string			cgi(cgi_.pathBeforeScript_);

	if (host.empty() || !host.has_only(ft::string::URI_UNRESERVED + ft::string::SUBDELIMS))
		throw (HttpException(HttpCode::BAD_REQUEST));
		
	if (port_ < 1 || 65535 < port_)
		throw (HttpException(HttpCode::BAD_REQUEST));

	if (path.empty() || !path.has_only(ft::string::PCHAR + "/"))
		throw (HttpException(HttpCode::BAD_REQUEST));

	if (cgi.empty())
		return ;

	if (!cgi.has_only(ft::string::PCHAR + "/"))
		throw (HttpException(HttpCode::BAD_REQUEST));
		
	cgi = cgi_.scriptName_;
	if (!cgi.has_only(ft::string::PCHAR + "/"))
		throw (HttpException(HttpCode::BAD_REQUEST));

	cgi = cgi_.pathInfo_;
	if (cgi.empty() || !cgi.has_only(ft::string::PCHAR + "/"))
		throw (HttpException(HttpCode::BAD_REQUEST));
}

std::string	HttpUri::getHost(void) const
{
	return (host_);
}

std::size_t	HttpUri::getPort(void) const
{
	return (port_);
}

std::string	HttpUri::getPortStr(void) const
{
	return (ft::to_string<std::size_t>(port_));
}

std::string	HttpUri::getPath(void) const
{
	return (path_);
}

HttpUri::Query_s	HttpUri::getQuery(void) const
{
	return (query_);
}

ft::str_map	HttpUri::getQueryMap(void) const
{
	return (query_.QueryMap_);
}

std::string	HttpUri::getQueryValue(std::string const &key) const
{
	std::string const	val = query_.QueryMap_.at(key);
	return (val);
}

std::string	HttpUri::getRawQueryString(void) const
{
	ft::str_map::const_iterator iter = query_.QueryMap_.begin();
	ft::str_map::const_iterator	end = query_.QueryMap_.end();
	std::ostringstream	oss;

	while (iter != end)
	{
		oss << iter->first << "=" << iter->second;
		ft::str_map::const_iterator	next = iter;
		std::advance(next, 1);
		if (next != end)
		{
			oss << "&";
		}
		iter++;
	}
	return(oss.str());
}

HttpUri::Cgi_s	HttpUri::getCgi(void) const
{
	return (cgi_);
}

bool	HttpUri::IsCgi(void) const
{
	return (cgi_.isCgi_);
}
