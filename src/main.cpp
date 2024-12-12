/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 06:06:23 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/12 02:55:36 by mogawa           ###   ########.fr       */
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
		return (EXIT_FAILURE);
	}
	catch (...)
	{
		std::cerr << "main.cpp:32 Non Standard Fatal Error." << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
