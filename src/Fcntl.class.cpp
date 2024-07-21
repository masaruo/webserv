#include "Fcntl.class.hpp"
#include "define.hpp"
#include <fcntl.h>

int	ft::Fcntl::setNonBlock(int fd)
{
	int	flags = 0;

	flags = fcntl(fd, F_GETFL);
	if (flags == ft::ERR)
	{
		//todo error
	}
	flags = flags | O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) == ft::ERR)
	{
		//todo error
	}
	return (flags);
}
