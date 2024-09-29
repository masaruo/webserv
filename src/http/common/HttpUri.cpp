#include "HttpUri.hpp"
#include "HttpStatus.hpp"
#include "string.hpp"
#include <sstream>

HttpUri::HttpUri()
:raw_(), authority_(),host_(), port_(0), path_(), ext_(), query_(),  hasQuery_(false)
{
	return ;
}

HttpUri::~HttpUri()
{
	return ;
}

HttpUri::HttpUri(HttpUri const &rhs)
:raw_(rhs.raw_)
,authority_(rhs.authority_)
,host_(rhs.host_)
,port_(rhs.port_)
,path_(rhs.path_)
,ext_(rhs.ext_)
,query_(rhs.query_)
,hasQuery_(rhs.hasQuery_)
{
	return ;
}

HttpUri &HttpUri::operator=(HttpUri const &rhs)
{
	if (this != &rhs)
	{
		raw_ = rhs.raw_;
		authority_ = rhs.authority_;
		host_ = rhs.host_;
		port_ = rhs.port_;
		path_ = rhs.path_;
		ext_ = rhs.ext_;
		query_ = rhs.query_;
		hasQuery_ = rhs.hasQuery_;
	}
	return (*this);
}

void	HttpUri::init(std::string const &raw)
{
	if (raw.size() > URI_MAX_LEN)
		throw (HttpStatus::HttpStatusException(HttpCode::URI_TOO_LONG));
	else if (raw.empty())
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	raw_ = raw;
}

void	HttpUri::parseQuery(std::string const &query)
{
	ft::string					ft_query(query);
	ft::string::string_vector	split_by_and = ft_query.split("&");
	if (split_by_and.empty())
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	ft::string::string_vector_const_iterator	iter = split_by_and.begin();
	ft::string::string_vector_const_iterator	end = split_by_and.end();

	while (iter != end)
	{
		ft::string::string_vector	split_by_equal = iter->split("=");
		if (split_by_equal.empty() || split_by_equal.size() != 2)
			throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
		std::string	key(percentDecoder(split_by_equal.at(0)));
		std::string	value(percentDecoder(split_by_equal.at(1)));
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
			throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
		}
	}
	if (host_.empty() || port_ == 0)
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
}

void	HttpUri::parseExt(void)
{
	std::string::size_type	lastDotPos = authority_.find_last_of('.');
	std::string 			ans;
	ans = authority_.substr(lastDotPos + 1);
	if (ans.empty())
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	ext_ = percentDecoder(ans);
}

void	HttpUri::parseAuthority(void)
{
	parsePort();
	parseExt();
}

void	HttpUri::parseAbsolute(std::string const &host)//? check host
{
	std::string	scheme(raw_, 0, 4);
	ft::string	ft_scheme(scheme);
	ft_scheme.to_lower();
	if (ft_scheme.str() != "http")
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	
	std::string::size_type	authorityStart = raw_.find("://") + 3;
	std::string	raw_after_scheme = raw_.substr(authorityStart);
	parseUri(raw_after_scheme, host);
}

void	HttpUri::parseUri(std::string const &authorityStart, std::string const &host)//? check host
{
	std::string::size_type	authorityEnd = authorityStart.find_first_of("/?");

	if (authorityEnd == std::string::npos)
	{
		authority_ = raw_;
		path_ = "/";
		hasQuery_ = false;
	}
	else
	{
		authority_ = authorityStart.substr(0, authorityEnd);
		if (authorityStart.at(authorityEnd) == '?')
		{
			path_ = "/";
			std::string queryString = authorityStart.substr(authorityEnd + 1);
			parseQuery(queryString);
			hasQuery_ = true;
		}
		else
		{
			std::string::size_type	queryStart = authorityStart.find('?', authorityEnd);
			if (queryStart == std::string::npos)
			{
				path_ = percentDecoder(authorityStart.substr(authorityEnd));
				hasQuery_ = false;
			}
			else
			{
				path_ = percentDecoder(authorityStart.substr(0, queryStart));
				std::string queryString = authorityStart.substr(queryStart + 1);
				parseQuery(queryString);
				hasQuery_ = true;
			}
		}
	}
	if (authority_.empty() || path_.empty())
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	parseAuthority();
}

void	HttpUri::parseOrigin(std::string const &host)
{
	if (host.empty())
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	std::string	concatinated = host + raw_;
	parseUri(concatinated, host);
}

void	HttpUri::constructWithHostheader(std::string const &host)
{
	if (raw_.empty())
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	if (raw_.at(0) == '/')
		parseOrigin(host);
	else
		parseAbsolute(host);

// to lower host data
	ft::string	ft_host(host_);
	ft_host.to_lower();
	host_ = ft_host;
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

std::string	HttpUri::getPath(void) const
{
	return (path_);
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
	ft::str_map_const_iter	last = query_.end();
	std::advance(last, -1);
	std::ostringstream	oss;

	while (iter != end)
	{
		oss << iter->first << "=" << iter->second;
		if (iter != last)
			oss << "&";
		iter++;
	}
	return(oss.str());
}

static void	assertHex(std::string const &hex)
{
	ft::string	fthex(hex);

	if (!fthex.has_only(ft::string::PCHAR))
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
}

static std::string	decordHex(std::string const &hex)
{
	ft::string	first(hex.substr(1, 1));
	ft::string	second(hex.substr(2));
	std::string	decorded;

	if (!first.has_only(ft::string::HEXDIG) || !second.has_only(ft::string::HEXDIG))
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	decorded = "\\x"+ first.str() + second.str();
	assertHex(decorded);
	return (decorded);
}

std::string	HttpUri::percentDecoder(std::string const &str)
{
	std::string::const_iterator	iter = str.begin();
	std::string::const_iterator	begin = str.begin();
	std::string::const_iterator	end = str.end();
	std::string					decordedStr;

	while (iter != end)
	{
		if (*iter == '%')
		{
			if (std::distance(iter, end) < PERCENT_DECORD_SIZE)//%を含めて３桁が文字列の最後までなければ
				throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
			std::string	cordedStr = str.substr(std::distance(begin, iter), PERCENT_DECORD_SIZE);
			decordedStr += decordHex(cordedStr);
			std::advance(iter, PERCENT_DECORD_SIZE);
		}
		else
		{
			decordedStr.push_back(*iter);
			iter++;
		}
	}
	return (decordedStr);
}
