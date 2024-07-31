// sample_class_test.cpp
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sample_class.h"

class MockDatabaseConnection : public DatabaseConnection {
public:
    MOCK_METHOD(bool, connect, (const std::string&), (override));
    MOCK_METHOD(void, disconnect, (), (override));
};

TEST(UserManagerTest, LoginSuccess) {
    MockDatabaseConnection mockDb;
    UserManager userManager(&mockDb);

    EXPECT_CALL(mockDb, connect("connection_string"))
        .WillOnce(testing::Return(true));
    EXPECT_CALL(mockDb, disconnect())
        .Times(1);

    bool result = userManager.login("admin", "password");
    EXPECT_TRUE(result);
}

TEST(UserManagerTest, LoginFailure) {
    MockDatabaseConnection mockDb;
    UserManager userManager(&mockDb);

    EXPECT_CALL(mockDb, connect("connection_string"))
        .WillOnce(testing::Return(true));
    EXPECT_CALL(mockDb, disconnect())
        .Times(1);

    bool result = userManager.login("admin", "wrong_password");
    EXPECT_FALSE(result);
}

TEST(UserManagerTest, DatabaseConnectionFailure) {
    MockDatabaseConnection mockDb;
    UserManager userManager(&mockDb);

    EXPECT_CALL(mockDb, connect("connection_string"))
        .WillOnce(testing::Return(false));
    EXPECT_CALL(mockDb, disconnect())
        .Times(0);

    bool result = userManager.login("admin", "password");
    EXPECT_FALSE(result);
}
