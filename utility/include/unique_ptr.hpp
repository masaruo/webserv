/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_ptr.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:47:20 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/17 16:16:16 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{

template <typename T>
class unique_ptr
{
private:
	T	*ptr_;
	unique_ptr(unique_ptr const &rhs){ (void) rhs; }// hidden
	unique_ptr &operator=(unique_ptr const &rhs){ (void) rhs; return (*this); }// hidden
public:
	unique_ptr();
	unique_ptr(T *inPtr);
	~unique_ptr();
	unique_ptr(unique_ptr &rhs);
	unique_ptr &operator=(unique_ptr &rhs);
	unique_ptr &operator*(void) const;
	unique_ptr *operator->(void) const;

	// class functions
	T		*get(void) const;
	void	reset(T *inPtr = NULL);
	T		*release(void);
};

template <typename T>
void	unique_ptr<T>::reset(T *inPtr)
{
	if (ptr_ != inPtr)
	{
		delete ptr_;
		ptr_ = inPtr;
	}
}

template <typename T>
T	*unique_ptr<T>::release(void)
{
	unique_ptr	*tmp = ptr_;
	delete ptr_;
	return (tmp);
}

template <typename T>
T	*unique_ptr<T>::get(void) const
{
	return (ptr_);
}

template <typename T>
unique_ptr<T>::unique_ptr(void)
:ptr_(NULL)
{
	return ;
}

template <typename T>
unique_ptr<T>::unique_ptr(T *inPtr)
:ptr_(inPtr)
{
	return ;
}

template <typename T>
unique_ptr<T>::~unique_ptr(void)
{
	delete ptr_;
}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr &rhs)
:ptr_(rhs.release())
{
	return ;
}

template <typename T>
unique_ptr<T>	&unique_ptr<T>::operator=(unique_ptr &rhs)
{
	if (this != &rhs)
	{
		reset(rhs.release());
	}
	return (*this);
}

template <typename T>
unique_ptr<T>	&unique_ptr<T>::operator*(void) const
{
	return (*ptr_);
}

template <typename T>
unique_ptr<T>	*unique_ptr<T>::operator->(void) const
{
	return (ptr_);
}

} // end of namespace ft
