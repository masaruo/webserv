/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 06:06:23 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/28 05:15:50 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <signal.h>

int main(void)
{
	signal(SIGINT, NULL);//todo sigintの時の終了処理？sigterm?
	try
	{
		Server	server("./config/config.md");
		server.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}
