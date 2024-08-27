#include <iostream>
#include <string>
#include <ctime>

std::string getCurrentDateTime() {
    time_t now = std::time(NULL);
    char buffer[26];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buffer);
}

int main() {
    std::string content = "<!DOCTYPE html>\n"
                          "<html>\n"
                          "<head>\n"
                          "<meta charset=\"UTF-8\">\n"
                          "<title>Simple CGI Program</title>\n"
                          "</head>\n"
                          "<body>\n"
                          "<h1>Hello from CGI!</h1>\n"
                          "<p>Current date and time: " + getCurrentDateTime() + "</p>\n"
                          "</body>\n"
                          "</html>\n";

    // HTTPヘッダーの出力（バージョンを含む）
    std::cout << "HTTP/1.1 200 OK\r\n";
    std::cout << "Content-Type: text/html; charset=UTF-8\r\n";
    std::cout << "Content-Length: " << content.length() << "\r\n";
    std::cout << "\r\n";  // 空行を忘れずに

    // HTMLコンテンツの出力
    std::cout << content;

    return 0;
}
