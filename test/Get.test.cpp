#include <gtest/gtest.h>
#include "Get.hpp"

class GetTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		// セットアップコード（必要な場合）
	}

	virtual void TearDown() {
		// クリーンアップコード（必要な場合）
	}
};

TEST_F(GetTest, DefaultConstructor) {
	Get request;
	// デフォルトコンストラクタのテスト
	// 例: EXPECT_EQ(request.getLine().getMethod(), "GET");
}

TEST_F(GetTest, ConstructorWithRawRequest) {
	std::string raw_request = "GET /index.html HTTP/1.1\r\nHost: example.com\r\n\r\n";
	Get request(raw_request);
	// raw_requestで初期化されたGETリクエストのテスト
	// 例: EXPECT_EQ(request.getLine().getMethod(), "GET");
	// EXPECT_EQ(request.getLine().getPath(), "/index.html");
	// EXPECT_EQ(request.getHeader().getHost(), "example.com");
}

TEST_F(GetTest, CopyConstructor) {
	std::string raw_request = "GET /index.html HTTP/1.1\r\nHost: example.com\r\n\r\n";
	Get original(raw_request);
	Get copy(original);
	// コピーコンストラクタのテスト
	// 例: EXPECT_EQ(copy.getLine().getMethod(), original.getLine().getMethod());
	// EXPECT_EQ(copy.getHeader().getHost(), original.getHeader().getHost());
}

TEST_F(GetTest, AssignmentOperator) {
	std::string raw_request = "GET /index.html HTTP/1.1\r\nHost: example.com\r\n\r\n";
	Get original(raw_request);
	Get assigned;
	assigned = original;
	// 代入演算子のテスト
	// 例: EXPECT_EQ(assigned.getLine().getMethod(), original.getLine().getMethod());
	// EXPECT_EQ(assigned.getHeader().getHost(), original.getHeader().getHost());
}
