#include "UriNormalizer.hpp"
#include "string.hpp"
#include "HttpStatus.hpp"
#include "define.hpp"
#include <algorithm>
#include <sstream>

static std::string	concatStringVector(std::string const &raw, ft::string::string_vector const &string_vec, char delim);
static char			decodeHex(std::string const &str);

std::string	UriNormalizer::uniformSlashAndHandleDots(std::string const &raw)
{
	if (ft::is_empty<std::string>(raw))
		return ("");

	std::string	uri(raw);

	std::replace(uri.begin(), uri.end(), '\\', '/');
	
	std::string	DotsHandled = decodeDots(uri);
	return (DotsHandled);
}

std::string	UriNormalizer::decodePercentAndHandleDots(std::string const &raw)
{
	if (ft::is_empty(raw))
		return ("");

	ft::string	ftraw(raw);
	std::string	decoded, dotsHandled;

	decoded = decodePercent(ftraw);
	dotsHandled = decodeDots(decoded);

	return (dotsHandled);
}

std::string	UriNormalizer::decodeDots(std::string const &raw)
{
	if (ft::is_empty(raw))
		return ("");

	ft::string									ftraw(raw);
	ft::string::string_vector					split_by_slash = ftraw.split("/");
	ft::string::string_vector_iterator			str = split_by_slash.begin();
	ft::string::string_vector_const_iterator	end = split_by_slash.end();
	ft::string::string_vector					normalized;

	while (str != end)
	{
		if ((*str == "." && str->size() == 1) || str->empty())
		{
			str++;
			continue ;
		}
		else if (*str == ".." && str->size() == 2)
		{
			if (!normalized.empty())
				normalized.pop_back();
			else
				throw (HttpStatus::HttpStatusException(HttpCode::FORBIDDEN));
		}
		else
		{
			normalized.push_back(*str);
		}
		str++;
	}
	std::string	res = concatStringVector(raw, normalized, '/');
	return (res);
}

static char	decodeHex(std::string const &str)
{
	std::istringstream	iss(str.substr(1));
	int	value;
	iss >> std::hex >> value;
	if (iss.fail())
	{
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	}
	return (static_cast<char>(value));
}

std::string	UriNormalizer::decodePercent(std::string const &raw)
{
	if (ft::is_empty(raw))
		return ("");

	ft::string::const_iterator	iter = raw.begin();
	ft::string::const_iterator	begin = raw.begin();
	ft::string::const_iterator	end = raw.end();
	std::string					percentStr;
	std::string					decorded;

	while (iter != end)
	{
		if (*iter == '%')
		{
			if (std::distance(iter, end) < UriNormalizer::PERCENT_ENCODE_LEN)//%後の文字列が２つないとき
			{
				throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
			}
			percentStr = raw.substr(std::distance(begin, iter), UriNormalizer::PERCENT_ENCODE_LEN);
			decorded.push_back(decodeHex(percentStr));
			std::advance(iter, UriNormalizer::PERCENT_ENCODE_LEN);
		}
		else
		{
			decorded.push_back(*iter);
			iter++;
		}
	}
	return (decorded);
}

static std::string	concatStringVector(std::string const &raw, ft::string::string_vector const &string_vec, char delim)
{
	ft::string::string_vector_const_iterator	iter = string_vec.begin();
	ft::string::string_vector_const_iterator	end = string_vec.end();
	std::stringstream	ss;
	ft::string	ftraw(raw);

	if (ftraw.start_with('/'))
		ss << "/";

	while (iter != end)
	{
		ss << iter->str();
		if (iter + 1 != end || ftraw.end_with('/'))
			ss << delim;
		iter++;
	}
	return (ss.str());
}
