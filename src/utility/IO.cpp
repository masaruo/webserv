#include "IO.hpp"
#include "string.hpp"
#include "GetRequest.hpp"
#include "PostRequest.hpp"
#include "DeleteRequest.hpp"
#include "PutRequest.hpp"

int const	IO::CHUNK_BODY = 1;
int const	IO::LENGTH_BODY = 2;
int const	IO::NO_BODY = 0;

IO::IO(int fd, config::ConfigFactory const &factory)
:fd_(fd)
,data_()
,rest_()
,config_factory_(factory)
,line_()
,header_()
,body_()
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
,config_factory_(rhs.config_factory_)
,line_(rhs.line_)
,header_(rhs.header_)
,body_(rhs.body_)
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
		line_ = rhs.line_;
		header_ = rhs.header_;
		body_ = rhs.body_;
	}
	return (*this);
}

static int	check_has_body_(HttpHeader &header)
{
	if (header.hasKey("content-length") && header.hasKey("transfer-encoding"))
		throw (HttpException(HttpCode::BAD_REQUEST));
	else if (header.hasKey("content-length") && ft::stonum<std::size_t>(header.getFirstValue("content-length")) > 0)
		return (IO::LENGTH_BODY);
	else if (header.hasKey("transfer-encoding") && header.getLastValue("transfer-encoding") == "chunked")
		return (IO::CHUNK_BODY);
	else
		return (IO::NO_BODY);
}

static std::size_t	parseChunkSize_(std::string const &hex_str)
{
	if (hex_str.empty() || hex_str.size() > 8)
		throw (HttpException(HttpCode::BAD_REQUEST));

	std::stringstream	ss(hex_str);
	std::size_t			size = 0;
	ss >> std::hex >> size;
	if (ss.fail() || !ss.eof())
		throw (HttpException(HttpCode::BAD_REQUEST));
	return (size);
}

bool	IO::parseHeader(ft::State &state, bool &request_complete)
{
	std::string::size_type	posCRLFCRLF = rest_.find("\r\n\r\n");

	if (posCRLFCRLF == std::string::npos)
		return (false);

	std::string const &headerline = rest_.substr(0, posCRLFCRLF + 4);
	header_ = HttpHeader(headerline);
	rest_ = rest_.substr(posCRLFCRLF + 4);

	if (check_has_body_(header_))
	{
		state = ft::RECV_BODY;
		return (true);
	}
	else
	{
		state = ft::IDLE;
		request_complete = true;
		return (false);
	}
}

bool	IO::parseRequestLine(ft::State &state)
{
	std::string::size_type	posCRLF = rest_.find("\r\n");
	if (posCRLF == std::string::npos)
		return (false);

	std::string const &requestline = rest_.substr(0, posCRLF + 2);
	line_ = RequestLine(requestline);
	rest_ = rest_.substr(posCRLF + 2);
	state = ft::RECV_HEADER;

	if (rest_.empty())
		return (false);
	else
		return (true);
}

bool	IO::parseBodyWithLength(ft::State &state, std::size_t size)
{
	if (rest_.size() > size)
		throw (HttpException(HttpCode::BAD_REQUEST));
	else if (rest_.size() == size)
	{
		body_ = HttpBody(rest_);
		rest_.clear();
		state = ft::IDLE;
		// return (false);
	}
	// else
		// return (true);
	return (false);
}

bool	IO::parseBodyWithChunk(ft::State &state)
{
 	std::string::size_type	pos = rest_.find("\r\n");
	if (pos == std::string::npos)
	{
		return (false);
	}

	std::string const	&sizeStr = rest_.substr(0, pos + 2);
	std::size_t			size = parseChunkSize_(sizeStr);
	if (size == 0)
	{
		rest_ = rest_.substr(pos + 2);
		if (rest_ != "\r\n")
			throw (HttpException(HttpCode::BAD_REQUEST));
		body_ = HttpBody(data_);
		data_.clear();
		rest_.clear();
		state = ft::IDLE;
		return (false);
	}
	else if (rest_.size() < pos + 2 + size + 2)
	{
		return (false);
	}

	data_.append(rest_.substr(pos + 2, size));
	rest_ = rest_.substr(pos + 2 + size + 2);
	return (false);
}

bool	IO::parseBody(ft::State &state, bool &request_complete)
{
	int const	body_type = check_has_body_(header_);
	bool		continue_parse;

	if (body_type == CHUNK_BODY)
	{
		continue_parse = parseBodyWithChunk(state);
	}
	else
	{
		std::size_t	size = ft::stonum<std::size_t>(header_.getFirstValue("content-length"));
		continue_parse = parseBodyWithLength(state, size);
	}
	if (!continue_parse && state == ft::IDLE)
	{
		request_complete = true;
	}
	return (continue_parse);
}

bool	IO::parseBuffer(ft::State &state)
{
	bool	parse_continue = true;
	bool	request_completed = false;

	while (parse_continue && !rest_.empty())
	{
		switch (state)
		{
			case (ft::RECV_REQUESTLINE):
				parse_continue = parseRequestLine(state);
				break ;
			case (ft::RECV_HEADER):
				parse_continue = parseHeader(state, request_completed);
				break ;
			case (ft::RECV_BODY):
				parse_continue = parseBody(state, request_completed);
				break ;
			case (ft::CGIRECV):
				parse_continue = false;
				request_completed = false;
			default:
				break ;
		}
	}
	return (request_completed);
}

bool	IO::recv(ft::State &state)
{
	char	tmp[ft::READ_BUF_SIZE];
	ssize_t	bytes = ::recv(fd_, tmp, sizeof(tmp), 0);
	bool	is_request_ready = false;

	if (bytes == -1)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	else if (bytes == 0)
	{
		// rest_.append(tmp, bytes);
		// data_.append(rest_);
		// rest_.clear();
		// state = ft::CGIEND;
		return (true);
	}
	else
	{
		rest_.append(tmp, bytes);
		is_request_ready = parseBuffer(state);
	}
	return (is_request_ready);
}

bool	IO::send(ft::State &state)
{
	std::size_t	sendSize = data_.size();
	if (data_.size() > ft::WRITE_BUF_SIZE)
		sendSize = ft::WRITE_BUF_SIZE;

	std::cerr << "IO::SEND. sendsize= " << sendSize << std::endl;

	ssize_t	bytes = ::send(fd_, &data_[0], sendSize, 0);

	std::cerr << "IO::SEND. sentsize= " << bytes << std::endl;

	data_ = data_.substr(bytes);
	if (data_.empty())
	{
		std::cerr << "IO::send completed" << std::endl;
		return (true);
	}
	return (false);
}

void	IO::setData(std::string const &data)
{
	data_.clear();
	rest_.clear();
	data_ = data;
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

ARequest	*IO::createRequest(Server &server)
{
	std::string const		&method = line_.getMethod();
	std::string const		&host = header_.getFirstValue("host");
	config::Config const	&config = config_factory_.getConfig(host);

	HttpException::loadErrorPageMap(config);
	HttpUri	&uri = line_.getUriReference();
	uri.updateWithHostHeader(host);

	if (method == "GET")
		return (new GetRequest(line_, header_, config, server));
	else if (method == "POST")
		return (new PostRequest(line_, header_, body_, config, server));
	else if (method == "DELETE")
		return (new DeleteRequest(line_, header_, config, server));
	else if (method == "PUT")
		return (new PutRequest(line_, header_, body_, config, server));
	else
		throw (HttpException(HttpCode::METHOD_NOT_ALLOWED));
}
