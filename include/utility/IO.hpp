/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IO.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:22:20 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/07 01:22:10 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"

#include <define.hpp>
#include <string>
#include <sys/socket.h>


class IO
{
private:
	int			fd_;
	std::string	data_;
	std::string	rest_;

	RequestLine	line_;
	HttpHeader	header_;
	HttpBody	body_;

	void	parseBuffer(ft::State &state);
	void	parseRequestLine(ft::State &state);
	void	parseHeader(ft::State &state);
	bool	parseBody(ft::State &state);
	// internal function
	ssize_t		recv_until(std::string const &until);
	ssize_t		recv_length(std::size_t len);
	ssize_t		recv_chunk(void);
	IO();//=delete
public:
	explicit	IO(int fd);
	~IO();
	IO(IO const &rhs);
	IO &operator=(IO const &rhs);

	ssize_t	recv(ft::State &state);
	ssize_t	send(std::string const &data) const;

	void		clear(void);
	std::string	getData(void) const;
	std::size_t	getSize(void) const;
};
