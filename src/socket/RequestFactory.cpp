#include "RequestFactory.hpp"
#include "GetRequest.hpp"
#include "Server.hpp"

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
	buf_.append(data, size);

	if (!isRequestLineParsed_)
		parseRequestLine();
	else if (!isHeaderParsed_)
		parseHeader();
	else if (!isParseCompleted_)
		parseBody();
	else
		throw (HttpException(HttpCode::BAD_REQUEST));
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

void	RequestFactory::parseRequestLine(void)
{
	std::string::size_type	pos = buf_.find("\r\n");
	if (pos == std::string::npos)
		return ;

	line_ = RequestLine(buf_.substr(0, pos + 2));
	buf_ = buf_.substr(pos + 2);
	isRequestLineParsed_ = true;
}

void	RequestFactory::parseHeader(void)
{
	std::string::size_type	posCRLFCRLF = buf_.find("\r\n\r\n");

	if (posCRLFCRLF == std::string::npos)
		return ;

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
}

void	RequestFactory::parseBody(void)
{
	RequestFactory::BodyType	body_type = isRequestBodyPresent(header_);

	if (body_type == RequestFactory::CHUNK)
	{
		parseBodyWithChunk();
	}
	else
	{
		std::size_t	size = ft::stonum<std::size_t>(header_.getFirstValue("content-length"));
		parseBodyWithLength(size);
	}
}

void	RequestFactory::parseBodyWithLength(std::size_t size)
{
	if (buf_.size() < size)
		return ;

	body_ = HttpBody(buf_.substr(0, size));
	buf_.clear();
	isParseCompleted_ = true;
}

void	RequestFactory::parseBodyWithChunk(void)
{
	std::string::size_type	pos = buf_.find("\r\n");

	if (pos == std::string::npos)
		return ;

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
	}
	else if (buf_.size() < pos + 2 + size + 2)
	{
		return ;
	}

	body_ = HttpBody(buf_.substr(pos + 2, size));
	buf_ = buf_.substr(pos + 2 + size + 2);
}

bool	RequestFactory::isParseCompleted(void) const
{
	return (isParseCompleted_);
}

// ARequest	*RequestFactory::createRequest(Server &server)
// {
// 	if (!isParseCompleted_)
// 		throw (HttpException(HttpCode::BAD_REQUEST));

// 	ARequest				*request;
// 	config::Config const	&config = server.getConfigFactory().getConfig(line_.getUri().getHost());
// 	if (line_.getMethod() == "GET")
// 		request = new GetRequest(line_, header_, body_, config, server);
// 	return (request);
// }
