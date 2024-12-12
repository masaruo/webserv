/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 06:06:23 by mogawa            #+#    #+#             */
/*   Updated: 2024/12/12 07:18:37 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
メモ：
* no autoindex allowed in cgi-bin
* only jpeg, png, mp4, html, txt, pdf, json, zip allowed as an accepted mime type
	rest will be treated as "applicatio/octet-stream"
* bodysize is from define.hpp
* first server block is the default block
*/

#include "Server.hpp"

int main(int argc, char **argv)
{
	std::string	path;
	if (argc == 1)
		path = "./config/config.md";
	else if (argc == 2)
		path = argv[1];
	else
	{
		std::cerr << "main.cpp: Invalid numbers of args." << std::endl;
		return (EXIT_FAILURE);
	}

	try
	{
		Server	server(path);
		server.run();
	}
	catch (config::Config::ConfigErrorException const &e)
	{
		std::cerr << "main.cpp: Config related fatal error detected." << std::endl;
		return (EXIT_FAILURE);
	}
	catch (std::exception const &e)
	{
		std::cerr << "main.cpp: fatal error caught " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	catch (...)
	{
		std::cerr << "main.cpp: Non Standard Fatal Error." << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
