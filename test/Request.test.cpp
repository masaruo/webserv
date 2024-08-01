#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Request.class.hpp"
#include "string.hpp"

TEST(RequestLineTest, ConstructorWithValidWhitespacesInBetween)
{
	ft::string	valid = "GET 	\r \t \v \f /index.html  	\r \t \v \f  HTTP/1.1 \r\n";
	RequestLine	req(valid);

	EXPECT_THAT(req.getMethod(), RequestLine::GET);
}

TEST(RequestLineTest, ConstructorWithValidWhiteSpacesBeforeAndAfter)
{
	ft::string	valid = "  	\r \t \v \f GET 	\r \t \v \f /index.html  	\r \t \v \f  HTTP/1.1 	\r \t \v \f \r\n";
	RequestLine	req(valid);

	EXPECT_THAT(req.getMethod(), RequestLine::GET);
}

TEST(RequestLineTest, ConstructorWithInvalidValidWhiteSpacesBeforeAndAfter)
{
	ft::string	invalid = "  abc	\r \t \v \f GET 	\r \t \v \f /index.html  	\r \t \v \f  HTTP/1.1 	\r \t \v \f \r\n";
	RequestLine	req(invalid);

	EXPECT_THAT(req.getMethod(), RequestLine::ERROR);
}

TEST(RequestLineTest, ConstructorWithArgsNotEndWithCRLF)
{
	ft::string	invalid = "  abc	\r \t \v \f GET 	\r \t \v \f /index.html  	\r \t \v \f  HTTP/1.1 	\r \t \v \f ";

	EXPECT_THROW({RequestLine rq(invalid);}, std::runtime_error);
}
