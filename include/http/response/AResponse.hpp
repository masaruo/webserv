#pragma once
#include <string>
#include <map>
#include "define.hpp"
#include "HttpHeader.hpp"
#include "StatusCode.hpp"
#include "ARequest.hpp"
#include "HttpBody.hpp"
// #include "Binary.hpp"

class AResponse
{
private:
	std::string	uri_;
	HttpHeader	request_header_;
	StatusCode	code_;
	HttpHeader	response_header_;
	HttpBody	body_;

	AResponse(); ///< デフォルトコンストラクタ（private）

protected:
	void		setCode(StatusCode const &code);
	void		setHeader(HttpHeader const &inHeader);
	void		setBody(HttpBody const &body);
	std::string	getUri(void) const;

public:
	AResponse(std::string const &uri, HttpHeader const &req_header);
	virtual ~AResponse();
	AResponse(AResponse const &rhs);
	AResponse &operator=(AResponse const &rhs);
	StatusCode getCode(void) const;
	HttpHeader getHeader(void) const;
	HttpBody getBody(void) const;
	Binary::vec_bytes	getResponse(void) const;
	virtual void generateResponse(void) = 0;
};
