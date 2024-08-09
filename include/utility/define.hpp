#pragma once
#include <string>

namespace ft
{
	int const	eof = 0;
	int const	err = -1;
	std::string const	SP = "32";
	std::string const	HTAB = "9";
	std::string const	VT = "11";
	std::string const	FF = "12";
	std::string const	CR = "13";
	std::string const	LF = "10";
	std::string const	CRLF = CR + LF;
}
