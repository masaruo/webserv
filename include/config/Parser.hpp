#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include "Config.hpp"


class Config;

class Parser {
private:
    std::string content_;
    size_t buf_idx_;
    size_t new_line_num;
public:
    Parser(std::string raw);
    std::string get_token();
    std::string consume_token();
    size_t get_new_lile_num() const;
};

bool isbrace(int c);
bool issemicolon(int c);
bool isnums(const std::string& str);
