#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "RequestLine.class.hpp"
#include "string.hpp"

TEST(RequestLineTest, ConstructorWithValidGetRequest)
{
	ft::string	valid = "GET /index.html HTTP/1.1";
	RequestLine	req(valid);

	EXPECT_THAT(req.getMethod(), RequestLine::GET);
}
