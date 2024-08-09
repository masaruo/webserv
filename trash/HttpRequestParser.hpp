#pragma once
#include "string.hpp"

class HttpRequestLine;
class HttpHeaders;
class ARequest;

class HttpRequestParser
{
private:
	HttpRequestParser(){};
	~HttpRequestParser(){};
	HttpRequestParser(HttpRequestParser const &rhs);
	HttpRequestParser &operator=(HttpRequestParser const &rhs);
public:
	HttpRequestLine	parseRequestLine(ft::string const &line);
	HttpHeaders		parseHeaders(ft::string::string_vector const &lines);
};
