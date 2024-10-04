#include "HttpUri.hpp"
#include "HttpException.hpp"
#include "string.hpp"
#include "UriNormalizer.hpp"
#include <sstream>

HttpUri::HttpUri()
:initial_uri_()
,authority_()
,host_()
,port_(0)
,path_()
,ext_()
,path_info_()
,query_()
,hasQuery_(false)
,is_cgi_(false)
{
	return ;
}

HttpUri::~HttpUri()
{
	return ;
}

HttpUri::HttpUri(HttpUri const &rhs)
:initial_uri_(rhs.initial_uri_)
,authority_(rhs.authority_)
,host_(rhs.host_)
,port_(rhs.port_)
,path_(rhs.path_)
,ext_(rhs.ext_)
,path_info_(rhs.path_info_)
,query_(rhs.query_)
,hasQuery_(rhs.hasQuery_)
,is_cgi_(rhs.is_cgi_)
{
	return ;
}

HttpUri &HttpUri::operator=(HttpUri const &rhs)
{
	if (this != &rhs)
	{
		initial_uri_ = rhs.initial_uri_;
		authority_ = rhs.authority_;
		host_ = rhs.host_;
		port_ = rhs.port_;
		path_ = rhs.path_;
		ext_ = rhs.ext_;
		path_info_ = rhs.path_info_;
		query_ = rhs.query_;
		hasQuery_ = rhs.hasQuery_;
		is_cgi_ = rhs.is_cgi_;
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
		query_[key] = value;
		iter++;
	}
}

void	HttpUri::parsePort(void)
{
	std::string::size_type	portStart = authority_.find(':');
	if (portStart == std::string::npos)
	{
		host_ = authority_;
		port_ = 80;
	}
	else
	{
		host_ = authority_.substr(0, portStart);
		std::string	hostStr = authority_.substr(portStart + 1);
		try
		{
			port_ = ft::stonum<std::size_t>(hostStr);
		}
		catch(std::invalid_argument const &e)
		{
			throw (HttpException(HttpCode::BAD_REQUEST));
		}
	}
	if (host_.empty() || port_ == 0)
		throw (HttpException(HttpCode::BAD_REQUEST));
}

void	HttpUri::parseExtAndPathInfo(void)
{
	std::string				dotDecodedStr = UriNormalizer::decodeDots(path_);
	std::string::size_type	lastDotPos = dotDecodedStr.find_last_of('.');
	std::string::size_type	extEnd = dotDecodedStr.find_first_of("/", lastDotPos + 1);
	std::string				ext, pathInfo;

	if (lastDotPos == std::string::npos)
	{
		ext = "";
		pathInfo = "";
	}
	else if (extEnd == std::string::npos)
	{
		ext = dotDecodedStr.substr(lastDotPos + 1);
		pathInfo = "";
	}
	else
	{
		ext = dotDecodedStr.substr(lastDotPos + 1, extEnd - 1 - lastDotPos);
		pathInfo = dotDecodedStr.substr(extEnd + 1);
	}
	ext_ = ext;
	path_info_ = pathInfo;
}

void	HttpUri::parseAuthority(void)
{
	parsePort();
	parseExtAndPathInfo();
}

void	HttpUri::parseUri(std::string const &authorityStart)//? check host
{
	bool	has_no_delim = false;
	bool	has_question = false;
	bool	has_pathInfo = false;
	
	std::string::size_type	authorityEndPos = authorityStart.find_first_of("/?");

	if (authorityEndPos == std::string::npos)
	{
		authority_ = initial_uri_;
		path_ = "/";
		hasQuery_ = false;
	}
	else
	{
		authority_ = authorityStart.substr(0, authorityEndPos);
		std::string const	pathStart = authorityStart.substr(authorityEndPos + 1);
		if (authorityStart.at(authorityEndPos) == '?')
		{
			path_ = "/";
			std::string queryString = authorityStart.substr(authorityEndPos + 1);
			parseQueryWithDecodePercent(queryString);
			hasQuery_ = true;
		}
		else
		{
			std::string::size_type	queryStart = pathStart.find('?');
			if (queryStart == std::string::npos)
			{
				path_ = "/" + pathStart;
				hasQuery_ = false;
			}
			else
			{
				path_ = "/" + pathStart.substr(0, queryStart);
				std::string queryString = pathStart.substr(queryStart + 1);
				parseQueryWithDecodePercent(queryString);
				hasQuery_ = true;
			}
		}
	}
	if (authority_.empty() || path_.empty())
		throw (HttpException(HttpCode::BAD_REQUEST));
	parseAuthority();
}

void	HttpUri::parseAbsolute(void)
{
	std::string	scheme(initial_uri_, 0, 4);
	ft::string	ft_scheme(scheme);
	ft_scheme.to_lower();
	if (ft_scheme.str() != "http")
		throw (HttpException(HttpCode::BAD_REQUEST));
	
	std::string::size_type	authorityStart = initial_uri_.find("://") + 3;
	std::string	raw_after_scheme = initial_uri_.substr(authorityStart);
	parseUri(raw_after_scheme);
}

void	HttpUri::parseOrigin(std::string const &hostHeader)
{
	std::string	concatinated = hostHeader + initial_uri_;
	parseUri(concatinated);
}

void	HttpUri::updateWithHostHeader(std::string const &hostHeader)
{
	if (initial_uri_.empty() || hostHeader.empty())
		throw (HttpException(HttpCode::BAD_REQUEST));
	if (initial_uri_.at(0) == '/')
		parseOrigin(hostHeader);
	else
		parseAbsolute();
	formatEachComponentsExQuery();
	assertFinalData();
	checkIsCgi();
}

void	HttpUri::formatEachComponentsExQuery(void)
{
	// to lower
	ft::string	fthost(host_);
	fthost.to_lower();
	host_ = fthost.str();

	// % decode
	authority_ = UriNormalizer::decodePercent(authority_);
	host_ = UriNormalizer::decodePercent(host_);
	path_ = UriNormalizer::decodePercent(path_);
	ext_ = UriNormalizer::decodePercent(ext_);
	path_info_ = UriNormalizer::decodePercent(path_info_);

	// expand dots
	path_ = UriNormalizer::decodeDots(path_);
	path_info_ = UriNormalizer::decodeDots(path_info_);
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
	if (!str.has_only(ft::string::PCHAR))
		is_valid = false;
	if (!ext_.empty() && ext_ != "py")
		is_valid = false;
	str = path_info_;
	if (!str.has_only(ft::string::VCHAR))
		is_valid = false;
	
	if (is_valid)
		throw (HttpException(HttpCode::BAD_REQUEST));
}

void	HttpUri::checkIsCgi(void)
{
	if (ext_ == "py")//決め打ちでpyのみ
		is_cgi_ = true;
	else
		is_cgi_ = false;
}

std::string	HttpUri::getAuthority(void) const
{
	return (authority_);
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

std::string	HttpUri::getExt(void) const
{
	return (ext_);
}

std::string	HttpUri::getPathInfo(void) const
{
	return (path_info_);
}

ft::str_map	HttpUri::getQuery(void) const
{
	return (query_);
}

std::string	HttpUri::getQueryValue(std::string const &key) const
{
	std::string	value = query_.at(key);
	return (value);
}

std::string	HttpUri::getQueryString(void) const
{
	ft::str_map_const_iter	iter = query_.begin();
	ft::str_map_const_iter	end = query_.end();
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

bool	HttpUri::getIsCgi(void) const
{
	return (is_cgi_);
}
