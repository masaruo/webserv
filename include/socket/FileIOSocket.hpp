#pragma once
#include "ASocket.class.hpp"
#include "define.hpp"


class FileIOSocket : public ASocket
{
private:
	int			pair_fd_[2];
	int			target_fd_;
	std::string	buffer_;
	// bool		is_writing_;

	void	init(void);
public:
	FileIOSocket();
	~FileIOSocket();
	FileIOSocket(FileIOSocket const &rhs);
	FileIOSocket &operator=(FileIOSocket const &rhs);
	void		setSockaddr(void);
	ssize_t		readFile(std::string const &data);
	ssize_t		writeFile(int writeto, std::string const &data);
	std::string	getBufferData(void) const;

	std::string	read(std::string const &target_path);
};
