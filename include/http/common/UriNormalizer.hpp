#pragma once
#include <string>

class UriNormalizer
{
private:
	UriNormalizer();
	~UriNormalizer();
	UriNormalizer(UriNormalizer const &rhs);
	UriNormalizer &operator=(UriNormalizer const &rhs);
public:
	static std::size_t const PERCENT_ENCODE_LEN;
	static std::string	uniformSlash(std::string const &raw);
	static std::string	decodeDots(std::string const &raw);
	static std::string	decodePercent(std::string const &raw);
};

