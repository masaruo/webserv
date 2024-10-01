#include "HttpHeader.hpp"
#include <utility>
#include <algorithm>
#include "string.hpp"
#include "HttpException.hpp"
#include <sstream>

std::set<std::string>	HttpHeader::noDupHeaderSet_;

void	HttpHeader::assertSemanticValue(void) const
{
	bool	is_invalid = false;

	if (!hasHeader("host"))
		is_invalid = true;
	if (hasHeader("content-length"))
	{
		try
		{
			ft::stonum<std::size_t>(getFirstValue("content-length"));
		}
		catch(const std::invalid_argument& e)
		{
			is_invalid = true;
		}
	}
	if (is_invalid)
		throw (HttpException(HttpCode::BAD_REQUEST));
	//todo 
	//connection header
	//transfer-encoding
}

void	HttpHeader::setupHeaderWithNoDuplication(void)
{
	noDupHeaderSet_.insert("host");
	noDupHeaderSet_.insert("content-type");
	noDupHeaderSet_.insert("content-length");
	noDupHeaderSet_.insert("content-encoding");
	noDupHeaderSet_.insert("transfer-encoding");
	noDupHeaderSet_.insert("if-modified-since");
	noDupHeaderSet_.insert("if-unmodified-since");
	noDupHeaderSet_.insert("if-none-match");
	noDupHeaderSet_.insert("if-match");
}

HttpHeader::HttpHeader()
:headers_()
{
	if (!noDupHeaderSet_.empty())
		setupHeaderWithNoDuplication();
	return ;
}

static void	assetHeaderLine(std::string const &line)
{
	ft::string	ftline(line);
	bool		is_invalid = false;

	if (ftline.empty())
		is_invalid = true;
	if (ftline.start_with(ft::string::WS))
		is_invalid = true;
	if (!ftline.end_with(ft::string::CR))
		is_invalid = true;
	if (ftline.size() > HttpHeader::MAX_FIELD_LEN)
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

static void	assertHeaderValueLine(std::string const &line)
{
	ft::string	ftline(line);
	bool		is_invalid = false;

	if (ftline.empty())
		is_invalid = true;
	if (!ftline.has_only(ft::string::FIELD_VALUE))
		is_invalid = true;

	if (is_invalid)
		throw (HttpException(HttpCode::BAD_REQUEST));
}

static void	assetHeaderValue(std::string const &a_value)
{
	ft::string	ftvalue(a_value);
	bool		is_invalid = false;

	if (ftvalue.empty())
		is_invalid = true;
	if (!ftvalue.has_only(ft::string::VCHAR + ft::string::OBS_TEXT))
		is_invalid = true;

	if (is_invalid)
		throw (HttpException(HttpCode::BAD_REQUEST));
}

HttpHeader::HttpHeader(std::istringstream &iss)
{
	std::string	line;
	while (true)
	{
		std::getline(iss, line);
		if (line == ft::string::CR)//!ヘッダーの最後（CRLFCRLF）だが、LFはGETLINEで削除される＝single CR
			break ;
		assetHeaderLine(line);
		ft::string ftline = line;
		ftline.trim(ft::string::CR);
		setHeader(ftline.str());
	}
	assertSemanticValue();
}

HttpHeader::~HttpHeader()
{
	return ;
}

HttpHeader::HttpHeader(HttpHeader const &rhs)
:headers_(rhs.headers_)
{
	return ;
}

HttpHeader &HttpHeader::operator=(HttpHeader const &rhs)
{
	if (this != &rhs)
	{
		headers_ = rhs.headers_;
	}
	return (*this);
}

void	HttpHeader::setHeader(std::string const &line)
{
	ft::string	name, values;
	std::string::size_type loc = line.find(':');

	name = line.substr(0, loc);
	assertDupHeaderName(name);

	values = line.substr(loc + 1);
	assertHeaderValueLine(values);
	values.trim(ft::string::WS);

	setHeader(name.str(), values.str());
}

bool	HttpHeader::hasHeader(std::string const &key) const
{
	if (headers_.find(key) == headers_.end())
		return (false);
	else
		return (true);
}

void	HttpHeader::assertDupHeaderName(std::string const &name) const
{
	std::set<std::string>::const_iterator foundPos;
	std::set<std::string>::const_iterator end = noDupHeaderSet_.end();
	foundPos = noDupHeaderSet_.find(name);
	if (foundPos != end)
		throw (HttpException(HttpCode::BAD_REQUEST));
}

void	HttpHeader::setHeader(std::string const &name, std::string const &value)
{
	ft::string	ftname(name), ftvalue(value);

	ftname.to_lower();

	if (hasHeader(ftname.str()))
		assertDupHeaderName(ftname.str());
	if (headers_.size() > MAX_HEADERS)
		throw (HttpException(HttpCode::BAD_REQUEST));

	headers_[ftname].push_back(ftvalue);
}

std::string	HttpHeader::getFirstValue(std::string const &key) const
{
	if (hasHeader(key))
		return (headers_.at(key).front());
	else
		return ("");
}

std::string	HttpHeader::getLastValue(std::string const &key) const
{
	if (hasHeader(key))
		return (headers_.at(key).back());
	else
		return ("");
}

ft::str_vec	HttpHeader::getValues(std::string const &key) const
{
	return (headers_.at(key));
}

std::size_t	HttpHeader::getContentLen(void) const
{
	try
	{
		std::size_t	res = ft::stonum<std::size_t>(getFirstValue("content-length"));
		return (res);
	}
	catch(const std::invalid_argument& e)
	{
		throw (HttpException(HttpCode::BAD_REQUEST));	
	}
}

HttpHeader::map_vec_t	HttpHeader::data(void) const
{
	return (headers_);
}

std::string 	HttpHeader::to_string(void) const
{
	const_iterator		iter = headers_.begin();
	const_iterator		end = headers_.end();
	std::ostringstream	oss;

	while (iter != end)
	{
		oss << iter->first << ":";

		ft::str_vec::const_iterator it = iter->second.begin();
		ft::str_vec::const_iterator end = iter->second.end();
		while (it != end)
		{
			oss << *it;
			it++;
		}
		iter++;
	}
	oss << ft::string::CR << ft::string::LF;
	return (oss.str());
}
