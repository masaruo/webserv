#include "RequestLine.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "define.hpp"
#include "string.hpp"

class RequestLineTest : public ::testing::Test
{
protected:
	void SetUp() override
	{

	}
	void TearDown() override
	{

	}
};

TEST_F(RequestLineTest, ConstructorValidInput) {
	ft::string validRequestLine = "GET /index.html HTTP/1.1";
	RequestLine requestLine(validRequestLine);
	
	EXPECT_EQ(requestLine.get_method(), ft::GET);
	EXPECT_EQ(requestLine.get_uri(), "/index.html");
	EXPECT_EQ(requestLine.get_ver(), "HTTP/1.1");
}

TEST_F(RequestLineTest, ConstructorInvalidMethod) {
	ft::string invalidMethodRequestLine = "INVALID /index.html HTTP/1.1";
	RequestLine requestLine(invalidMethodRequestLine);
	
	EXPECT_EQ(requestLine.get_method(), ft::ERROR);
	EXPECT_EQ(requestLine.get_uri(), "/index.html");
	EXPECT_EQ(requestLine.get_ver(), "HTTP/1.1");
}

TEST_F(RequestLineTest, CopyConstructor) {
	ft::string validRequestLine = "POST /submit HTTP/1.1";
	RequestLine original(validRequestLine);
	RequestLine copy(original);
	
	EXPECT_EQ(copy.get_method(), ft::POST);
	EXPECT_EQ(copy.get_uri(), "/submit");
	EXPECT_EQ(copy.get_ver(), "HTTP/1.1");
}

TEST_F(RequestLineTest, AssignmentOperator) {
	ft::string validRequestLine1 = "GET /page1 HTTP/1.1";
	ft::string validRequestLine2 = "DELETE /resource HTTP/1.1";
	RequestLine requestLine1(validRequestLine1);
	RequestLine requestLine2(validRequestLine2);
	
	requestLine1 = requestLine2;
	
	EXPECT_EQ(requestLine1.get_method(), ft::DELETE);
	EXPECT_EQ(requestLine1.get_uri(), "/resource");
	EXPECT_EQ(requestLine1.get_ver(), "HTTP/1.1");
}

// TEST_F(RequestLineTest, InvalidInputFormat) {
// 	ft::string invalidRequestLine = "GET /index.html";  // HTTPバージョンが欠けている
// 	EXPECT_THROW(RequestLine requestLine(invalidRequestLine), std::invalid_argument);
// }
