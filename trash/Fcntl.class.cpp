#include "Fcntl.class.hpp"
#include "define.hpp"
#include <fcntl.h>

int	ft::Fcntl::setNonBlock(int fd)
{
	int	flags = 0;

	flags = O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) == ft::err)
	{
		//todo error
	}
	return (flags);
}

int	ft::Fcntl::setNonBlock(int *fds, std::size_t size)
{
	std::size_t	i = 0;
	while (i < size)
	{
		setNonBlock(fds[i]);
		i++;
	}
}
