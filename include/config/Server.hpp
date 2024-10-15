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

    // bool is_config(Config& config);
    // bool is_server(Config& config);
    // bool is_server_name(Config& config);
    // bool is_port(Config& config);
    // bool is_root(Config& config);
    // bool is_max_body_size(Config& config);
    // bool is_timeout(Config& config);
    // bool is_error_page(Config& config);
    // bool start_with(const std::string& str);
public:    
    // Parser(const std::string& file_name);
    Parser(std::string raw);
    // Config parse(Config& config);
    std::string get_token();
    std::string consume_token();
};

bool isbrace(int c);
bool issemicolon(int c);
bool isnums(const std::string& str);
