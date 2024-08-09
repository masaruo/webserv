#pragma once

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
};
}// end of namespace ft
