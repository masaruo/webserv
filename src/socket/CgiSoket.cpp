/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiSoket.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 02:08:55 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/28 13:10:06 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiSocket.hpp"
#include "define.hpp"
#include "Server.hpp"
#include "Env.hpp"
// #include <sys/epoll.h>
#include <sys/wait.h>
#include <cstring>//strcpy
// #include <cstdlib>
#include <unistd.h>
// #include "HttpException.hpp"
// #include "Env.hpp"
// #include "string.hpp"
// #include "Server.hpp"
#include "Fcntl.class.hpp"

int const	CgiSocket::INTERNAL_SERVER_ERROR = 50;

static void	assert_wait_(pid_t child_pid)
{
	int	status;
	pid_t	res = waitpid(child_pid, &status, WNOHANG);
	if (res == child_pid)
	{
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		{
			throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
		}
	}
}

CgiSocket::CgiSocket(ASocket *parent, RequestFactory const &factory, Server &server)
:ASocket(-1, server)
,parent_socket_(parent)
,factory_(factory)
,child_pid_(-1)
,data_()
{
	sockfd_[ft::PARENTFD] = -1;
	sockfd_[ft::CHILDFD] = -1;
	setupCGI();
	return ;
}

CgiSocket::~CgiSocket()
{
	if (sockfd_[ft::PARENTFD] > 2)
	{
		close(sockfd_[ft::PARENTFD]);
		fd_ = -1;
	}
	if (sockfd_[ft::CHILDFD] > 2)
		close(sockfd_[ft::CHILDFD]);
	return ;
}

void	CgiSocket::setupCGI(void)
{
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockfd_) == -1)
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
	ft::Fcntl::setNonBlock(sockfd_[ft::PARENTFD]);
	fd_ = sockfd_[ft::PARENTFD];

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
	// if (chdir(script_path_.c_str()) == -1)
	// 	std::exit(INTERNAL_SERVER_ERROR);
	
	// ft::string const &path(script_path_);
	// ft::string::string_vector	split_by_slash = path.split("/");
	// ft::string const &filename = split_by_slash.back();

	// std::string const &path = factory_.getRequestLine().getUri().getPath();
	// config::ConfigFactory &loc = server_.getConfigFactory().getConfig().getConfigLocation(path);
	std::string chdir_target = "/webserv/cgi-bin";//todo get from config
	if (chdir(chdir_target.c_str()) == -1)
	{
		std::exit(INTERNAL_SERVER_ERROR);
	}

	Env env(factory_.getRequestLine(), factory_.getHeader(), factory_.getBody());

	std::string const &filename = "echo.py";//todo get from config
	// std::string const &filename = factory_.getRequestLine().getUri().getPathInfo().fileName_;
	char	**argv;
	try
	{
		argv = generateArgv(filename);
	}
	catch(std::bad_alloc const &e)
	{
		std::exit(INTERNAL_SERVER_ERROR);
	}

	execve(argv[0], argv, env.c_env());

	std::exit(INTERNAL_SERVER_ERROR);
}

// void	CgiSocket::execute(void)
// {
	// ft::State	&state = getRefState();
	// bool		complete = false;

	// switch (state)
	// {
	// 	case (ft::CGI_SEND):
	// 		complete = io_.send(state);
	// 		if (complete)
	// 		{
	// 			shutdown(getFd(), SHUT_WR);
	// 			setState(ft::CGI_RECV);
	// 			io_.clear();
	// 			updateEventsWithState();
	// 		}
	// 		break ;
	// 	case (ft::CGI_RECV):
	// 		complete = io_.recv(state);
	// 		if (complete)
	// 		{
	// 			response_body_ = io_.getData();
	// 			setState(ft::CGI_COMPLETE);
	// 			updateEventsWithState();
	// 		}
	// 		break ;
	// 	case (ft::CGI_COMPLETE):
	// 		assert_wait_(child_pid_);
	// 		if (parent_socket_)
	// 		{
	// 			ActiveSocket *active = dynamic_cast<ActiveSocket*>(parent_socket_);
	// 			active->setData(response_body_);
	// 			parent_socket_->setState(ft::SEND);
	// 		}
	// 		setState(ft::DELETE);
	// 		break ;
	// 	default:
	// 		break ;

	// }
// }

// std::string	CgiSocket::getData(void) const
// {
// 	return (response_body_);
// }

void	CgiSocket::handleEvent(uint32_t event)
{
	if (event == EPOLLOUT)
	{
		// setupCGI();
	}
	else if (event == EPOLLIN)
	{
		
	}
	else
	{
		throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	}
}
