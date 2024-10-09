#pragma once
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "define.hpp"
#include "HttpException.hpp"

namespace vm
{

template <typename K, typename V>
class VecMap
{
public:
	typedef std::vector<V>				valueVec_t;
	typedef std::map<K, valueVec_t>		vecmap_t;
	typedef vecmap_t::const_iterator	const_iterator;
	typedef vecmap_t::iterator			iterator;
	typedef vecmap_t::size_type			size_type;
	typedef vecmap_t::difference_type	difference_type;
	iterator		begin(void){ return (data_.begin(); )};
	iterator		end(void){ return (data_.end(); )};
	const_iterator	begin(void){ return (data_.begin(); )} const;
	const_iterator	end(void){ return (data_.end(); )} const;
private:
	vecmap_t	data_;

protected:
	vecmap_t	&getDataRef(void);
	void		assertHasKey(K const &key) const;
	void		assertHasValue(K const &key, V const &value) const;
public:
	VecMap();
	~VecMap();
	VecMap(VecMap const &rhs);
	VecMap &operator=(VecMap const &rhs);

	// setter
	virtual void	addValue(K const &key, V const &value);
	virtual void	removeValue(K const &key, V const &value);
	virtual void	removeKey(K const &key);

	// checker
	bool	hasKey(K const &rhs) const;
	bool	hasValue(K const &key, V const &value) const;

	// getter
	virtual valueVec_t	getVectorValue(K const &key) const;
	virtual V		getFirstValue(K const &key) const;
	virtual V		getLastValue(K const &key) const;
	vecmap_t		data(void) const;

	// exception
	class VecMapException : public std::runtime_error
	{
	public:
		VecMapException(std::string const &msg)
		:std::runtime_error(msg){ return; }
	};

	class VecMapHttpException : public HttpException
	{
	public:
		VecMapHttpException(std::string const &msg)
		:HttpException(msg){ return; }
	};
};

}// end of namespace ft

// #include "VecMap.tpp";

namespace vm
{

template <typename K, typename V>
VecMap<K, V>::VecMap()
:data_()
{
	return ;
}

template <typename K, typename V>
VecMap<K, V>::~VecMap()
{
	return ;
}

template <typename K, typename V>
VecMap<K, V>::VecMap(VecMap const &rhs)
:data_(rhs.data_)
{
	return ;
}

template <typename K, typename V>
VecMap<K, V>	&VecMap<K,V>::operator=(VecMap const &rhs)
{
	if (this != &rhs)
	{
		data_ = rhs.data_;
	}
	return (*this);
}

//* protected
template<typename K, typename V>
VecMap<K, V>::vecmap_t	&VecMap<K, V>::getDataRef(void)
{
	return (data_);
}

//* static helper func
template<typename K, typename V>
void	VecMap<K, V>::assertHasKey(K const &key) const
{
	if (!hasKey(key))
		throw (VecMapException("No key in the data."));
}

template<typename K, typename V>
void	VecMap<K, V>::assertHasValue(K const &key, V const &value) const
{
	assertHasKey(key);

	if (!hasValue(key, value))
		throw (VecMapException("No value with the key."));
}

//* setter
template<typename K, typename V>
void	VecMap<K, V>::addValue(K const &key, V const &value)
{
	data_[key].push_back(value);
}

template<typename K, typename V>
void	VecMap<K, V>::removeValue(K const &key, V const &value)
{
	assertHasValue(key, value);

	valueVec_t const &vec = data_[key];
	valueVec_t::iterator iter = std::find(vec.begin(), vec.end(), value);
	vec.erase(iter);

	if (vec.empty())
		removeKey(key);
}

template<typename K, typename V>
void	VecMap<K, V>::removeKey(K const &key)
{
	assertHasKey(key);

	data_.erase(key);
}

// *checker
template <typename K, typename V>
bool	VecMap<K, V>::hasKey(K const &key) const
{
	if (data_.find(key) != data_.end())
		return (true);
	else
		return (false);
}

template <typename K, typename V>
bool	VecMap<K, V>::hasValue(K const &key, V const &value) const
{
	assertHasKey(key);

	valueVec_t					vec = data_[key];
	valueVec_t::const_iterator	iter = std::find(vec.begin(), vec.end(), value);
	if (iter != vec.end())
		return (true);
	else
		return (false);
}

//* getter
template<typename K, typename V>
VecMap<K, V>::valueVec_t	VecMap<K, V>::getVectorValue(K const &key) const
{
	assertHasKey(key);

	return (data_[key]);
}

template<typename K, typename V>
V	VecMap<K, V>::getFirstValue(K const &key) const
{
	assertHasValue(key, value);

	return (data_[key].at(0));
}

template<typename K, typename V>
V	VecMap<K, V>::getLastValue(K const &key) const
{
	assertHasValue(key, value);

	return (data_[key].at(data_[key].size() - 1));
}

template<typename K, typename V>
VecMap<K, V>::vecmap_t	VecMap<K, V>::data(void) const
{
	return (data_);
}

}// end of namespace vm
