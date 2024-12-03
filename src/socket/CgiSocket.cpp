/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiSocket.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 02:08:55 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/03 07:52:01 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiSocket.hpp"
#include "define.hpp"
#include "Server.hpp"
#include "Env.hpp"
#include "UriNormalizer.hpp"
#include "FileHandler.hpp"
#include "string.hpp"
#include <sys/wait.h>
#include <cstring>//strcpy
#include <unistd.h>
#include <fcntl.h>

int const	CgiSocket::INTERNAL_SERVER_ERROR = 50;

CgiSocket::CgiSocket(ClientSocket *parent, RequestFactory const &factory, Server &server)
:ASocket(-1, server)
,parent_socket_(parent)
,factory_(factory)
,child_pid_(-1)
,data_()
{
	setAddr(parent->getAddr());
	sockfd_[ft::PARENTFD] = -1;
	sockfd_[ft::CHILDFD] = -1;
	return ;
}

CgiSocket::~CgiSocket()
{
	if (sockfd_[ft::PARENTFD] > 2)
	{
		close(sockfd_[ft::PARENTFD]);
		setFd(-1);
	}
	if (sockfd_[ft::CHILDFD] > 2)
		close(sockfd_[ft::CHILDFD]);
	return ;
}

void	CgiSocket::handleCgiExecution(void)
{
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockfd_) == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	if (fcntl(sockfd_[ft::PARENTFD], F_SETFL, O_NONBLOCK) == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	setFd(sockfd_[ft::PARENTFD]);

	child_pid_ = fork();
	if (child_pid_ == ft::err)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	else if (child_pid_ == 0)
	{
		execChild(sockfd_);
	}

	//parent
	if (close(sockfd_[ft::CHILDFD]) == -1)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	server_.add(this, EPOLLOUT);
}

static char	**generateArgv(std::string const &uri)
{
	char	**argv = NULL;
	std::string	cgiPath;

	argv = new char*[2]();
	argv[1] = NULL;

	argv[0] = new char[uri.size() + 1]();
	std::strcpy(argv[0], uri.c_str());
	return (argv);
}

static void assertCgiPath(std::string const &dir, std::string const &file)
{
	std::string const pathWithRoot = dir + "/" + file;
	if (!FileHandler::checkPathExist(dir))
		throw (HttpException(HttpCode::NOT_FOUND));
	if (!FileHandler::checkIfFile(pathWithRoot))
		throw (HttpException(HttpCode::CONFLICT));
	if (access(pathWithRoot.c_str(), X_OK) == -1)
		throw (HttpException(HttpCode::FORBIDDEN));
}

void	CgiSocket::execChild(int sockfd[2])
{
	if (close(sockfd[ft::PARENTFD]) == -1)
		std::exit(INTERNAL_SERVER_ERROR);
	if (dup2(sockfd[ft::CHILDFD], STDIN_FILENO) == -1)
		std::exit(INTERNAL_SERVER_ERROR);
	if (dup2(sockfd[ft::CHILDFD], STDOUT_FILENO) == -1)
		std::exit(INTERNAL_SERVER_ERROR);
	if (close(sockfd[ft::CHILDFD]) == -1)
		std::exit(INTERNAL_SERVER_ERROR);
	
	HttpUri const &uri = factory_.getRequestLine().getUri();
	config::Config const &config = server_.getConfigFactory().getConfig(uri.getHost());
	std::string const &cgiPath = config.getConfigLocation(uri.getPath()).directive_.getFirstValue(config::Config::CGI_ROOT);
	// std::string const &cgiDir = uri.getPathInfo().directory_;
	// std::string const &cgiPath = cgiRoot + cgiDir;
	std::string const &scriptName = uri.getPathInfo().fileName_;
	assertCgiPath(cgiPath, scriptName);
	if (chdir(cgiPath.c_str()) == -1)
	{
		std::exit(INTERNAL_SERVER_ERROR);
	}
	Env env(factory_.getRequestLine(), factory_.getHeader(), factory_.getBody());
	uint32_t const ip = ntohl(getAddr().sin_addr.s_addr);
	std::stringstream ip_ss;
	ip_ss << ((ip >> 24) & 0xFF) << '.' << ((ip >> 16) & 0xFF) << '.' << ((ip >> 8) & 0xFF) << '.' << (ip & 0xFF);
	env.addEnvItem("remote_addr", ip_ss.str());

	// ft::string const &path = getCgiPath();
	// ft::string::string_vector	split_by_slash = path.split("/");
	// ft::string const &filename = split_by_slash.back();
	// split_by_slash.pop_back();
	// ft::string const &chdir_target = ft::reverse_split(split_by_slash, '/');

	// std::string const &path = factory_.getRequestLine().getUri().getPath();
	// config::ConfigFactory &loc = server_.getConfigFactory().getConfig().getConfigLocation(path);
	// std::string chdir_target = "/webserv/cgi-bin";//todo get from config

	// if (chdir(chdir_target.c_str()) == -1)
	// {
	// 	std::exit(INTERNAL_SERVER_ERROR);
	// }

	// Env env(factory_.getRequestLine(), factory_.getHeader(), factory_.getBody(), getAddr());

	// std::string const &filename = "echo.py";//todo get from config
	// std::string const &filename = factory_.getRequestLine().getUri().getPathInfo().fileName_;
	char	**argv;
	try
	{
		argv = generateArgv(scriptName);
	}
	catch(std::bad_alloc const &e)
	{
		std::exit(INTERNAL_SERVER_ERROR);
	}

	execve(argv[0], argv, env.c_env());

	std::exit(INTERNAL_SERVER_ERROR);
}


void	CgiSocket::handleEvent(uint32_t event)
{
	char buf[2043];
	ssize_t bytes;

	if (event & EPOLLOUT)
	{
		//todo change to chunk or large file
		std::string const &body = factory_.getBody().c_str();
		send(getFd(), body.c_str(), body.size(), 0);
		server_.mod(this, EPOLLIN);
	}
	else if (event & (EPOLLIN | EPOLLHUP))
	{
	 	bytes = recv(getFd(), buf, sizeof(buf), 0);
		if (bytes <= 0)
		{
			int status;
			waitpid(child_pid_, &status, WNOHANG);
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
				data_ = "Status: 500 Internal Server Error\r\n\r\n";
			}
			//todo assert data from child
			parent_socket_->setData(data_);
			server_.mod(parent_socket_, EPOLLOUT);
			setSocketAsClose();
			return;
		}
		data_.append(buf, bytes);
	}
	else
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
}
