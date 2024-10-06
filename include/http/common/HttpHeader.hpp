#pragma once
#include <set>
#include "StrVecMap.hpp"
#include "HttpStatus.hpp"

class HttpHeader : public svm::StrVecMap
{
public:
	static std::size_t const	MAX_FIELD_LEN = 4096;
	static std::size_t const	MAX_HEADERS = 100;
private:
	static std::set<std::string>	noDupHeaderSet_;
	void							setElem(std::string const &line);
	void							setupNoDupHeaderSet(void);
	void	assertDupHeaderName(std::string const &name) const;
	void	assertSemanticValue(void) const;
public:
	HttpHeader();
	explicit HttpHeader(std::istringstream &iss);
	~HttpHeader();
	HttpHeader(HttpHeader const &rhs);
	HttpHeader &operator=(HttpHeader const &rhs);
	void		setElem(std::string const &key, std::string const &value);
	std::size_t	getContentLen(void) const;
	std::string	to_string(void) const;
};
