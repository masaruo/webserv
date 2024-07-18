/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:47:26 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/18 19:30:14 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Socket
{
private:
    int							fd_;
    struct sockaddr_in const	addr_;
    
    // member function
    // hidden
    Socket();
    Socket(Socket const &rhs);
    Socket &operator=(Socket const &rhs);
public:
    Socket(int port);
    ~Socket();
    void    closeSocket(void) const;
    int     getAcceptedFD(void);
    //todo exceptions
};