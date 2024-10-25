#include "Parser.hpp"

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

bool isnums(const std::string& str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!isdigit(str[i]))
            return (false);
    return (true);
}

Parser::Parser(std::string raw) : content_(raw), buf_idx_(0)
{}

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

// int main()
// {
//     std::string str = "server {\n\tlisten 8080;\n\tserver_name localhost; \n\troot ./docs/;\n\tmax_body_size 10000;\n\tkeep_alive_timeout 75;\n\terror_page 404 /404.html;\n\t}\n";
//     // std::string str = "server { }";
//     std::cout << str << std::endl;
//     // std::cout << std::boolalpha << is_config(str) << std::endl;

//     Parser parser(str);
//     Config config = parser.parse();
//     std::cout << "port: " << config.port_ << std::endl;
//     std::cout << "server_name: " << config.server_name_ << std::endl;
//     std::cout << "root: " << config.root_ << std::endl;
//     std::cout << "max_body_size: " << config.max_body_size_ << std::endl;
//     std::cout << "keep_alive_timeout: " << config.keep_alive_timeout_ << std::endl;
//     std::cout << "code: " << config.error_pages_.begin()->first << std::endl;
//     std::cout << "error_page: " << config.error_pages_.begin()->second << std::endl;
//     // std::cout << parser.get_token() << std::endl;
//     // std::cout << parser.get_token() << std::endl;
//     // std::cout << parser.get_token() << std::endl;
//     // std::cout << parser.get_token() << std::endl;
//     // std::cout << parser.get_token() << std::endl;
//     // std::cout << parser.get_token() << std::endl;
//     return (0);
// }

/*
<config> := <server>
<space> := (" " | "\t")+
<server> := "server <space> {" <server_name> <space> "}"
<server_name> := "a...z_"+
*/
