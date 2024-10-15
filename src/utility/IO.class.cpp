#include "IO.class.hpp"
#include "sys/socket.h"
#include "define.hpp"
#include "HttpException.hpp"
#include <cerrno>
#include <stdexcept>
#include <limits>
#include <unistd.h>

namespace io
{

static std::size_t	getChunkSize(std::string const &line);

IO::IO(int fd, std::size_t dataSize, std::size_t bufSize, bool isChunked)
:fd_(fd)
,data_()

,max_data_size_(dataSize)
,buf_size_(bufSize)
,isChunked_(isChunked)
{

	return ;
}

IO::~IO()
{
	return ;
}

IO::IO(IO const &rhs)
:fd_(rhs.fd_)
,data_(rhs.data_)
,max_data_size_(rhs.max_data_size_)
,buf_size_(rhs.buf_size_)
,isChunked_(rhs.isChunked_)
{
	return ;
}

IO &io::IO::operator=(IO const &rhs)
{
	if (this != &rhs)
	{
		fd_ = rhs.fd_;
		data_ = rhs.data_;
		max_data_size_ = rhs.max_data_size_;
		buf_size_ = rhs.buf_size_;
		isChunked_ = rhs.isChunked_;
	}
	return (*this);
}

ssize_t	IO::smartRecv(int fd, std::string &buf, std::size_t readsize) const
{
	ssize_t	bytes;
	std::string	peekStr = "";
	std::size_t	remainToRead = buf_size_;

	peekStr.resize(buf_size_);
	bytes = ::recv(fd, &peekStr[0], buf_size_, MSG_PEEK | MSG_DONTWAIT);
	if (bytes == ft::err)
		return (bytes);

	peekStr.resize(bytes);

	std::string::size_type posCRLFCRLF = peekStr.find("\r\n\r\n");
	if (posCRLFCRLF != std::string::npos)
	{
		remainToRead = posCRLFCRLF + 4;
	}
	if (readsize != std::numeric_limits<std::size_t>::max())
	{
		remainToRead = readsize - data_.size();
	}

	buf.resize(remainToRead);
	bytes = ::recv(fd, &buf[0], remainToRead, MSG_DONTWAIT);
	return (bytes);
}

ssize_t	IO::smartRecv(int fd, std::string &buf) const
{
	ssize_t	bytes = 0;
	ssize_t	sizeToRead = 0;
	std::string	peekSizeStr = "";
	std::string	contentStr = "";
	std::string::size_type	posCRLF = 0;

	peekSizeStr.resize(buf_size_);
	bytes = ::recv(fd, &peekSizeStr[0], buf_size_, MSG_PEEK | MSG_DONTWAIT);
	if (bytes == ft::err)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));


	peekSizeStr.resize(bytes);
	posCRLF = peekSizeStr.find("\r\n");
	if (posCRLF == std::string::npos)// /r/n not in buf size => error
		throw (HttpException(HttpCode::BAD_REQUEST));

	peekSizeStr.resize(posCRLF + 2);
	bytes = ::recv(fd, &peekSizeStr[0], posCRLF + 2, MSG_DONTWAIT);
	if (bytes == ft::err)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

	sizeToRead = getChunkSize(peekSizeStr);

	if (data_.size() + sizeToRead > max_data_size_)
		throw (HttpException(HttpCode::BAD_REQUEST));

	contentStr.resize(sizeToRead + 2);
	bytes = ::recv(fd, &contentStr[0], sizeToRead + 2, MSG_DONTWAIT);
	if (bytes == ft::err)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	else if (bytes != sizeToRead + 2)
		throw (HttpException(HttpCode::BAD_REQUEST));

	contentStr.resize(bytes);

	if (sizeToRead == 0)
	{
		if (contentStr != "\r\n")
			throw (HttpException(HttpCode::BAD_REQUEST));
		buf = contentStr;
		return (0);
	}

	ft::string	ftContent(contentStr);
	if (!ftContent.end_with_str("\r\n"))
		throw (HttpException(HttpCode::BAD_REQUEST));

	ftContent.trim(ft::string::CRLF);
	buf = ftContent;
	return (bytes);
}

void	IO::recv_internal(std::size_t readSize  = std::numeric_limits<std::size_t>::max())
{
	std::string	buf;

	while (true)
	{
		buf.resize(buf_size_);
		ssize_t	bytes = smartRecv(fd_, buf, readSize);
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
			data_.append(buf);
			std::string::size_type	posCRLFCRLF = buf.find("\r\n\r\n");
			if (posCRLFCRLF != std::string::npos)
				break ;
		}
		buf.clear();
	}
}

static std::size_t	getChunkSize(std::string const &line)
{
	ft::string					ftline(line);
	ft::string::string_vector	split = ftline.split(ft::string::WS + ";=");
	std::size_t					chunk_size = 0;

	if (split.empty() || split[0].empty())
		throw (HttpException(HttpCode::BAD_REQUEST));

	std::stringstream	ss;
	ss << std::hex << split[0].str();
	ss >> chunk_size;
	if (ss.fail())
		throw (HttpException(HttpCode::BAD_REQUEST));

	return (chunk_size);
}


std::string	IO::recv(std::string const &transfer_ecoding_value)
{
	if (transfer_ecoding_value != "chunked")
		return (recv());

	clear();
	std::string	buf = "";
	std::size_t	bytes = 0;
	while (true)
	{
		bytes = smartRecv(fd_, buf);
		if (bytes == 0)
			break ;
		data_.append(buf);
	}
	return (data_);
}

std::string	IO::recv(void)
{
	clear();
	recv_internal();
	return (data_);
}

std::string	IO::recv(std::size_t readSize)
{
	clear();
	recv_internal(readSize);
	return (data_);
}

void	IO::send(std::string const &data) const
{
	std::size_t	total_sent = 0;
	ssize_t		bytes_sent = 0;

	while (total_sent < data.size())
	{
		bytes_sent = ::send(fd_, data.c_str() + total_sent, data.size() - total_sent, MSG_NOSIGNAL);
		if (bytes_sent == ft::err)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				continue ;
			else
				throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
		}
		total_sent += bytes_sent;
	}
}

void	IO::clear(void)
{
	data_.clear();
}

std::size_t	IO::getSize(void) const
{
	return (data_.size());
}

}//end of namespace io
