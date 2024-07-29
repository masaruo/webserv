// sample_class.h
#pragma once
#include <string>

class DatabaseConnection {
public:
    virtual ~DatabaseConnection() = default;
    virtual bool connect(const std::string& connectionString) = 0;
    virtual void disconnect() = 0;
};

class UserManager {
public:
    UserManager(DatabaseConnection* db) : m_db(db) {}
    bool login(const std::string& username, const std::string& password) {
        if (m_db->connect("connection_string")) {
            // Simulate login logic
            bool success = (username == "admin" && password == "password");
            m_db->disconnect();
            return success;
        }
        return false;
    }
private:
    DatabaseConnection* m_db;
};
