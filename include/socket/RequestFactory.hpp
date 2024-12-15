#pragma once
#include "RequestLine.hpp"
#include "RequestHeader.hpp"
#include "HttpBody.hpp"
#include "Server.hpp"

class ARequest;
class Server;

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
	std::string		buf_;
	RequestLine		line_;
	RequestHeader	header_;
	HttpBody		body_;
	Server			&server_;
	bool			isRequestLineParsed_;
	bool			isHeaderParsed_;
	bool			isParseCompleted_;
	bool			isCgiRequest_;
	std::size_t		max_body_size_;

	void		checkIsCgiRequest(void);
	bool		parseRequestLine(void);
	bool		parseHeader(void);
	bool		parseBody(void);
	bool		parseBodyWithLength(std::size_t size);
	bool		parseBodyWithChunk(void);
	void		configRelatedInitialization(void);
	RequestFactory();//=delete
public:
	explicit	RequestFactory(Server &server);
	~RequestFactory();
	RequestFactory(RequestFactory const &rhs);
	RequestFactory &operator=(RequestFactory const &rhs);
	void				parse(std::string const &data, ssize_t size);
	bool				isParseCompleted(void) const;
	bool				isCgiRequest(void) const;
	RequestLine const	&getRequestLine(void) const;
	RequestHeader const	&getHeader(void) const;
	HttpBody const		&getBody(void) const;
	ARequest			*createRequest(Server &server) const;
};
