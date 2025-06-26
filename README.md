### webserv project at 42Tokyo
* create a webserver based on nginx
* the server should be NON blocking
* the server should only have one eventloop (`epoll_wait`) and all read / write have to be conducted only after checking I/O
* the server should be able to handle `CGI`
* the server should NOT use child processes apart from CGI

### access
* run `make` then access `http://localhost:8888`
* access port can be altered by ./config/config.md

### environment
* run on ubuntu (use vscode devcontainer for mac)
* using epoll hence this will not compile in mac
