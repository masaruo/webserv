#pragma once
#include "ARequest.hpp"

class RequestValidator
{
private:
	RequestValidator();//=delete
	~RequestValidator();//=delete
	RequestValidator(RequestValidator const &rhs);//=delete
	RequestValidator &operator=(RequestValidator const &rhs);//=delete
public:
	static void	assertRequest(ARequest const &request);
};
