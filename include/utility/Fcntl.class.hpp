#pragma once
#include <cstddef>

namespace ft
{
class Fcntl
{
private:
	Fcntl();
	~Fcntl();
	Fcntl(Fcntl const &rhs);
	Fcntl &operator=(Fcntl const &rhs);
public:
	static int	setNonBlock(int fd);
	static int	setNonBlock(int *fds, std::size_t size);
};
}// end of namespace ft
