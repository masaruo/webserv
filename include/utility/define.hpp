#pragma once
#include <string>

namespace ft
{
	int const	eof = 0;
	int const	err = -1;

	typedef enum 
	{
		GET,
		POST,
		DELETE,
		ERROR
	}	http_method_t;
}
