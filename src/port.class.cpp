/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:47:23 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/19 19:07:50 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "port.class.hpp"
#include <unistd.h>
// #include <fcntl.h>

static struct sockaddr_in   makeSockaddr(int port)
{
    struct sockaddr_in  addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);//? htonsl
    addr.sin_addr.s_addr = htons(INADDR_ANY);
    return (addr);
}

// static void  flagNonblock(int fd)
// {
//     int flag = 0;

//     flag = fcntl(fd, F_GETFL);
//     if (flag == -1)
//     {
//         //todo error
//     }
//     flag |= O_NONBLOCK;
//     if (fcntl(fd, F_SETFL, flag) == -1)
//     {
//         //todo error
//     }
// }

Port::Port(int port)
:port_(port), addr_(makeSockaddr(port))
{
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    //todo error
    int optval = 1;
    if (setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
    {
        //todo error
    }
    makeSockaddr(port);
    if (bind(fd_, (struct sockaddr *)&addr_, sizeof(addr_)) == -1)//? static_cast?
    {
        //todo error
    }
    if (listen(fd_, SOMAXCONN))
    {
        //todo error
    }
    return ;   
}

Port::~Port()
{
    close (fd_);
    return ;
}

void    Port::closePort(void) const
{
    close (fd_);
}

int Port::getPort(void) const
{
    return (port_);
}

int	Port::getFd(void) const
{
    return (fd_);
}
