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
#include <ctime>

// class ARequest;
// class AResponse;

class ClientSocket : public ASocket
{
private:
	ft::unique_ptr<ARequest>	request_;
	std::time_t					last_activity_;
	std::size_t					timeout_;
	// ARequest	*request_;
	// AResponse	*response_;
	int	acceptHandler(int listen_fd);
	std::time_t	get_time(void) const;
	ClientSocket();
	ClientSocket(ClientSocket const &rhs);
	ClientSocket &operator=(ClientSocket const &rhs);
public:
	ClientSocket(int listen_fd);
	~ClientSocket();
	void setSockaddr(void);//?
	ssize_t	recv_handler(void);
	ssize_t	send_hander(void) const;
	void	set_time(void);
	void	check_timeouts(void);
};
