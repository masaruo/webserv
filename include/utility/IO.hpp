/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IO.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:22:20 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/08 07:01:14 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"

#include <define.hpp>
#include <string>
#include <sys/socket.h>

namespace config
{
	class ConfigFactory;
}

class ARequest;

class IO
{
public:
	static int const	CHUNK_BODY;
	static int const	LENGTH_BODY;
	static int const	NO_BODY;
private:
	int							fd_;
	std::string					data_;
	std::string					rest_;
	config::ConfigFactory const	&config_factory_;
	RequestLine					line_;
	HttpHeader					header_;
	HttpBody					body_;

	bool	parseBuffer(ft::State &state);
	bool	parseRequestLine(ft::State &state);
	bool	parseHeader(ft::State &state, bool &request_complete);
	bool	parseBody(ft::State &state, bool &request_complete);
	bool	parseBodyWithLength(ft::State &state, std::size_t size);
	bool	parseBodyWithChunk(ft::State &state);
	IO();//=delete
public:
	explicit	IO(int fd, config::ConfigFactory const &factory);
	~IO();
	IO(IO const &rhs);
	IO &operator=(IO const &rhs);

	bool	recv(ft::State &state);
	bool	send(ft::State &state);

	void		clear(void);
	void		setData(std::string const &data);
	std::string	getData(void) const;
	std::size_t	getSize(void) const;

	ARequest	*createRequest(void);
};
