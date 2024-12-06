#pragma once
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"
#include "RequestFactory.hpp"
#include "Config.hpp"

class Response;
class Server;

class ARequest
{
public:
	struct	ResponseData
	{
		HttpStatus	status_;
		HttpHeader	header_;
		HttpBody	body_;
		bool		has_body_;
		ResponseData():has_body_(false){};
	};
	struct Request
	{
		RequestLine	line_;
		HttpHeader	header_;
		HttpBody	body_;
	};
private:
	RequestLine						requestLine_;
	HttpHeader						header_;
	HttpBody						body_;
	config::Config					config_;
	ResponseData					response_;
	Server							&server_;
	mutable bool					is_initialized_;

	// helper function
	config::Config::LocationConfig	setServerConfigLocation(void);
	virtual std::string				setLocalPath(void) const = 0;//! pure virtual
	void							assertRedirection(void) const;
	void							assertAllowedMethod(void) const;
	ARequest();//=delete:
protected:
	void							assertFileExist(std::string const &filePath) const;
	//response structure setter / getter
	void							setResponseStatus(HttpStatus const &response_status);
	void							setResponseHeader(HttpHeader const &response_header);
	void							setResponseBody(HttpBody const &response_body);
	void							setResponseHasBody(bool hasBody);
	Server							&getServerReference(void);
public:
	// explicit ARequest(Request const &request, Server &server);
	explicit ARequest(RequestLine const &line, HttpHeader const &header, config::Config const &config, Server &server);
	explicit ARequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config, Server &server);
	virtual ~ARequest();
	ARequest(ARequest const &rhs);
	ARequest &operator=(ARequest const &rhs);

	void							init(void) const;
	RequestLine 					getLine(void) const;
	HttpHeader 						getHeader(void) const;
	HttpBody						getBody(void) const;
	config::Config					getConfig(void) const;

	config::Config::LocationConfig	getConfigLocation(void) const;//? delete

	//getter for response
	HttpStatus						getResponseStatus(void) const;
	HttpHeader						getResponseHeader(void) const;
	HttpBody						getResponseBody(void) const;
	bool							getResponseHasBody(void) const;

	virtual void					generateResponseData(void) = 0;//! pure virtual
	Response						generateResponse(void) const;
};
