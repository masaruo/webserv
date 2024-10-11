#pragma once
#include "string.hpp"
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
	std::size_t	max_data_size_;
	std::size_t	buf_size_;
	bool		isChunked_;
	IO();//=delete
	ssize_t		smartRecv(int fd, std::string &buf) const;
	ssize_t		smartRecv(int fd, std::string &buf, std::size_t readsize) const;
	void		recv_internal(std::size_t readSize);

public:
	explicit IO(int fd, std::size_t	dataSize = 800000, std::size_t bufSize = 600000, bool isChunked = false);
	~IO();
	IO(IO const &rhs);
	IO &operator=(IO const &rhs);

	std::string		recv(void);
	std::string		recv(std::size_t readSize);
	std::string		recv(std::string const &transfer_encoding_value);
	void			send(std::string const &data) const;
	// ssize_t		read(void);
	// ssize_t		write(void);
	void			clear(void);
	std::size_t		getSize(void) const;
};
}
