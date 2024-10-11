#pragma once
#include <string>

class Date
{
private:
	Date();
	~Date();
	Date(Date const &rhs);
	Date &operator=(Date const &rhs);
public:
	static std::string	time(void);
};
