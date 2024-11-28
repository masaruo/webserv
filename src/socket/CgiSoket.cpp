/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiSoket.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 02:08:55 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/28 05:30:29 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiSocket.hpp"
#include "define.hpp"
#include <sys/epoll.h>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "HttpException.hpp"
#include "Env.hpp"
#include "string.hpp"
#include "Server.hpp"
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

CgiSocket::CgiSocket(Env const &env, std::string const &script_path, std::string const &request_body, Server &server)
:ASocket(-1, server)
// :ASocket(-1, -1, ft::CGI_SEND, EPOLLIN, server)
,env_(env)
,child_pid_(-1)
,script_path_(script_path)
,request_body_(request_body)
,response_body_()
,io_(-1)
,parent_socket_(NULL)
{
	setupCGI();
	return ;
}

CgiSocket::~CgiSocket()
{
	return ;
}

void	CgiSocket::setupCGI(void)
{
	// int			sockfds[2];
	// pid_t		pid = 0;
	// std::string	bodyStr = "";

	// if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockfds) == -1)
	// {
	// 	throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	// }

	// ft::Fcntl::setNonBlock(sockfds[ft::PARENTFD]);
	// // setFd(sockfds[ft::PARENTFD]);

	// sockaddr_in	dummy_sockaddr = {};
	// std::memset(&dummy_sockaddr, 0, sizeof(sockaddr));
	// // ASocket::Addr dummy;
	// dummy.addrin_ = dummy_sockaddr;
	// dummy.addrlen_ = sizeof(dummy);

	// cgi_socket_ = new ActiveSocket(0, sockfds[ft::PARENTFD], ft::CGISEND, EPOLLOUT, getServerReference(), dummy);
	// if (cgi_socket_ == NULL)
	// 	throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

	// pid = fork();
	// if (pid == ft::err)
	// {
	// 	close(sockfds[ft::PARENTFD]);
	// 	close(sockfds[ft::CHILDFD]);
	// 	throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));
	// }
	// else if (pid == 0)
	// {
	// 	execChild(sockfds);
	// }

	// //parent
	// if (close(sockfds[ft::CHILDFD]) == -1)
	// 	throw (HttpException(HttpCode::INTERNAL_SERVER_ERROR));

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
	if (chdir(script_path_.c_str()) == -1)
		std::exit(INTERNAL_SERVER_ERROR);
	
	ft::string const &path(script_path_);
	ft::string::string_vector	split_by_slash = path.split("/");
	ft::string const &filename = split_by_slash.back();

	char	**argv;
	try
	{
		argv = generateArgv(filename);
	}
	catch(std::bad_alloc const &e)
	{
		std::exit(INTERNAL_SERVER_ERROR);
	}

	execve(argv[0], argv, env_.c_env());

	std::exit(INTERNAL_SERVER_ERROR);
}

void	CgiSocket::execute(void)
{
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
}

std::string	CgiSocket::getData(void) const
{
	return (response_body_);
}
