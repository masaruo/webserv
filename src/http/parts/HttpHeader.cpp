#include "HttpHeader.hpp"
#include <utility>
#include <algorithm>
#include "string.hpp"
#include "HttpException.hpp"
#include <sstream>

std::set<std::string>	HttpHeader::noDupHeaderSet_;

const std::string HttpHeader::HOST = "host";
const std::string HttpHeader::CONTENT_TYPE = "content-type";
const std::string HttpHeader::CONTENT_LENGTH = "content-length";
const std::string HttpHeader::CONTENT_ENCODING = "content-encoding";
const std::string HttpHeader::TRANSFER_ENCODING = "transfer-encoding";
const std::string HttpHeader::CONNECTION = "connection";
const std::string HttpHeader::USER_AGENT = "user-agent";
const std::string HttpHeader::ACCEPT = "accept";
const std::string HttpHeader::ACCEPT_ENCODING = "accept-encoding";
const std::string HttpHeader::ACCEPT_LANGUAGE = "accept-language";
const std::string HttpHeader::REFERER = "referer";
const std::string HttpHeader::AUTHORIZATION = "authorization";
const std::string HttpHeader::COOKIE = "cookie";
const std::string HttpHeader::SERVER = "server";
const std::string HttpHeader::LOCATION = "location";
const std::string HttpHeader::DATE = "date";
const std::string HttpHeader::LAST_MODIFIED = "last-modified";
const std::string HttpHeader::ETAG = "etag";
const std::string HttpHeader::CACHE_CONTROL = "cache-control";
const std::string HttpHeader::PRAGMA = "pragma";
const std::string HttpHeader::EXPIRES = "expires";
const std::string HttpHeader::CONTENT_DISPOSITION = "content-disposition";

void	HttpHeader::assertSemanticValue(void) const
{
	bool	is_invalid = false;

	if (!hasKey(HOST))
		is_invalid = true;
	if (hasKey(TRANSFER_ENCODING))
	{
		if (hasKey(CONTENT_LENGTH))
			is_invalid = true;
		std::string const &is_chunk = getLastValue(TRANSFER_ENCODING);
		if (is_chunk != "chunked")
			is_invalid = true;
	}
	if (hasKey(CONTENT_LENGTH) && hasKey(TRANSFER_ENCODING))
		is_invalid = true;
	if (hasKey(CONTENT_LENGTH))
	{
		try
		{
			ft::stonum<std::size_t>(getFirstValue(CONTENT_LENGTH));
		}
		catch(const std::invalid_argument& e)
		{
			is_invalid = true;
		}
	}
	if (is_invalid)
		throw (HttpException(HttpCode::BAD_REQUEST));
}

void	HttpHeader::setupNoDupHeaderSet(void)
{
	noDupHeaderSet_.insert(HOST);
	noDupHeaderSet_.insert(CONTENT_TYPE);
	noDupHeaderSet_.insert(CONTENT_LENGTH);
	noDupHeaderSet_.insert(CONTENT_ENCODING);
	noDupHeaderSet_.insert(TRANSFER_ENCODING);
	noDupHeaderSet_.insert("if-modified-since");
	noDupHeaderSet_.insert("if-unmodified-since");
	noDupHeaderSet_.insert("if-none-match");
	noDupHeaderSet_.insert("if-match");
}

HttpHeader::HttpHeader()
:vm::VecMap<std::string, std::string>()
{
	if (!noDupHeaderSet_.empty())
		setupNoDupHeaderSet();
	return ;
}

static void	assertHeaderLine(std::string const &line)
{
	ft::string	ftline(line);
	bool		is_invalid = false;

	if (ftline.empty())
		is_invalid = true;
	if (ftline.start_with(ft::string::WS))
		is_invalid = true;
	if (!ftline.end_with(ft::string::CR))
		is_invalid = true;
	if (ftline.size() > ft::MAX_FIELD_LEN)
		is_invalid = true;
	if (!ftline.has(":"))
		is_invalid = true;

	if (is_invalid)
		throw (HttpException(HttpCode::BAD_REQUEST));
}

static void	assertHeaderName(std::string const &name)
{
	ft::string	ftname(name);
	bool		is_invalid = false;

	if (ftname.empty())
		is_invalid = true;
	if (!ftname.has_only(ft::string::TOKEN))
		is_invalid = true;
	
	if (is_invalid)
		throw (HttpException(HttpCode::BAD_REQUEST));
}

static void	assertHeaderValue(std::string const &a_value)
{
	ft::string	ftvalue(a_value);
	bool		is_invalid = false;

	if (ftvalue.empty())
		is_invalid = true;
	if (!ftvalue.has_only(ft::string::VCHAR + ft::string::WS))
		is_invalid = true;

	if (is_invalid)
		throw (HttpException(HttpCode::BAD_REQUEST));
}

HttpHeader::HttpHeader(std::istringstream &iss)
:vm::VecMap<std::string, std::string>()
{
	std::string	line;
	while (true)
	{
		std::getline(iss, line);
		if (line == ft::string::CR)//!ヘッダーの最後（CRLFCRLF）だが、LFはGETLINEで削除される＝single CR
			break ;
		assertHeaderLine(line);
		ft::string ftline = line;
		ftline.trim(ft::string::CR);
		addValue(ftline.str());
	}
	assertSemanticValue();
}

HttpHeader::~HttpHeader()
{
	return ;
}

HttpHeader::HttpHeader(HttpHeader const &rhs)
:vm::VecMap<std::string, std::string>(rhs)
{
	return ;
}

HttpHeader &HttpHeader::operator=(HttpHeader const &rhs)
{
	if (this != &rhs)
	{
		vm::VecMap<std::string, std::string>::operator = (rhs);
	}
	return (*this);
}

void	HttpHeader::addValue(std::string const &line)
{
	ft::string	key, values;
	std::string::size_type loc = line.find(':');

	key = line.substr(0, loc);
	assertDupHeaderName(key);
	assertHeaderName(key);

	values = line.substr(loc + 1);
	assertHeaderValue(values);

	ft::string::string_vector					split_by_comma = values.split(",");
	ft::string::string_vector_const_iterator	iter = split_by_comma.begin();
	ft::string::string_vector_const_iterator	end = split_by_comma.end();

	while (iter != end)
	{
		if (!iter->empty())
		{
			ft::string	value = *iter;
			value.trim(ft::string::WS);
			addValue(key, value);
		}
		iter++;
	}
}

void	HttpHeader::assertDupHeaderName(std::string const &name) const
{
	std::set<std::string>::const_iterator foundPos;
	std::set<std::string>::const_iterator end = noDupHeaderSet_.end();
	foundPos = noDupHeaderSet_.find(name);
	if (foundPos != end)
		throw (HttpException(HttpCode::BAD_REQUEST));
}

void	HttpHeader::addValue(std::string const &key, std::string const &value)
{
	ft::string	ftkey(key), ftvalue(value);

	ftkey.to_lower();

	assertDupHeaderName(ftkey);
	assertHeaderName(ftkey);
	assertHeaderValue(value);
	if (data().size() > ft::MAX_HEADERS_NUM)
		throw (HttpException(HttpCode::BAD_REQUEST));
	vm::VecMap<std::string, std::string>::addValue(ftkey, ftvalue);
}

std::size_t	HttpHeader::getContentLen(void) const
{
	try
	{
		std::size_t	res = ft::stonum<std::size_t>(getFirstValue(CONTENT_LENGTH));
		return (res);
	}
	catch(const std::invalid_argument& e)
	{
		throw (HttpException(HttpCode::BAD_REQUEST));	
	}
}

std::string 	HttpHeader::to_string(void) const
{
	const_iterator	iter = cbegin();
	const_iterator	end = cend();
	std::stringstream	ss;

	while (iter != end)
	{
		ss << iter->first;
		ss << ":";

		ft::str_vec	value = iter->second;
		ft::str_vec::const_iterator	vec_iter = value.begin();
		ft::str_vec::const_iterator vec_end = value.end();
		while (vec_iter != vec_end)
		{
			ss << *vec_iter;
			if (vec_iter + 1 != vec_end)
				ss << ",";
			vec_iter++;
		}
		ss << ft::string::CR << ft::string::LF;
		iter++;
	}
	return (ss.str());
}
