#pragma once
// #include "string.hpp"

class Request
{
public://typedef
	// typedef enum {GET, POST, DELETE, ERR} method_t;
	// typedef struct
	// {
	// 	method_t	method_;
	// 	ft::string	target_;
	// 	ft::string	version_;
	// }	request_line_t;

private:
//attribute
	// ft::string				buf_;
	// request_line_t const	request_line_;
//method

//hidden
Request();
Request &operator=(Request const &rhs);

public:
Request(int fd);
~Request();
Request(Request const &rhs);

//todo ERRORs
};

//todo 
// 一行ずつ読み込む
// 最初の行にメソッド、ターゲット、HTTPバージョン
