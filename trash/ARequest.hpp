#pragma once

class HttpRequestLine;
class Httpheaders;
class AResponse;

class ARequest
{
private:
	ARequest &operator=(ARequest const &rhs);
	ARequest();
protected:
	HttpRequestLine	line_;
	HttpHeaders		headers_;
	//POST need body;
public:
	ARequest(HttpRequestLine line, HttpHeaders headers);
	virtual ~ARequest();
	ARequest(ARequest const &rhs);
	HttpRequestLine	getRequestLine(void) const;
	HttpHeaders		getRequestHeaders(void) const;
	virtual AResponse *createResponse(void) const = 0;
};
