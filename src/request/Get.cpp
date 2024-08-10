#include "Get.hpp"

Get::Get()
{
	return ;
}

Get::Get(std::string const &raw_request)
:ARequest(raw_request)
{
	return ;
}

Get::~Get()
{
	return ;
}

Get::Get(Get const &rhs)
:ARequest(rhs)
{

}

Get &Get::operator=(Get const &rhs)
{
	if (this != &rhs)
	{
		*this = rhs;
	}
	return (*this);
}
