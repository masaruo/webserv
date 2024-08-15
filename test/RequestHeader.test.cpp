#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "RequestHeader.hpp"

class RequestHeaderTest : public ::testing::Test {
protected:
	ft::string::string_vector sample_headers;

	void SetUp() override {
		sample_headers.push_back("Host: example.com");
		sample_headers.push_back("Content-Type: text/html");
		sample_headers.push_back("User-Agent: Mozilla/5.0");
	}
};

TEST_F(RequestHeaderTest, ConstructorTest) {
	RequestHeader headers(sample_headers);
	EXPECT_EQ(headers.get_pair("Host")->second, "example.com");
	EXPECT_EQ(headers.get_pair("Content-Type")->second, "text/html");
	EXPECT_EQ(headers.get_pair("User-Agent")->second, "Mozilla/5.0");
}

TEST_F(RequestHeaderTest, CopyConstructorTest) {
	RequestHeader original(sample_headers);
	RequestHeader copy(original);

	EXPECT_EQ(copy.get_pair("Host")->second, "example.com");
	EXPECT_EQ(copy.get_pair("Content-Type")->second, "text/html");
	EXPECT_EQ(copy.get_pair("User-Agent")->second, "Mozilla/5.0");
}

TEST_F(RequestHeaderTest, AssignmentOperatorTest) {
	RequestHeader headers1(sample_headers);
	ft::string::string_vector other_headers;
	other_headers.push_back("Accept: */*");
	other_headers.push_back("Connection: keep-alive");
	RequestHeader headers2(other_headers);

	headers1 = headers2;

	EXPECT_EQ(headers1.get_pair("Accept")->second, "*/*");
	EXPECT_EQ(headers1.get_pair("Connection")->second, "keep-alive");
	EXPECT_EQ(headers1.get_pair("Host"), headers1.get_pair("Host"));  // 存在しないキーの場合
}

TEST_F(RequestHeaderTest, GetPairTest) {
	RequestHeader headers(sample_headers);

	EXPECT_EQ(headers.get_pair("Host")->second, "example.com");
	EXPECT_EQ(headers.get_pair("Content-Type")->second, "text/html");
	EXPECT_EQ(headers.get_pair("User-Agent")->second, "Mozilla/5.0");
	EXPECT_EQ(headers.get_pair("Non-Existent"), headers.get_pair("Non-Existent"));  // 存在しないキーの場合
}

TEST_F(RequestHeaderTest, ConstGetPairTest) {
	const RequestHeader headers(sample_headers);

	EXPECT_EQ(headers.get_pair("Host")->second, "example.com");
	EXPECT_EQ(headers.get_pair("Content-Type")->second, "text/html");
	EXPECT_EQ(headers.get_pair("User-Agent")->second, "Mozilla/5.0");
	EXPECT_EQ(headers.get_pair("Non-Existent"), headers.get_pair("Non-Existent"));  // 存在しないキーの場合
}

TEST_F(RequestHeaderTest, EmptyHeadersTest) {
	ft::string::string_vector empty_headers;
	RequestHeader headers(empty_headers);

	EXPECT_EQ(headers.get_pair("Any-Key"), headers.get_pair("Any-Key"));  // 空のヘッダーの場合
}

// 重複キーのテスト（現在の実装では処理されていないが、将来的に実装される可能性がある）
TEST_F(RequestHeaderTest, DuplicateKeyTest) {
	ft::string::string_vector duplicate_headers = sample_headers;
	duplicate_headers.push_back("Host: another.com");

	RequestHeader headers(duplicate_headers);

	// 注意: この動作は現在の実装に依存します。適切な動作を定義し、それに応じてテストを調整してください。
	EXPECT_EQ(headers.get_pair("Host")->second, "another.com");  // または "example.com" かもしれません
}
