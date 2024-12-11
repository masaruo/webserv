#pragma once
#include <string>

class Fd
{
private:
	int	fd_;
public:
	Fd(int fd = -1);
	// Fd(std::string const &path, int flags);
	~Fd();
	void	set(int new_fd);
	int		get(void) const;
	int		release(void);
	int		reset(int new_fd = -1);
private:
	Fd(Fd const &rhs);
	Fd &operator=(Fd const &rhs);
};
