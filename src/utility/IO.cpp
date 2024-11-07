#include "IO.hpp"
#include "string.hpp"

IO::IO(int fd)
:fd_(fd)
,data_()
,rest_()
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
,rest_(rhs.rest_)
{
	return ;
}

IO &IO::operator=(IO const &rhs)
{
	if (this != &rhs)
	{
		fd_ = rhs.fd_;
		data_ = rhs.data_;
		rest_ = rhs.rest_;
	}
	return (*this);
}

static bool	is_chunk_body_(HttpHeader &header)
{
	if (header.hasKey("content-length") && header.hasKey("transfer-endocing"))
		throw (HttpException(HttpCode::BAD_REQUEST));
	else if (header.hasKey("content-length") && ft::stonum<std::size_t>(header.getFirstValue("content-length")) > 0)
		return (false);
	else if (header.hasKey("transfer-endocing") && header.getLastValue("transfer_encoding") == "chunked")
		return (true);
	else
		throw (HttpException(HttpCode::BAD_REQUEST));
}

static std::size_t	getChunkSize(std::string const &line)
{
	ft::string const				&ftline(line);
	ft::string::string_vector const &split = ftline.split(ft::string::WS + ";=");
	std::size_t						chunk_size = 0;

	if (split.empty() || split[0].empty())
		throw (HttpException(HttpCode::BAD_REQUEST));

	std::stringstream	ss;
	ss << std::hex << split[0].str();
	ss >> chunk_size;
	if (ss.fail())
		throw (HttpException(HttpCode::BAD_REQUEST));
	return (chunk_size);
}

ssize_t	IO::recv_chunk(void)
{
	// ssize_t	bytes = 0;
	// ssize_t	sizeToRead = 0;
	// std::string	peekSizeStr = "";
	// std::string	contentStr = "";
	// std::string::size_type	posCRLF = 0;

	// peekSizeStr.resize(ft::READ_BUF_SIZE);
	// bytes = ::recv(fd_, &peekSizeStr[0], peekSizeStr.size(), MSG_PEEK | MSG_DONTWAIT);
	// if (bytes == ft::err)
	// 	throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

	// peekSizeStr.resize(bytes);
	// posCRLF = peekSizeStr.find("\r\n");
	// if (posCRLF == std::string::npos)//! /r/n not in buf size => error
	// {

	// }

	// peekSizeStr.resize(posCRLF + 2);
	// bytes = ::recv(fd_, &peekSizeStr[0], posCRLF + 2, MSG_DONTWAIT);
	// if (bytes == ft::err)
	// 	throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

	// sizeToRead = getChunkSize(peekSizeStr);

	// if (data_.size() + sizeToRead > max_data_size_)
	// 	throw (HttpException(HttpCode::BAD_REQUEST));

	// contentStr.resize(sizeToRead + 2);
	// bytes = ::recv(fd_, &contentStr[0], sizeToRead + 2, MSG_DONTWAIT);
	// if (bytes == ft::err)
	// 	throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	// else if (bytes != sizeToRead + 2)
	// 	throw (HttpException(HttpCode::BAD_REQUEST));

	// contentStr.resize(bytes);

	// if (sizeToRead == 0)
	// {
	// 	if (contentStr != "\r\n")
	// 		throw (HttpException(HttpCode::BAD_REQUEST));
	// 	buf = contentStr;
	// 	return (0);
	// }

	// ft::string	ftContent(contentStr);
	// if (!ftContent.end_with_str("\r\n"))
	// 	throw (HttpException(HttpCode::BAD_REQUEST));

	// ftContent.trim(ft::string::CRLF);
	// buf = ftContent;
	// return (bytes);
}

ssize_t	IO::recv_length(std::size_t len)
{
	ssize_t		bytes = 0;
	std::string	buf(ft::READ_BUF_SIZE, '\0');
	std::size_t	readSize = 0;

	data_ = rest_;
	rest_.clear();

	if (data_.size() == len)
	{
		data_.resize(len);
		return (0);
	}
	else if (data_.size() > len)
	{
		throw (HttpException(HttpCode::BAD_REQUEST));
	}

	readSize = len - data_.size();
	if (readSize > ft::READ_BUF_SIZE)
	{
		buf.resize(ft::READ_BUF_SIZE);
		bytes = ::recv(fd_, &buf[0], buf.size(), MSG_DONTWAIT);
		if (bytes == -1)
			throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
		else if (bytes != readSize)
			throw (HttpException(HttpCode::BAD_REQUEST));
		else
		{
			rest_.append(buf);
			return (bytes);
		}
	}
	else
	{
		buf.resize(readSize);
		bytes = ::recv(fd_, &buf[0], buf.size(), MSG_DONTWAIT);
		if (bytes == -1)
			throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
		else if (bytes != 0 && bytes != readSize)
			throw (HttpException(HttpCode::BAD_REQUEST));
		else
		{
			data_.append(buf);
			return (0);
		}
	}
}

ssize_t	IO::recv_until(std::string const &until)
{
	ssize_t		bytes = 0;
	std::string	tmp(ft::READ_BUF_SIZE, '\0');

	data_.append(rest_);
	rest_.clear();

	bytes = ::recv(fd_, &tmp[0], tmp.size(), MSG_DONTWAIT);
	if (bytes == -1)
		return (-1);
	tmp.resize(bytes);
	std::string::size_type	posUntil = tmp.find(until);
	if (posUntil == std::string::npos)
	{
		rest_.append(tmp);
		return (bytes);
	}
	else
	{
		data_.append(tmp.substr(0, posUntil + until.size()));
		rest_.append(tmp.substr(posUntil + until.size()));
		return (0);
	}
}

void	IO::parseHeader(ft::State &state)
{
	ssize_t	bytes = recv_until("\r\n\r\n");
	if (bytes == -1)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	else if (bytes > 0)
		return ;

	header_ = HttpHeader(getData());
	clear();
	state = ft::RECV_BODY;
	return ;
}

void	IO::parseRequestLine(ft::State &state)
{
	ssize_t bytes = recv_until("\r\n");
	if (bytes == -1)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	else if (bytes > 0)
		return ;

	line_ = RequestLine(getData());
	clear();
	state = ft::RECV_HEADER;
	return ;
}

bool	IO::parseBody(ft::State &state)
{
	bool const	is_chunk = is_chunk_body_(header_);
	ssize_t		bytes = 0;

	if (is_chunk)
	{
		bytes = recv_chunk();
	}
	else
	{
		std::size_t	size = ft::stonum<std::size_t>(header_.getFirstValue("content-length"));
		bytes = recv_length(size);
	}

	if (bytes == 0)
	{
		body_ = HttpBody(data_);
		data_.clear();
		return (false);
	}
	else
		return (true);
}

void	IO::parseBuffer(ft::State &state)
{
	bool	parse_continue = true;

	while (parse_continue && !rest_.empty())
	{
		switch (state)
		{
			case (ft::RECV_REQUESTLINE):
				parseRequestLine(state);
				break ;
			case (ft::RECV_HEADER):
				parseHeader(state);
				break ;
			case (ft::RECV_BODY):
				parse_continue = parseBody(state);
				break ;
			default:
				break ;
		}
	}
}

ssize_t	IO::recv(ft::State &state)
{
	char	tmp[ft::READ_BUF_SIZE];
	ssize_t	bytes = ::recv(fd_, tmp, sizeof(tmp), 0);
	if (bytes > 0)
	{
		rest_.append(tmp, bytes);
		parseBuffer(state);
	}
	return (bytes);
}

std::string	IO::getData(void) const
{
	return (data_);
}

std::size_t	IO::getSize(void) const
{
	return (data_.size());
}

void	IO::clear(void)
{
	data_.clear();
}
