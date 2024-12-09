/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 06:06:23 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/07 23:34:17 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <signal.h>

int main(void)
{
	try
	{
		if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
			throw (std::runtime_error("Signal to catch SIGPIPE failed to set up."));
		Server	server("./config/config.md");
		server.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << "main.cpp:27 fatal error caught " << e.what() << std::endl;
		return (1);
	}
	catch (...)
	{
		std::cerr << "main.cpp:32 Non Standard Fatal Error." << std::endl;
		return (1);
	}
	return (0);
}
