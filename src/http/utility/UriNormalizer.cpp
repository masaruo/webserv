#include "UriNormalizer.hpp"
#include "string.hpp"
#include "HttpException.hpp"
#include <algorithm>

std::size_t const	UriNormalizer::PERCENT_ENCODE_LEN = 3;

std::string	UriNormalizer::uniformSlash(std::string const &raw)
{
	if (raw.empty())
		return ("");

	std::string	uri(raw);
	std::replace(uri.begin(), uri.end(), '\\', '/');
	return (uri);
}

std::string	UriNormalizer::decodeDots(std::string const &raw)
{
	if (raw.empty())
		return ("");

	ft::string									ftraw(raw);
	ft::string::string_vector					split_by_slash = ftraw.split("/");
	ft::string::string_vector_iterator			iter = split_by_slash.begin();
	ft::string::string_vector_const_iterator	end = split_by_slash.end();
	ft::string::string_vector					normalized;

	while (iter != end)
	{
		if ((*iter == "." && iter->size() == 1) || iter->empty())
		{
			iter++;
			continue ;
		}
		else if (*iter == ".." && iter->size() == 2)
		{
			if (!normalized.empty())
				normalized.pop_back();
			else
				throw (HttpException(HttpCode::BAD_REQUEST));
		}
		else
		{
			normalized.push_back(*iter);
		}
		iter++;
	}
	std::string	res = ft::reverse_split(normalized, '/');

	if (ftraw.start_with('/') && ftraw.size() != 1)
		res.insert(0, 1, '/');
	if (ftraw.end_with('/') && ftraw.size() != 1)
		res.push_back('/');
	if (res.empty())
		res.push_back('/');
	return (res);
}

std::string	UriNormalizer::decodePercent(std::string const &raw)
{
	if (raw.empty())
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
				throw (HttpException(HttpCode::BAD_REQUEST));
			}
			percentStr = raw.substr(std::distance(begin, iter), UriNormalizer::PERCENT_ENCODE_LEN);
			std::istringstream iss(percentStr.substr(1));
			int value;
			iss >> std::hex >> value;
			if (iss.fail())
				throw (HttpException(HttpCode::BAD_REQUEST));
			decorded.push_back(static_cast<char>(value));

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
