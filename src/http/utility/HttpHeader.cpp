#include "HttpHeader.hpp"
#include <utility>
#include "string.hpp"

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
		return ;
	ft::string	to_mod(line);
	ft::string::string_vector	split_by_dcolon = to_mod.split(":");
	std::string	key = split_by_dcolon.at(0);
	split_by_dcolon.at(1).trim(ft::string::SP + ft::string::CR);
	std::string value = split_by_dcolon.at(1);
	//todo verification
	setHeader(key, value);
	
}

void	HttpHeader::setHeader(std::string const &key, std::string const &value)
{
	headers_[key].push_back(value);
}

std::string	HttpHeader::getHeader(std::string const &key) const
{
	return (headers_.at(key).front());
	//todo error - out_of_range will be thrown
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
		// combined += "\r\n";
		ans += combined;
		iter++;
	}
	return (ans);
}
