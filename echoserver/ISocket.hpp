/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ISocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 00:32:11 by mogawa            #+#    #+#             */
/*   Updated: 2024/10/31 02:26:52 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class ISocket
{
public:
	virtual				~ISocket(){ return ; };
	virtual void		close(void) = 0;
	virtual ISocket*	clone(void) const = 0;
};
