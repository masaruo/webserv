#include "RequestFactory.hpp"
#include "GetRequest.hpp"
#include "Server.hpp"

//! todo assertion such as allowed method?

RequestFactory::RequestFactory()
:buf_()
,line_()
,header_()
,body_()
,isRequestLineParsed_(false)
,isHeaderParsed_(false)
,isParseCompleted_(false)
{
	return ;
}

RequestFactory::~RequestFactory()
{
	return ;
}

RequestFactory::RequestFactory(RequestFactory const &rhs)
:buf_(rhs.buf_)
,line_(rhs.line_)
,header_(rhs.header_)
,body_(rhs.body_)
,isRequestLineParsed_(rhs.isRequestLineParsed_)
,isHeaderParsed_(rhs.isHeaderParsed_)
,isParseCompleted_(rhs.isParseCompleted_)
{
	return ;
}

RequestFactory &RequestFactory::operator=(RequestFactory const &rhs)
{
	if (this != &rhs)
	{
		buf_ = rhs.buf_;
		line_ = rhs.line_;
		header_ = rhs.header_;
		body_ = rhs.body_;
		isRequestLineParsed_ = rhs.isRequestLineParsed_;
		isHeaderParsed_ = rhs.isHeaderParsed_;
		isParseCompleted_ = rhs.isParseCompleted_;
	}
	return (*this);
}

void	RequestFactory::parse(std::string const &data, ssize_t size)
{
	buf_.append(data.c_str(), size);
	bool	recv_required = false;

	while (!isParseCompleted_ && !recv_required)
	{
		if (!isRequestLineParsed_)
			recv_required = parseRequestLine();
		else if (!isHeaderParsed_)
			recv_required = parseHeader();
		else if (!isParseCompleted_)
			recv_required = parseBody();
		else
			throw (HttpException(HttpCode::BAD_REQUEST));
	}
}

static RequestFactory::BodyType	isRequestBodyPresent(HttpHeader const &header)
{
	if (header.hasKey("content-length") && header.hasKey("transfer-encoding"))
		throw (HttpException(HttpCode::BAD_REQUEST));
	else if (header.hasKey("content-length") && ft::stonum<std::size_t>(header.getFirstValue("content-length")) > 0)
		return (RequestFactory::LENGTH);
	else if (header.hasKey("transfer-encoding") && header.getLastValue("transfer-encoding") == "chunked")
		return (RequestFactory::CHUNK);
	else
		return (RequestFactory::EMPTY);
}

bool	RequestFactory::parseRequestLine(void)
{
	std::string::size_type	pos = buf_.find("\r\n");
	if (pos == std::string::npos)
		return (true);

	line_ = RequestLine(buf_.substr(0, pos + 2));
	buf_ = buf_.substr(pos + 2);
	isRequestLineParsed_ = true;
	return (false);
}

bool	RequestFactory::parseHeader(void)
{
	std::string::size_type	posCRLFCRLF = buf_.find("\r\n\r\n");

	if (posCRLFCRLF == std::string::npos)
		return (true);

	header_ = HttpHeader(buf_.substr(0, posCRLFCRLF + 4));
	buf_ = buf_.substr(posCRLFCRLF + 4);

	if (isRequestBodyPresent(header_) == RequestFactory::EMPTY)
	{
		isHeaderParsed_ = true;
		isParseCompleted_ = true;
	}
	else
	{
		isHeaderParsed_ = true;
		isParseCompleted_ = false;
	}
	return (false);
}

bool	RequestFactory::parseBody(void)
{
	RequestFactory::BodyType	body_type = isRequestBodyPresent(header_);
	bool						recv_required = false;

	if (body_type == RequestFactory::CHUNK)
	{
		recv_required = parseBodyWithChunk();
	}
	else
	{
		std::size_t	size = ft::stonum<std::size_t>(header_.getFirstValue("content-length"));
		recv_required = parseBodyWithLength(size);
	}
	return (recv_required);
}

bool	RequestFactory::parseBodyWithLength(std::size_t size)
{
	if (buf_.size() < size)
		return (true);

	body_ = HttpBody(buf_.substr(0, size));
	buf_.clear();
	isParseCompleted_ = true;
	return (false);
}

bool	RequestFactory::parseBodyWithChunk(void)
{
	std::string::size_type	pos = buf_.find("\r\n");

	if (pos == std::string::npos)
		return (true);

	std::string const	&sizeStr = buf_.substr(0, pos);
	std::size_t			size = ft::stonum<std::size_t>(sizeStr);

	if (size == 0)
	{
		buf_ = buf_.substr(pos + 2);
		if (buf_ != "\r\n")
			throw (HttpException(HttpCode::BAD_REQUEST));
		body_ = HttpBody(buf_);
		buf_.clear();
		isParseCompleted_ = true;
		return (false);
	}
	else if (buf_.size() < pos + 2 + size + 2)
	{
		return (true);
	}

	body_ = HttpBody(buf_.substr(pos + 2, size));
	buf_ = buf_.substr(pos + 2 + size + 2);
	return (false);
}

bool	RequestFactory::isParseCompleted(void) const
{
	return (isParseCompleted_);
}

RequestLine const	&RequestFactory::getRequestLine(void) const
{
	return (line_);
}

HttpHeader const	&RequestFactory::getHeader(void) const
{
	return (header_);
}

HttpBody const		&RequestFactory::getBody(void) const
{
	return (body_);
}

Request	RequestFactory::createRequest(Server &server) const
{
	if (!isParseCompleted_)
		throw (HttpException(HttpCode::BAD_REQUEST));

	return (Request(line_, header_, body_, server));
}
