/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 06:06:23 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/06 09:32:49 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <signal.h>

int main(void)
{
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return (1);
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
