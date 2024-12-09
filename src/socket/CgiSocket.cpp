/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiSocket.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 02:08:55 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/09 08:57:52 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiSocket.hpp"
#include "define.hpp"
#include "Server.hpp"
#include "Env.hpp"
#include "UriNormalizer.hpp"
#include "FileHandler.hpp"
#include "string.hpp"
#include "Response.hpp"
#include <sys/wait.h>
#include <cstring>//strcpy
#include <unistd.h>
#include <fcntl.h>

int const	CgiSocket::INTERNAL_SERVER_ERROR = 50;
int const	CgiSocket::NOT_FOUND = 51;
int const	CgiSocket::FORBIDDEN = 53;

CgiSocket::CgiSocket(ClientSocket *parent, RequestFactory const &factory, Server &server)
:ASocket(-1, server)
,parent_socket_(parent)
,factory_(factory)
,child_pid_(-1)
,recv_buf_()
{
	setAddr(parent->getAddr());
	sockfd_[ft::PARENTFD] = -1;
	sockfd_[ft::CHILDFD] = -1;
	updateLastActiveTime();
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

	send_buf_ = factory_.getBody().c_str();

	child_pid_ = fork();
	if (child_pid_ == -1)
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

static int assertCgiPath_(std::string const &dir, std::string const &file)
{
	std::string const pathWithRoot = dir + "/" + file;
	if (!FileHandler::isExist(dir))
		return (CgiSocket::NOT_FOUND);
	if (!FileHandler::isOK(dir, R_OK | X_OK))
		return (CgiSocket::FORBIDDEN);
	if (!FileHandler::isExist(pathWithRoot))
		return (CgiSocket::NOT_FOUND);
	if (!FileHandler::isOK(pathWithRoot, R_OK | X_OK))
		return (CgiSocket::FORBIDDEN);
	return (0);
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
	std::string const &scriptName = uri.getPathInfo().fileName_;
	int error = assertCgiPath_(cgiPath, scriptName);
	if (error != 0)
		std::exit(error);
	if (chdir(cgiPath.c_str()) == -1)
		std::exit(INTERNAL_SERVER_ERROR);

	Env env(factory_.getRequestLine(), factory_.getHeader(), factory_.getBody());
	uint32_t const ip = ntohl(getAddr().sin_addr.s_addr);
	std::stringstream ip_ss;
	ip_ss << ((ip >> 24) & 0xFF) << '.' << ((ip >> 16) & 0xFF) << '.' << ((ip >> 8) & 0xFF) << '.' << (ip & 0xFF);
	env.addEnvItem("remote_addr", ip_ss.str());

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

void	CgiSocket::assertTimeout(void) const
{
	time_t	now = time(NULL);
	if (now == -1)
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	else if (now > getLastActiveTime() + ft::TIMEOUT_CGI_SEC)
		throw (HttpException(HttpCode::REQUEST_TIMEOUT));
	else
		return ;
}

static Response	createResponse(std::string const &buf, int exit_status)
{
	if (exit_status == CgiSocket::INTERNAL_SERVER_ERROR)
		return (Response(HttpStatus(HttpCode::INTERNAL_SERVER_ERROR)));
	if (exit_status == CgiSocket::NOT_FOUND)
		return (Response(HttpStatus(HttpCode::NOT_FOUND)));
	if (exit_status == CgiSocket::FORBIDDEN)
		return (Response(HttpStatus(HttpCode::FORBIDDEN)));

	std::string::size_type	posCRLFCRLF = buf.find("\r\n\r\n");
	if (posCRLFCRLF == std::string::npos)
		return (Response(HttpStatus(HttpCode::INTERNAL_SERVER_ERROR)));

	std::string const	&buf_header = buf.substr(0, posCRLFCRLF + 4);
	std::string const	&buf_body = buf.substr(posCRLFCRLF + 4);

	ResponseHeader header(buf_header);
	if (!header.hasKey(AHeader::CONTENT_TYPE))
		return (Response(HttpStatus(HttpCode::INTERNAL_SERVER_ERROR)));

	HttpBody	body(buf_body);
	HttpStatus	status(HttpCode::OK);

	return (Response(status, header, body));
}

void	CgiSocket::handleEvent(uint32_t event)
{
	#ifndef DEBUG
	assertTimeout();
	#endif
	ssize_t bytes = 0;
	if (event & EPOLLOUT)
	{
		if (send_buf_.empty())
		{
			updateLastActiveTime();
			server_.mod(this, EPOLLIN);
			return ;
		}
		bytes = send(getFd(), send_buf_.c_str(), send_buf_.size(), 0);
		if (bytes <= 0)
			throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
		send_buf_ = send_buf_.substr(bytes);
	}
	else if (event & (EPOLLIN | EPOLLRDHUP))
	{
		char buf[ft::READ_BUF_SIZE];
	 	bytes = recv(getFd(), buf, sizeof(buf), 0);
		if (bytes == -1)
			throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
		else if (bytes == 0)
		{
			int status;
			Response	res;
			waitpid(child_pid_, &status, WNOHANG);
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
				res = createResponse("", WEXITSTATUS(status));
			else
				res = createResponse(recv_buf_, 0);
			parent_socket_->setData(res.to_string());
			parent_socket_->updateLastActiveTime();
			server_.mod(parent_socket_, EPOLLOUT);
			setSocketClose();
			return;
		}
		else
			recv_buf_.append(buf, bytes);
	}
	else
	{
		return ;
	}
}

