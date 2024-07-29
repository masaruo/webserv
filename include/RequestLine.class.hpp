#pragma once
#include "string.hpp"

// @brief HttpRequestの一行目の分析を行うclass
class RequestLine
{
public://typedef
typedef enum {GET, POST, DELETE, ERROR}	method_t;

private:
	method_t	method_;
	ft::string	target_;
	ft::string	version_;
	//method
	void	parse_line(ft::string const &line);
	method_t get_method(ft::string const &word) const;
	//hidden
	RequestLine();
	RequestLine &operator=(RequestLine const &rhs);
public:
	RequestLine(ft::string	const &line);
	RequestLine(RequestLine const &rhs);
	// @brief methodの種類をリターンする
	// @return method_tの数値、エラーの場合にはERRORをリターン
	method_t	getMethod(void) const;

	//todo ERROR
	// 501 (not implemented)
	// 414 (uri too long)
};

/*
* RFC9110(HTTPSemantics)
* RFC9111(HTTP Caching)
* RFC9112(HTTP/1.1)
	https://www.rfc-editor.org/rfc/rfc9112.html
/

HTTP-message   = start-line CRLF
                   *( field-line CRLF )
                   CRLF
                   [ message-body ]

start-line     = request-line / status-line
request-line   = method SP request-target SP HTTP-version
method         = token





*/
