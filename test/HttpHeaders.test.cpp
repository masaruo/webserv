#include "HttpHeaders.hpp"
#include "../include/utility/string.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(HttpHeadersTest, AddHeader)
{
	HttpHeaders	headers;
	headers.addHeader(ft::string("Content-Type"), ft::string("text/plain"));
	EXPECT_THAT(headers.getHeader(ft::string("Content-Type")), ft::string("text/plain"));
}
