#include "IO.class.hpp"
#include "sys/socket.h"
#include "define.hpp"
#include "HttpException.hpp"
#include <cerrno>
#include <stdexcept>
#include <limits>

io::IO::IO(int fd, std::size_t dataSize, std::size_t bufSize, bool isChunked)
:fd_(fd)
,data_()
,keep_()
,max_data_size_(dataSize)
,buf_size_(bufSize)
,isChunked_(isChunked)
{
	// data_.reserve(dataSize);
	// keep_.reserve(bufSize);
	return ;
}

io::IO::~IO()
{
	return ;
}

io::IO::IO(IO const &rhs)
:fd_(rhs.fd_)
,data_(rhs.data_)
,keep_(rhs.keep_)
,max_data_size_(rhs.max_data_size_)
,buf_size_(rhs.buf_size_)
,isChunked_(rhs.isChunked_)
{
	return ;
}

io::IO &io::IO::operator=(IO const &rhs)
{
	if (this != &rhs)
	{
		fd_ = rhs.fd_;
		data_ = rhs.data_;
		keep_ = rhs.keep_;
		max_data_size_ = rhs.max_data_size_;
		buf_size_ = rhs.buf_size_;
		isChunked_ = rhs.isChunked_;
	}
	return (*this);
}

bool	io::IO::parseRecv(std::string const &buf, std::size_t readSize)
{
	std::string::size_type	combinedSize = data_.size() + buf.size();
	std::string::size_type	posCRLFCRLF = buf.find("\r\n\r\n");
	if (combinedSize > max_data_size_)
	{
		throw (std::out_of_range("IO.cpp:52. recv data surpassed max size."));
	}
	if (combinedSize > readSize)
	{
		std::size_t const	appendSize = combinedSize - readSize;
		data_.append(buf.substr(0, appendSize));
		return (true);
	}
	else if (posCRLFCRLF != std::string::npos)
	{
		data_.append(buf, 0, posCRLFCRLF + 4);//CRLFCRLFは残す
		keep_ = buf.substr(posCRLFCRLF + 4);
		return (true);
	}
	else
	{
		data_.append(buf, 0, buf.size());
		return (false);
	}
}

void	io::IO::recvNormal(std::size_t readSize  = std::numeric_limits<std::size_t>::max())
{
	std::string	buf;

	if (!keep_.empty())
	{
		data_.append(keep_);
		keep_.clear();
	}

	while (true)
	{
		buf.resize(buf_size_);
		ssize_t bytes = ::recv(fd_, &buf[0], buf_size_, 0);
		if (bytes == ft::err)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;
			else
				throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
		}
		else if (bytes == ft::eof)
			break ;
		else
		{
			buf.resize(bytes);
			bool toBreak = parseRecv(buf, readSize);
			if (toBreak == true)
				break ;
		}
		buf.clear();
	}
}

std::string	io::IO::recv(void)
{
	recvNormal();
	return (data_);
}

std::string	io::IO::recv(std::size_t readSize)
{
	recvNormal(readSize);
	return (data_);
}

void	io::IO::clear(void)
{
	data_.clear();
	keep_.clear();
	buf_size_ = 0;
	buf_size_ = 0;
	isChunked_ = false;
}
