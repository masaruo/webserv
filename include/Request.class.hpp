#pragma once
#include "string.hpp"
#include <map>

class Request
{
public://typedef
	typedef enum {GET, POST, DELETE, ERROR}		method_t;
	typedef std::map<ft::string, ft::string>	field_map;

private:
	method_t	method_;
	ft::string	target_;
	ft::string	version_;
	field_map	fields_;
	//method
	void	parse_start_line(ft::string &line);
	method_t get_method(ft::string const &word) const;
	//hidden
	Request &operator=(Request const &rhs);
public:
	Request();
	Request(Request const &rhs);
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
