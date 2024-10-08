#pragma once
#include <string>
#include <sys/types.h>
#include <stdexcept>

namespace io
{

class IO
{
private:
	int			fd_;
	std::string	data_;
	std::string	keep_;
	std::size_t	max_data_size_;
	std::size_t	buf_size_;
	bool		isChunked_;
	IO();//=delete

	bool	parseRecv(std::string const &buf, std::size_t readSize);

	void	recvNormal(std::size_t readSize);
	// ssize_t	recvChunked(void);
	// ssize_t	sendNormal(void);
	// ssize_t	sendChunked(void);
public:
	explicit IO(int fd, std::size_t	dataSize = 800000, std::size_t bufSize = 600000, bool isChunked = false);
	~IO();
	IO(IO const &rhs);
	IO &operator=(IO const &rhs);

	std::string		recv(void);
	std::string		recv(std::size_t readSize);
	// void			send(void);
	// ssize_t		read(void);
	// ssize_t		write(void);
	void			clear(void);
};
}
