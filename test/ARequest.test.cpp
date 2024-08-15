#include <gtest/gtest.h>
#include "ARequest.hpp"
#include "Get.hpp"

class ARequestTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		// セットアップコード（必要な場合）
	}

	virtual void TearDown() {
		// クリーンアップコード（必要な場合）
	}
};

TEST_F(ARequestTest, DefaultConstructor) {
	Get request;  // ARequestは抽象クラスなので、具象クラスのGetを使用
	// デフォルトコンストラクタのテスト
	// ここでは、line_とheader_が正しく初期化されているかを確認します
	// 例: EXPECT_EQ(request.getLine().getMethod(), "");
}

TEST_F(ARequestTest, ConstructorWithRawRequest) {
	std::string raw_request = "GET /index.html HTTP/1.1\r\nHost: example.com\r\n\r\n";
	Get request(raw_request);
	// raw_requestで初期化されたリクエストのテスト
	// 例: EXPECT_EQ(request.getLine().getMethod(), "GET");
	// EXPECT_EQ(request.getHeader().getHost(), "example.com");
}
