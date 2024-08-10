#include <gtest/gtest.h>
#include "RequestFactory.hpp"
#include "RequestLine.hpp"
#include "Get.hpp"
#include "define.hpp"
// #include "Post.hpp"
// #include "Delete.hpp"

class RequestFactoryTest : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(RequestFactoryTest, CreateGetRequestFromLine) {
    std::string line("GET /index.html HTTP/1.1");
    ARequest* request = RequestFactory::createRequest(line).release();
    // ASSERT_TRUE(request != NULL);
    // EXPECT_TRUE(dynamic_cast<Get*>(request) != NULL);
    EXPECT_EQ(request->getRequestLine().get_method(), ft::GET);
    EXPECT_EQ(request->getRequestLine().get_uri(), "/index.html");
    EXPECT_EQ(request->getRequestLine().get_ver(), "HTTP/1.1");
    delete request;
}

// TEST_F(RequestFactoryTest, CreatePostRequestFromLine) {
//     RequestLine line("POST /submit HTTP/1.1");
//     ARequest* request = RequestFactory::createRequest(line).release();
//     ASSERT_TRUE(request != NULL);
//     EXPECT_TRUE(dynamic_cast<HttpPost*>(request) != NULL);
//     EXPECT_EQ(request->getRequestLine().getMethod(), "POST");
//     EXPECT_EQ(request->getRequestLine().getUri(), "/submit");
//     EXPECT_EQ(request->getRequestLine().getVersion(), "HTTP/1.1");
//     delete request;
// }

// TEST_F(RequestFactoryTest, CreateDeleteRequestFromLine) {
//     RequestLine line("DELETE /resource HTTP/1.1");
//     ARequest* request = RequestFactory::createRequest(line).release();
//     ASSERT_TRUE(request != NULL);
//     EXPECT_TRUE(dynamic_cast<HttpDelete*>(request) != NULL);
//     EXPECT_EQ(request->getRequestLine().getMethod(), "DELETE");
//     EXPECT_EQ(request->getRequestLine().getUri(), "/resource");
//     EXPECT_EQ(request->getRequestLine().getVersion(), "HTTP/1.1");
//     delete request;
// }

// TEST_F(RequestFactoryTest, CreateRequestFromRawRequest) {
//     std::string raw_request = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nAccept: text/html\r\n\r\n";
//     ARequest* request = RequestFactory::createRequest(raw_request).release();
//     ASSERT_TRUE(request != NULL);
//     EXPECT_TRUE(dynamic_cast<HttpGet*>(request) != NULL);
//     EXPECT_EQ(request->getRequestLine().getMethod(), "GET");
//     EXPECT_EQ(request->getRequestLine().getUri(), "/index.html");
//     EXPECT_EQ(request->getRequestLine().getVersion(), "HTTP/1.1");
//     EXPECT_EQ(request->getRequestHeader().getFieldValue("Host"), "example.com");
//     EXPECT_EQ(request->getRequestHeader().getFieldValue("Accept"), "text/html");
//     delete request;
// }

// TEST_F(RequestFactoryTest, CreateUnsupportedRequest) {
//     RequestLine line("PUT /index.html HTTP/1.1");
//     ARequest* request = RequestFactory::createRequest(line).release();
//     EXPECT_TRUE(request == NULL);
// }

// TEST_F(RequestFactoryTest, CreateRequestFromInvalidRawRequest) {
//     std::string raw_request = "INVALID /index.html HTTP/1.1\r\nHost: example.com\r\n\r\n";
//     ARequest* request = RequestFactory::createRequest(raw_request).release();
//     EXPECT_TRUE(request == NULL);
// }
