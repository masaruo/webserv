/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:58:08 by mogawa            #+#    #+#             */
/*   Updated: 2024/11/07 06:23:13 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ConfigFactory.hpp"
#include "RequestLine.hpp"
#include "HttpHeader.hpp"
#include "HttpBody.hpp"
#include "define.hpp"

class ARequest;

class RequestFactory
{
private:
	ft::State	state_;
	RequestLine	line_;
	HttpHeader	header_;
	HttpBody	body_;

	bool	parseRequestLine(std::string &buffer);
	bool	parseHeader(std::string &buffer);
	bool	parseBody(std::string &buffer);
public:
	static ARequest	*createRequest(int fd, config::ConfigFactory const &config_factory);
	static void		createRequestLineAndHeader(int fd, RequestLine &line, HttpHeader &header);
	static int		hasBody(HttpHeader const &header);
};
