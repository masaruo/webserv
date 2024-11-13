/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiSocket.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:53:40 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/13 05:55:52 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ASocket.hpp"
#include "IO.hpp"
#include "Env.hpp"

class CgiSocket : public ASocket
{
public:
	static int const	INTERNAL_SERVER_ERROR;
private:
	Env			env_;
	pid_t		child_pid_;
	std::string	script_path_;
	std::string	request_body_;
	std::string	response_body_;
	IO			io_;
	void	setupCGI(void);
	void	execChild(int sockfd[2]);

	CgiSocket(CgiSocket const &rhs);
	CgiSocket &operator=(CgiSocket const &rhs);
public:
	explicit CgiSocket(Env const &env, std::string const &script_path, std::string const &request_body, Server &server);
	~CgiSocket();
	void		execute(void);
	std::string	getData(void) const;
};
