/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 06:06:23 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/11 03:55:49 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
メモ：
* no autoindex allowed in cgi-bin
* only jpeg, png, mp4, html, txt, pdf, json, zip allowed as an accepted mime type
	rest will be treated as "applicatio/octet-stream"
* 一番最初のコンフィグがデフォルト
*/

#include "Server.hpp"
#include <signal.h>

//! read from argv
int main(int argc, char **argv)//todo read from argv
{
	try
	{
		if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
			throw (std::runtime_error("Signal to catch SIGPIPE failed to set up."));
		Server	server("./config/config.md");
		server.run();
	}
	catch (config::Config::ConfigErrorException const &e)
	{
		std::cerr << "main.cpp:35 Config related fatal error detected." << std::endl;
	}
	catch (std::exception const &e)
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
