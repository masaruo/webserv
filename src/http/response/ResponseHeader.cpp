#include "ResponseHeader.hpp"
#include "Date.hpp"
#include "string.hpp"

ResponseHeader::ResponseHeader()
:AHeader()
{
	return ;
}

ResponseHeader::ResponseHeader(std::string const &response)
:AHeader()
{
	parseHeaderStr(response);
	return ;
}

ResponseHeader::~ResponseHeader()
{
	return ;
}

ResponseHeader::ResponseHeader(ResponseHeader const &rhs)
:AHeader(rhs)
{
	return ;
}

ResponseHeader &ResponseHeader::operator=(ResponseHeader const &rhs)
{
	if (this != &rhs)
	{
		AHeader::operator=(rhs);
	}
	return (*this);
}

void	ResponseHeader::parseHeaderStr(std::string const &res)
{
	std::istringstream	iss(res);
	ft::string			buf;

	while (true)
	{
		std::getline(iss, buf.str());
		if (buf == ft::string::CR)
			break ;
		add(buf.str());
	}
}

static void	assertLine_(ft::string const &line)
{
	bool	is_invalid = false;

	if (line.empty())
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

void	ResponseHeader::add(std::string const &line)
{
	assertLine_(line);
	std::string::size_type	posDoubleColon = line.find(":");
	ft::string				field = line.substr(0, posDoubleColon);
	field.trim(ft::string::CR);
	assertFieldName_(field);
	HeaderField fieldtype = strToEnum(field);

	ft::string const	&values = line.substr(posDoubleColon + 1);
	ft::string::string_vector	splitByComma = values.split(",");
	ft::string::string_vector_const_iterator	it = splitByComma.begin();
	while (it != splitByComma.end())
	{
		ft::string	value = *it;
		assertValue_(value);
		value.trim(ft::string::WS + ft::string::CR);
		fields_.addValue(fieldtype, value);
		it++;
	}
}
