#pragma once
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"

class ARequest;

class RequestFactory
{
public:
	enum BodyType
	{
		CHUNK,
		LENGTH,
		EMPTY
	};
private:
	std::string	buf_;
	RequestLine	line_;
	HttpHeader	header_;
	HttpBody	body_;
	bool		isRequestLineParsed_;
	bool		isHeaderParsed_;
	bool		isParseCompleted_;

	bool		parseRequestLine(void);
	bool		parseHeader(void);
	bool		parseBody(void);
	bool		parseBodyWithLength(std::size_t size);
	bool		parseBodyWithChunk(void);
public:
	RequestFactory();
	~RequestFactory();
	RequestFactory(RequestFactory const &rhs);
	RequestFactory &operator=(RequestFactory const &rhs);
	void		parse(std::string const &data, ssize_t size);
	bool		isParseCompleted(void) const;
	// ARequest	*createRequest(Server &server) const;
};
