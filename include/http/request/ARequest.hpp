#pragma once
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"
#include "RequestFactory.hpp"
#include "Config.hpp"

class Response;

class ARequest
{
public:
	// enum	RequestType//?
	// {
	// 	GET,
	// 	POST,
	// 	DELETE,
	// 	PUT,
	// 	CGI,
	// 	// AUTOINDEX,
	// };
private:
	RequestLine						requestLine_;
	HttpHeader						header_;
	HttpBody						body_;
	config::Config					config_;
	config::Config::LocationConfig	configLocation_;//? delete
	std::string						localPath_;
	// RequestType						requestType_;//?

	// helper function
	config::Config::LocationConfig	setServerConfigLocation(void);
	virtual std::string				setLocalPath(void) const = 0;
	void							assertRedirection(void) const;
	void							assertAllowedMethod(void) const;
	ARequest();//=delete:
protected:
	std::string						getLocalPath(void) const;
	void							assertFileExist(std::string const &filePath) const;
public:
	explicit ARequest(RequestLine const &line, HttpHeader const &header, config::Config const &config);
	explicit ARequest(RequestLine const &line, HttpHeader const &header, HttpBody const &body, config::Config const &config);
	virtual ~ARequest();
	ARequest(ARequest const &rhs);
	ARequest &operator=(ARequest const &rhs);
	RequestLine 					getLine(void) const;
	HttpHeader 						getHeader(void) const;
	HttpBody						getBody(void) const;
	config::Config					getConfig(void) const;
	config::Config::LocationConfig	getConfigLocation(void) const;
	virtual	Response				generateResponse(void) const = 0;
};
