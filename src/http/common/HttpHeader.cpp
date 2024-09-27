#include "HttpHeader.hpp"
#include <utility>
#include <algorithm>
#include "string.hpp"
#include "HttpStatus.hpp"

HttpHeader::HttpHeader()
:headers_()
{
	return ;
}

HttpHeader::HttpHeader(std::istringstream &iss)
{
	std::string	line;
	while (true)
	{
		std::getline(iss, line);
		ft::string trim_CR(line);
		trim_CR.trim(ft::string::CR);
		if (trim_CR.empty())
			break ;
		setHeader(trim_CR.str());
	}
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
	if (line == ft::string::CR)
	{
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	}
	ft::string	key, value;
	std::string::size_type loc = line.find(':');
	if (loc == std::string::npos)
	{
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	}
	key = line.substr(0, loc);
	value = line.substr(loc + 1);
	key.trim(ft::string::WS + ft::string::CR);
	value.trim(ft::string::WS + ft::string::CR);
	if (key.empty() || value.empty())
		throw (HttpStatus::HttpStatusException(HttpCode::BAD_REQUEST));
	setHeader(key, value);
}

void	HttpHeader::setHeader(std::string const &key, std::string const &value)
{
	headers_[key].push_back(value);
}

std::string	HttpHeader::getValue(std::string const &key) const
{
	if (hasHeader(key))
		return (headers_.at(key).front());
	else
		return ("");
}

bool	HttpHeader::hasHeader(std::string const &key) const
{
	if (headers_.find(key) == headers_.end())
		return (false);
	else
		return (true);
}

HttpHeader::map_vec_t	HttpHeader::data(void) const
{
	return (headers_);
}

ft::string 	HttpHeader::str(void) const
{
	const_iterator	iter = headers_.begin();
	const_iterator	end = headers_.end();
	ft::string		ans;

	while (iter != end)
	{
		std::string					combined;
		std::string					key = iter->first;
		std::vector<std::string>	values = iter->second;
		std::size_t					i = 0;
		combined = key + ": " + values.at(i);
		while (i < values.size() - 1)
		{
			combined += "; " + values.at(i);
			i++;
		}
		ans += combined;
		iter++;
	}
	return (ans);
}
