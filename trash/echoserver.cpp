/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echoserver.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:17:49 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/18 14:01:37 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 1025

int	ft_listen(int port_num) {
	int					fd;
	struct sockaddr_in	address;
	int					opt;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket()");
		return -1;
	}
	opt = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		perror("setsockopt()");
		close(fd);
		return -1;
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port_num);
	if (bind(fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind()");
		close(fd);
		return -1;
	}
	if (listen(fd, SOMAXCONN) < 0) {
		perror("listen()");
		close(fd);
		return -1;
	}
	return fd;
}

ssize_t	ft_send(int fd, const std::string &buffer) {
	ssize_t				ret;
	std::string			response;
	std::ostringstream	oss;

	oss << buffer.length() + 2;
	response += "HTTP/1.1 200 OK\r\n";
	response += "Content-Type: text/plain\r\n";
	response += "Content-Length: ";
	response += oss.str() + "\r\n";
	response += "\r\n";
	response += buffer;
	response += "\r\n";

	// send(): クライアントにレスポンスメッセージを送信する
	ret = send(fd, response.c_str(), response.length(), 0);
	if (ret < 0) {
		perror("send");
		return -1;
	} else if (ret == 0) {
		std::cout << "send 接続が切れた: " << fd << std::endl;
		return ret;
	}
	return ret;
}


ssize_t	ft_recv(int fd, std::string &buffer) {
	char	buf[BUF_SIZE];
	ssize_t	ret;

	ret = recv(fd, buf, (BUF_SIZE - 1), 0);
	if (ret < 0) {
		perror("recv");
		return -1;
	} else if (ret == 0) {
		std::cout << "recv 接続が切れた: " << fd << std::endl;
		return ret;
	}
	buffer = std::string(buf, ret);
	std::cout << "-----------リクエストメッセージ-----------" << std::endl;
	std::cout << buffer << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	return ret;
}

int	ft_accept(int listen_fd) {
	int					fd;
	struct sockaddr_in	address;
	int addrlen = sizeof(address);

	fd = accept(listen_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
	if (fd < 0) {
		perror("accept");
		return -1;
	}
	return fd;
}

int	main(int argc, const char **argv) {
	int			server_socket;
	int			connect_socket;
	ssize_t		ret;
	std::string	buf;

	if (argc != 2)
		return 1;
	server_socket = ft_listen(std::atoi(argv[1]));
	if (server_socket < 0)
		return 1;
	while (true) {
		connect_socket = ft_accept(server_socket);
		if (connect_socket < 0) {
			close(server_socket);
			return 1;
		}
		ret = ft_recv(connect_socket, buf);
		if (ret < 0) {
			close(server_socket);
			return 1;
		}
		ret = ft_send(connect_socket, buf);
		if (ret < 0) {
			close(server_socket);
			return 1;
		}
		close(connect_socket);
	}
	close(server_socket);
	return 0;
}