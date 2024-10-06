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

	if (!hasElem("host"))
		is_invalid = true;
	if (hasElem("content-length"))
	{
		try
		{
			ft::stonum<std::size_t>(getValueAtFirst("content-length"));
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

void	HttpHeader::setupNoDupHeaderSet(void)
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
:svm::StrVecMap()
{
	if (!noDupHeaderSet_.empty())
		setupNoDupHeaderSet();
	return ;
}

static void	asserttHeaderLine(std::string const &line)
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
:svm::StrVecMap()
{
	std::string	line;
	while (true)
	{
		std::getline(iss, line);
		if (line == ft::string::CR)//!ヘッダーの最後（CRLFCRLF）だが、LFはGETLINEで削除される＝single CR
			break ;
		asserttHeaderLine(line);
		ft::string ftline = line;
		ftline.trim(ft::string::CR);
		setElem(ftline.str());
	}
	assertSemanticValue();
}

HttpHeader::~HttpHeader()
{
	return ;
}

HttpHeader::HttpHeader(HttpHeader const &rhs)
:svm::StrVecMap(rhs)
{
	return ;
}

HttpHeader &HttpHeader::operator=(HttpHeader const &rhs)
{
	if (this != &rhs)
	{
		svm::StrVecMap::operator = (rhs);
	}
	return (*this);
}

void	HttpHeader::setElem(std::string const &line)
{
	ft::string	key, values;
	std::string::size_type loc = line.find(':');

	key = line.substr(0, loc);
	assertDupHeaderName(key);

	values = line.substr(loc + 1);
	assertHeaderValueLine(values);

	ft::string::string_vector					split_by_comma = values.split(",");
	ft::string::string_vector_const_iterator	iter = split_by_comma.begin();
	ft::string::string_vector_const_iterator	end = split_by_comma.end();

	while (iter != end)
	{
		if (!iter->empty())
		{
			ft::string	value = *iter;
			value.trim(ft::string::WS);
			setElem(key, value);
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

void	HttpHeader::setElem(std::string const &name, std::string const &value)
{
	ft::string	ftname(name), ftvalue(value);

	ftname.to_lower();

	if (hasElem(ftname.str()))
		assertDupHeaderName(ftname.str());
	if (data().size() > MAX_HEADERS)
		throw (HttpException(HttpCode::BAD_REQUEST));

	StrVecMap::setElem(name, value);
}

std::size_t	HttpHeader::getContentLen(void) const
{
	try
	{
		std::size_t	res = ft::stonum<std::size_t>(getValueAtFirst("content-length"));
		return (res);
	}
	catch(const std::invalid_argument& e)
	{
		throw (HttpException(HttpCode::BAD_REQUEST));	
	}
}

std::string 	HttpHeader::to_string(void) const
{
	svm::StrVecMap::const_iterator	iter = data().begin();
	svm::StrVecMap::const_iterator	end = data().end();
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
