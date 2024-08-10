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
#include <cstddef>

/**
 * @file unique_ptr.hpp
 * @brief C++98標準に準拠した独自のユニークポインタ実装
 */
namespace ft
{
/**
 * @brief 単一の所有権を持つスマートポインタ
 *
 * このクラスは、動的に割り当てられたオブジェクトの単一の所有権を管理します。
 * リソースは自動的に解放され、コピーは禁止されていますが、所有権の移動は可能です。
 *
 * @tparam T 管理対象のオブジェクトの型
 */
template <typename T>
class unique_ptr
{
private:
	T	*ptr_;
	unique_ptr &operator=(unique_ptr const &rhs){ (void) rhs; return (*this); }// hidden
	unique_ptr(unique_ptr const &rhs){ return ;}
public:
	unique_ptr();
	explicit unique_ptr(T *inPtr);
	~unique_ptr();
	unique_ptr(unique_ptr &rhs);
	unique_ptr &operator=(unique_ptr &rhs);
	/**
	* @brief デリファレンス演算子
	* @return T& 管理対象オブジェクトへの参照
	*/
	T &operator*(void) const;
	/**
	 * @brief メンバアクセス演算子
	 *
	 * @return T* 管理対象オブジェクトへのポインタ
	*/
	T *operator->(void) const;

	// class functions
	/**
	 * @brief 管理しているポインタを取得
	 *
	 * @return T* 管理対象オブジェクトへのポインタ
	*/
	T		*get(void) const;

	/**
	 * @brief 管理しているポインタをリセット
	 *
	 * 現在のリソースを解放し、新しいポインタを設定します。
	 * 現在のリソースと新しいポインタが同じでない場合のみ、
	 * 現在のリソースは削除されます。
	 *
	 * @param inPtr 新しく管理対象とするポインタ（デフォルトはNULL）
	 */
	void	reset(T *inPtr = NULL);

	/**
	 * @brief 管理しているポインタの所有権を放棄
	 *
	 * ポインタの所有権を放棄し、内部ポインタをNULLに設定します。
	 * このメソッドはリソースを解放しません。返されたポインタは
	 * 呼び出し元が適切に管理（必要に応じて解放）する必要があります。
	 *
	 * @return T* 以前管理していたポインタ
	 */
	T		*release(void);
};

template <typename T>
void	unique_ptr<T>::reset(T *inPtr)
{
	T	*old;
	old = ptr_;
	ptr_ = inPtr;
	delete old;
}

template <typename T>
T	*unique_ptr<T>::release(void)
{
	T *tmp = ptr_;
	ptr_ = NULL;
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
T	&unique_ptr<T>::operator*(void) const
{
	return (*ptr_);
}

template <typename T>
T	*unique_ptr<T>::operator->(void) const
{
	return (ptr_);
}

} // end of namespace ft

/**
 * @brief unique_ptrの使用例
 *
 * @code
 * // unique_ptrの作成
 * ft::unique_ptr<int> ptr1(new int(42));
 *
 * // リソースへのアクセス
 * int value = *ptr1;
 * 
 * // 所有権の移動
 * ft::unique_ptr<int> ptr2 = ptr1;  // ptr1はNULLになる
 * 
 * // リセット
 * ptr2.reset(new int(10));
 *
 * // リソースの解放
 * int* raw_ptr = ptr2.release();
 * delete raw_ptr;
 * 
 * or
 * 
 * ptr1.reset();
 * @endcode
 */
