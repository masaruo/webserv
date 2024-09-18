#pragma once
#include "unique_ptr.hpp"
#include <string>
#include <stdexcept>

class ARequest;

class RequestFactory
{
private:
	RequestFactory();
	RequestFactory(RequestFactory const &rhs);
	RequestFactory &operator=(RequestFactory const &rhs);
	~RequestFactory();
public:
	static	ARequest	*createRequest(int fd);
	// class RequestFactoryException : public std::runtime_error
	// {
	// public:
	// 	RequestFactoryException(std::string const &msg);
	// };
};
