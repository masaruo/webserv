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

void	io::IO::recv_internal(std::size_t readSize  = std::numeric_limits<std::size_t>::max())
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
		ssize_t bytes = ::recv(fd_, (void*)buf.data(), buf_size_, 0);
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

// std::size_t	io::IO::getChunkSize(void)
// {
// 	std::string	buf;
// 	std::size_t	chunk_size = 0;

// 	buf.resize(buf_size_);
// 	ssize_t	bytes = ::recv(fd_, (void*)buf.data(), buf_size_, 0);
// 	if (bytes <= 0)
// 		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

// 	std::string::size_type	posCRLF = buf.find("\r\n");
// 	if (posCRLF == std::string::npos)
// 		throw (HttpException(HttpCode::BAD_REQUEST));
// 	buf.resize(bytes);
// 	std::string	chunkline = buf.substr(0, posCRLF);
// 	keep_ = buf.substr(posCRLF + 2);

// 	ft::string					ftChunk(chunkline);
// 	ft::string::string_vector	splt = ftChunk.split(ft::string::WS + ";=");
// 	if (splt.empty() || splt[0].empty())
// 		throw (HttpException(HttpCode::BAD_REQUEST));
// 	try
// 	{
// 		char		hexChar = ft::decodeHex(splt[0]);
// 		std::string	hexStr(hexChar, 1);
// 		chunk_size = ft::stonum<std::size_t>(hexStr);
// 	}
// 	catch(std::invalid_argument const &e)
// 	{
// 		throw (HttpException(HttpCode::BAD_REQUEST));
// 	}
// 	chunk_size -= keep_.size();
// 	return (chunk_size);
// }

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

// std::size_t	io::IO::parseChunkSize(void)
// {
// 	std::string 				buf;
// 	ft::string::string_vector	splitted;
// 	std::string::size_type		posCRLF;
// 	std::size_t					bytes = 0;
// 	std::size_t					chunk_size = 0;

// 	while (true)
// 	{
// 		buf.resize(buf_size_);
// 		buf = recv(buf_size_);

// 		keep_.append(buf);
// 		posCRLF = keep_.find("/r/n");
// 		if (posCRLF != std::string::npos)
// 			break ;
// 	}
// 	std::string const	chunkSizeLine = keep_.substr(0, posCRLF + 2);
// 	std::string const	rest = keep_.substr(posCRLF + 2);

// 	chunk_size = getChunkSize(chunkSizeLine);

// 	if (rest.size() > chunk_size)



// 	chunk_size -= keep_.size();
// 	return (chunk_size);

	// if (!keep_.empty())
	// {
	// 	buf = recv(buf_size_ - keep_.size());
	// }

	// if (!keep_.empty())
	// {
	// 	bytes = keep_.size();
	// 	buf.resize(bytes);
	// 	buf = keep_;
	// }
	// else
	// {
	// 	buf.resize(buf_size_);
	// 	bytes = ::recv(fd_, (void*) buf.data(), buf_size_, 0);
	// }

	// std::string::size_type	posCRLF = keep_.find("/r/n");
	// if (posCRLF == std::string::npos)
	// 	//todo continue


	// std::string const	firstLine = buf.substr()
	// 	buf = keep_.substr(0, posCRLF + 2);
	// 	std::string afterCRLF = keep_.substr(posCRLF + 2);
// }

std::string	io::IO::parseChunkContent(std::size_t size, std::string const &line)
{
	ft::string	ftline(line);

	
}

bool	io::IO::parseChunkLine(std::string const &line)
{
	ft::string const				ftline(line);
	ft::string::string_vector const	split_by_lf = ftline.split(ft::string::LF);
	ft::string::string_vector_const_iterator	iter = split_by_lf.begin();
	ft::string::string_vector_const_iterator	next = split_by_lf.begin() + 1;
	ft::string::string_vector_const_iterator	end = split_by_lf.end();

	if (split_by_lf.empty() || split_by_lf[0].empty())
		throw (HttpException(HttpCode::BAD_REQUEST));

	while (next != end)
	{
		std::size_t	size = getChunkSize(iter->str());

		iter++; next++;
	}

}

std::string	io::IO::recv(std::string const &transfer_ecoding_value)
{
	if (transfer_ecoding_value != "chunked")
		return (recv());

	std::string	buf;
	buf.resize(buf_size_);

	while (true)
	{
		buf = recv();

	}
}

std::string	io::IO::recv(void)
{
	recv_internal();
	return (data_);
}

std::string	io::IO::recv(std::size_t readSize)
{
	recv_internal(readSize);
	return (data_);
}

void	io::IO::clear(void)
{
	data_.clear();
	keep_.clear();
}

std::size_t	io::IO::getSize(void) const
{
	return (data_.size());
}
