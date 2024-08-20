#include "define.hpp"

std::size_t	ft::stosizet(std::string const &numStr)
{
	std::stringstream	ss(numStr);
	std::size_t			num = 0;
	ss >> num;
	if (ss.failbit)//? is it correct?
	{
		//todo error?
	}
	return (num);
}
