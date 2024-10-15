/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:10:22 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/28 10:08:18 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ASocket.class.hpp"
#include "unique_ptr.hpp"
#include "ARequest.hpp"
#include "ConfigFactory.hpp"
#include <ctime>

class ClientSocket : public ASocket
{
private:
	ft::unique_ptr<ARequest>	request_;
	std::time_t					last_activity_;
	std::time_t					timeout_;

	int	acceptHandler(int listen_fd);
	std::time_t	get_time(void) const;
	ClientSocket();//=delete
	ClientSocket(ClientSocket const &rhs);//=delete
	ClientSocket &operator=(ClientSocket const &rhs);//=delete
public:
	explicit ClientSocket(int listen_fd);
	~ClientSocket();
	void setSockaddr(void);//? need?
	void	recv_handler(config::ConfigFactory const &config_factory);
	void	set_time(void);
	void	check_timeouts(void);
};
