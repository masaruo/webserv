#include "RequestHeader.hpp"
#include "string.hpp"
#include "HttpException.hpp"
#include <algorithm>

static RequestHeader::headerSet	initNoDup_(void)
{
	RequestHeader::headerSet	s;
	s.insert(RequestHeader::HOST);
	s.insert(RequestHeader::CONTENT_TYPE);
	s.insert(RequestHeader::CONTENT_LENGTH);
	s.insert(RequestHeader::CONTENT_ENCODING);
	s.insert(RequestHeader::TRANSFER_ENCODING);
	s.insert(RequestHeader::IF_MODIFIED_SINCE);
	s.insert(RequestHeader::IF_UNMODIFIED_SINCE);
	s.insert(RequestHeader::IF_NONE_MATCH);
	s.insert(RequestHeader::IF_MATCH);
	return (s);
}

RequestHeader::RequestHeader()
:AHeader()
,noDup_(initNoDup_())
{
	return ;
}

RequestHeader::RequestHeader(std::string const &request)
:AHeader()
,noDup_(initNoDup_())
{
	parseHeaderStr(request);
	assertHeader();
	return ;
}

RequestHeader::~RequestHeader()
{
	return ;
}

RequestHeader::RequestHeader(RequestHeader const &rhs)
:AHeader(rhs)
,noDup_(rhs.noDup_)
{
	return ;
}

RequestHeader &RequestHeader::operator=(RequestHeader const &rhs)
{
	if (this != &rhs)
	{
		AHeader::operator=(rhs);
		noDup_ = rhs.noDup_;
	}
	return (*this);
}

void	RequestHeader::parseHeaderStr(std::string const &request)
{
	std::istringstream	iss(request);
	ft::string			buf;

	while (true)
	{
		std::getline(iss, buf.str());
		if (buf == ft::string::CR)
			break ;
		add(buf);
	}
}

void	RequestHeader::assertHeader(void) const
{
	if (!fields_.hasKey(HOST))
		throw (HttpException(HttpCode::BAD_REQUEST));

	if (fields_.hasKey(TRANSFER_ENCODING) && fields_.hasKey(CONTENT_LENGTH))
		throw (HttpException(HttpCode::BAD_REQUEST));

	if (fields_.hasKey(TRANSFER_ENCODING))
	{
		std::string const &last = fields_.getLastValue(TRANSFER_ENCODING);
		if (last != "chunked")
			throw (HttpException(HttpCode::BAD_REQUEST));
	}

	if (fields_.hasKey(CONTENT_LENGTH))
	{
		try
		{
			ft::stonum<std::size_t>(fields_.getFirstValue(CONTENT_LENGTH));
		}
		catch(std::invalid_argument const &e)
		{
			throw (HttpException(HttpCode::BAD_REQUEST));
		}
		
	}
}

static void	assertLine_(ft::string const &line)
{
	bool	is_invalid = false;

	int cnt = std::count(line.begin(), line.end(), ':');
	if (cnt == 0)
		is_invalid = true;
	else if (line.empty())
		is_invalid = true;
	else if (line.start_with(ft::string::WS))
		is_invalid = true;
	else if (!line.end_with(ft::string::CR))
		is_invalid = true;
	else if (line.size() >ft::MAX_FIELD_LEN)
		is_invalid = true;

	if (is_invalid)
		throw (HttpException(HttpCode::BAD_REQUEST));
}

static void	assertFieldName_(ft::string const &name)
{
	if (name.empty() || !name.has_only(ft::string::TOKEN))
		throw (HttpException(HttpCode::BAD_REQUEST));
}

static void	assertValue_(ft::string const &value)
{
	ft::string trimmed = value;
	trimmed.trim(ft::string::CR);
	if (value.empty() || !trimmed.has_only(ft::string::VCHAR + ft::string::WS))
		throw (HttpException(HttpCode::BAD_REQUEST));
}

static void	assertNoDupHeaderField(AHeader::vecmap const &fields_, RequestHeader::headerSet const &noDupSet, RequestHeader::HeaderField field)
{
	RequestHeader::headerSet::const_iterator	found = noDupSet.find(field);
	if (fields_.hasKey(field) && found != noDupSet.end())
		throw (HttpException(HttpCode::BAD_REQUEST));
}

void	RequestHeader::add(std::string const &line)
{
	assertLine_(line);
	std::string::size_type	posDoubleColon = line.find(":");
	ft::string const	&field = line.substr(0, posDoubleColon);
	assertFieldName_(field);
	HeaderField fieldtype = strToEnum(field);
	assertNoDupHeaderField(fields_, noDup_, fieldtype);

	ft::string const	&values = line.substr(posDoubleColon + 1);
	ft::string::string_vector	splitByComma = values.split(",");
	ft::string::string_vector_const_iterator	it = splitByComma.begin();
	while (it != splitByComma.end())
	{
		ft::string	value = *it;
		value.trim(ft::string::CR);
		value.trim(ft::string::WS);
		assertValue_(value);
		fields_.addValue(fieldtype, value);
		it++;
	}
}
