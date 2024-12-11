#include "Fd.hpp"
#include <unistd.h>

Fd::Fd(int fd)
:fd_(fd)
{
	return ;
}

Fd::~Fd()
{
	if (fd_ > 2)
		close (fd_);
}

void	Fd::set(int new_fd)
{
	fd_ = new_fd;
}

int	Fd::get(void) const
{
	return (fd_);
}

int	Fd::release(void)
{
	int	tmp = fd_;
	fd_ = -1;
	return (tmp);
}

int	Fd::reset(int new_fd)
{
	if (fd_ > 2)
	{
		int	res = close(fd_);
		if (res == -1)
			return (-1);
	}
	fd_ = new_fd;
	return (0);
}
