/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiSocket.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:53:40 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/28 08:38:54 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ASocket.hpp"
#include "RequestFactory.hpp"
// #include "IO.hpp"
// #include "Env.hpp"

class CgiSocket : public ASocket
{
public:
	static int const	INTERNAL_SERVER_ERROR;
private:
	ASocket			*parent_socket_;
	RequestFactory	factory_;
	pid_t			child_pid_;
	std::string		data_;
	int				sockfd_[2];

	void	setupSocketPair(void);
	void	setupCGI(void);
	void	execChild(int fd[2]);
	void	execParent(int fd);

	CgiSocket(CgiSocket const &rhs);
	CgiSocket &operator=(CgiSocket const &rhs);
public:
	explicit	CgiSocket(ASocket *parent, RequestFactory const &factory, Server &server);
	// explicit CgiSocket(Env const &env, std::string const &script_path, std::string const &request_body, Server &server);
	~CgiSocket();
	void	handleEvent(uint32_t event);
};
