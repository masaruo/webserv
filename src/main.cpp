/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 06:06:23 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/05 10:08:47 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <signal.h>

int main(void)
{
	signal(SIGPIPE, SIG_IGN);
	try
	{
		Server	server("./config/config.md");
		server.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << "main.cpp: " << e.what() << std::endl;
		return (1);
	}
	catch (...)
	{
		return (1);
	}
	return (0);
}
