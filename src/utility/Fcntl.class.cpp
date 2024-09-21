#include "Fcntl.class.hpp"
#include "define.hpp"
#include <fcntl.h>

int	ft::Fcntl::setNonBlock(int fd)
{
	int	flags = 0;

	// flags = fcntl(fd, F_GETFL);//! not allowed. only F_SETFL, O_NONBLOCK and FD_CLOEXEC
	// if (flags == ft::err)
	// {
	// 	//todo error
	// }
	flags = flags | O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) == ft::err)
	{
		//todo error
	}
	return (flags);
}
