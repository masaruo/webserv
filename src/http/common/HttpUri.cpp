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
:initial_uri_()
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
:initial_uri_(rhs.initial_uri_)
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
		initial_uri_ = rhs.initial_uri_;
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
	if (raw.size() > URI_MAX_LEN)
		throw (HttpException(HttpCode::URI_TOO_LONG));
	else if (raw.empty())
		throw (HttpException(HttpCode::BAD_REQUEST));
	initial_uri_ = UriNormalizer::uniformSlashAndHandleDots(raw);
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
		if (!ftkey.has_only(ft::string::VCHAR) || !ftvalue.has_only(ft::string::VCHAR))
			throw (HttpException(HttpCode::BAD_REQUEST));
		query_.QueryMap_[key] = value;
		iter++;
	}
}

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
	// host_ = host;
	std::string	hostWoPort = extractPort(host);
	host_ = hostWoPort;
	return (afterHost);
}

std::string	HttpUri::extractQuery(std::string const &after_host)
{
	std::string::size_type	queryStartPos = after_host.find("?");
	std::string	path = "";
	std::string	query = "";

	if (queryStartPos == std::string::npos)
	{
		path = after_host;
		query = "";
		query_.hasQuery_ = false;
	}
	else
	{
		path = after_host.substr(0, queryStartPos);
		query = after_host.substr(queryStartPos + 1);
		query_.hasQuery_ = true;
		parseQueryWithDecodePercent(query);
	}
	return (path);
}

std::string	HttpUri::extractPort(std::string const &host)
{
	std::string::size_type	portStartPos = host.find(':');
	std::string	hostWoPort = "";

	if (portStartPos == std::string::npos)
	{
		hostWoPort = host;
		port_ = 80;
	}
	else
	{
		hostWoPort = host.substr(0, portStartPos);
		std::string::size_type	portEndPos = host.find_first_of('/', portStartPos);
		std::string	portStr = host.substr(portStartPos + 1, portEndPos - portStartPos);
		try
		{
			port_ = ft::stonum<std::size_t>(portStr);
		}
		catch(std::invalid_argument const &e)
		{
			throw (HttpException(HttpCode::BAD_REQUEST));
		}
	}
	return (hostWoPort);
}

std::string	HttpUri::extractPathAndCgi(std::string const &path)
{
	std::string::size_type	scriptEndPos = path.find(".py");//! ONLY PYTHON
	if (scriptEndPos == std::string::npos)
	{
		cgi_.isCgi_ = false;
		return (path);
	}

	ft::string									ftpath(path);
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
	cgi.pathBeforeScript_ = ft::concatSplitVector(pathBeforeScriptVec, '/');
	cgi.scriptName_ = scriptName;
	cgi.ext_ = "py";
	cgi.pathInfo_ = ft::concatSplitVector(pathInfoVec, '/');

	cgi_ = cgi;
	return (cgi.pathBeforeScript_ + "/" + cgi.scriptName_);
}

void	HttpUri::parseUriAndExtractPath(std::string const &after_scheme)
{
	std::string const	pathStart = extractHost(after_scheme);
	std::string const	pathStartWoQuery = extractQuery(pathStart);
	std::string const	path = extractPathAndCgi(pathStartWoQuery);
	
	path_ = path;
}

void	HttpUri::parseAbsoluteFormUri(void)
{
	std::string	scheme(initial_uri_, 0, 4);
	ft::string	ft_scheme(scheme);
	ft_scheme.to_lower();
	if (ft_scheme.str() != "http")
		throw (HttpException(HttpCode::BAD_REQUEST));
	
	std::string::size_type	hostStartPos = initial_uri_.find("://") + 3;
	std::string	raw_after_scheme = initial_uri_.substr(hostStartPos);
	std::string	raw_after_scheme_dup_slash_removed = ft::removeConsecutiveDelim(raw_after_scheme, '/');
	parseUriAndExtractPath(raw_after_scheme_dup_slash_removed);
}

void	HttpUri::parseOriginFormUri(std::string const &hostHeader)
{
	std::string	concatinated = hostHeader + initial_uri_;
	std::string	concatinated_dup_slash_removed = ft::removeConsecutiveDelim(concatinated, '/');
	parseUriAndExtractPath(concatinated_dup_slash_removed);
}

void	HttpUri::updateWithHostHeader(std::string const &hostHeader)
{
	if (initial_uri_.empty() || hostHeader.empty())
		throw (HttpException(HttpCode::BAD_REQUEST));
	if (initial_uri_.at(0) == '/')
		parseOriginFormUri(hostHeader);
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
}

void	HttpUri::assertFinalData(void) const
{
	bool	is_valid = true;

	ft::string	str;
	str = host_;
	if (!str.has_only(ft::string::HOST))
		is_valid = false;
	if (port_ < 1 || 65535 < port_)
		is_valid = false;
	str = path_;
	if (!str.has_only(ft::string::PCHAR + "/"))
		is_valid = false;
	str = cgi_.pathBeforeScript_;
	if (!str.has_only(ft::string::PCHAR + "/"))
		is_valid = false;
	str = cgi_.scriptName_;
	if (!str.has_only(ft::string::PCHAR + "/"))
	str = cgi_.pathInfo_;
	if (!str.has_only(ft::string::VCHAR))
		is_valid = false;

	if (!is_valid)
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
	ft::str_map_const_iter	iter = query_.QueryMap_.begin();
	ft::str_map_const_iter	end = query_.QueryMap_.end();
	std::ostringstream	oss;

	while (iter != end)
	{
		oss << iter->first << "=" << iter->second;
		ft::str_map_const_iter	next = iter;
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
