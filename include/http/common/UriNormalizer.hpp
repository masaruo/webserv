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
	static std::size_t const PERCENT_ENCODE_LEN = 3;
	static std::string	normalizeFullUri(std::string const &raw);
	static std::string	normalizeComponent(std::string const &raw);
};

