#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ARequest.hpp"

class ARequestTest : public ::testing::Test {
protected:
    ft::string::string_vector startline;

    virtual void SetUp() {
        startline.push_back("GET");
        startline.push_back("/index.html");
        startline.push_back("HTTP/1.1");
    }
};

TEST_F(ARequestTest, LineAttributeTest) {
    ARequest request(startline);

    // line_属性はprotectedなので、直接アクセスできません
    // テスト用のpublicメソッドを追加するか、フレンドクラスを使用する必要があります
    // ここでは、テスト用のpublicメソッドを追加したと仮定します

    EXPECT_THAT(request.getMethod(), "GET");
    EXPECT_THAT(request.getTarget(), "/index.html");
    EXPECT_THAT(request.getVersion(), "HTTP/1.1");
}

TEST_F(ARequestTest, FieldsAttributeTest) {
    ARequest request(startline);

    ft::string::string_vector fields;
    fields.push_back("Host: example.com");
    fields.push_back("User-Agent: Mozilla/5.0");

    request.parseFields(fields);

    // fields_属性もprotectedなので、直接アクセスできません
    // テスト用のpublicメソッドを追加したと仮定します

    EXPECT_THAT(request.getField("Host"), "example.com");
    EXPECT_THAT(request.getField("User-Agent"), "Mozilla/5.0");
}

TEST_F(ARequestTest, FieldsAttributeTestOfBrokenFields) {
    ARequest request(startline);

    ft::string::string_vector fields;
    fields.push_back("Host: example");
    fields.push_back(".com");

    request.parseFields(fields);

    // fields_属性もprotectedなので、直接アクセスできません
    // テスト用のpublicメソッドを追加したと仮定します

    EXPECT_THAT(request.getField("Host"), "example.com");
}
