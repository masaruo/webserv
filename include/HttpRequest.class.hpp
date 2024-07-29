/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:05:58 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/28 17:07:24 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class HttpRequest
{
private:

public:
	HttpRequest();
	~HttpRequest();
	HttpRequest(HttpRequest const &rhs);
	HttpRequest &operator=(HttpRequest const &rhs);
};
