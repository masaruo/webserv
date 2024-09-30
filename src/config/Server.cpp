#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include "../../include/http/common/HttpCode.hpp"
// #include <../../include/config/Location.hpp>

/*
<config> := <server>
<space> := (" " | "\t")+
<server> := "server <space> {" <server_name> <space> "}"
<server_name> := "a...z_"+
*/

bool isbrace(int c)
{
    if (c == '{' || c == '}')
        return (true);
    return (false);
}

bool issemicolon(int c)
{
    if (c == ';')
        return (true);
    return (false);
}


class Config {
public:    
	std::string								server_name_;
	std::size_t								port_;
	std::string								root_;
	std::size_t								max_body_size_;
	std::map<HttpCode::code_e, std::string>	error_pages_;
	std::size_t								keep_alive_timeout_;
	// std::map<std::string, location_s>		locations_;
};

class Parser {
private:
    std::string content_;
    size_t buf_idx_;

    bool is_config(Config& config);
    bool is_server(Config& config);
    bool is_server_name(Config& config);
    bool is_port(Config& config);
    bool is_root(Config& config);
    bool is_max_body_size(Config& config);
    bool start_with(const std::string& str);
public:    
    // Parser(const std::string& file_name);
    Parser(std::string raw);
    Config parse();
    std::string get_token();
    std::string consume_token();
};

Parser::Parser(std::string raw) : content_(raw), buf_idx_(0)
{}

Config Parser::parse()
{
    Config config;
    if (!is_config(config))
        throw std::runtime_error("invalid config");
    return (config);
}

bool Parser::is_config(Config& config) {
    return is_server(config);
}

bool Parser::start_with(const std::string& str)
{
    size_t len = str.size();
    size_t i;
    for (i = 0; i < len; i++)
        if (content_[buf_idx_ + i] != str[i])
            return false;
    return true;
}

bool Parser::is_server(Config& config) {
    if (consume_token() != "server")
        return false;
    if (consume_token() != "{")
        return false;
    while (get_token() != "}" && get_token() != "\0")
    {
        is_port(config);
        is_server_name(config);
        is_root(config);
        is_max_body_size(config);
    }
    if (consume_token() != "}")
        return false;
    return true;
}

bool Parser::is_server_name(Config& config) {
    if (get_token() != "server_name")
        return false;
    consume_token();
    std::string server_name = consume_token();
    config.server_name_ = server_name;
    if (consume_token() != ";")
        return false;
    return true;
}

bool Parser::is_port(Config& config) {
    if (get_token() != "listen")
        return false;
    consume_token();
    std::stringstream port;
    port << consume_token();
    port >> config.port_;
    if (consume_token() != ";")
        return false;
    return true;
}

bool Parser::is_root(Config& config) {
    if (get_token() != "root")
        return false;
    consume_token();
    config.root_ = consume_token();
    if (consume_token() != ";")
        return false;
    return true;
}

bool Parser::is_max_body_size(Config& config) {
    if (get_token() != "max_body_size")
        return false;
    consume_token();
    std::stringstream max_body_size;
    max_body_size << consume_token();
    max_body_size >> config.max_body_size_;
    if (consume_token() != ";")
        return false;
    return true;
}

std::string Parser::get_token()
{
    while (isspace(content_[buf_idx_]))
        buf_idx_++;
    if (isbrace(content_[buf_idx_]) || issemicolon(content_[buf_idx_]))
        return (content_.substr(buf_idx_, 1));
    size_t token_len = 0;
    while (!isspace(content_[buf_idx_ + token_len])
        && !isbrace(content_[buf_idx_ + token_len])
        && !issemicolon(content_[buf_idx_ + token_len])
        && content_[buf_idx_ + token_len] != '\0')
        token_len++;
    return (content_.substr(buf_idx_, token_len));
}

std::string Parser::consume_token()
{
    while (isspace(content_[buf_idx_]))
        buf_idx_++;
    std::string token;
    if (isbrace(content_[buf_idx_]) || issemicolon(content_[buf_idx_]))
    {
        token = content_.substr(buf_idx_, 1);
        buf_idx_++;
        return (token);
    }
    size_t token_len = 0;
    while (!isspace(content_[buf_idx_ + token_len])
        && !isbrace(content_[buf_idx_ + token_len])
        && !issemicolon(content_[buf_idx_ + token_len])
        && content_[buf_idx_ + token_len] != '\0')
        token_len++;
    token = content_.substr(buf_idx_, token_len);
    buf_idx_ += token_len;
    return (token);
}

int main()
{
    std::string str = "server {\n\tlisten 8080;\n\tserver_name localhost;\n\troot ./docs/;\n\tmax_body_size 10000;\n\t}\n";
    // std::string str = "server { }";
    std::cout << str << std::endl;
    // std::cout << std::boolalpha << is_config(str) << std::endl;

    Parser parser(str);
    Config config = parser.parse();
    std::cout << "port: " << config.port_ << std::endl;
    std::cout << "server_name: " << config.server_name_ << std::endl;
    std::cout << "root: " << config.root_ << std::endl;
    std::cout << "max_body_size: " << config.max_body_size_ << std::endl;
    // std::cout << parser.get_token() << std::endl;
    // std::cout << parser.get_token() << std::endl;
    // std::cout << parser.get_token() << std::endl;
    // std::cout << parser.get_token() << std::endl;
    // std::cout << parser.get_token() << std::endl;
    // std::cout << parser.get_token() << std::endl;
    return (0);
}