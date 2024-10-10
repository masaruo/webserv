#ifndef VEC_MAP_TPP
#define VEC_MAP_TPP

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
typename VecMap<K, V>::vecmap_t	&VecMap<K, V>::getDataRef(void)
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

	valueVec_t						&vec = data_[key];
	typename valueVec_t::iterator	iter = std::find(vec.begin(), vec.end(), value);
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

	std::size_t const	size = getIdxOfValue(key, value);
	if (size == 0)
		return (false);
	else
		return (true);
}

//* getter
template<typename K, typename V>
typename VecMap<K, V>::valueVec_t	VecMap<K, V>::at(K const &key) const
{
	assertHasKey(key);
	const_iterator iter = data_.find(key);
	if (iter != data_.end())
		return (iter->second);
}

template<typename K, typename V>
typename VecMap<K, V>::valueVec_t	VecMap<K, V>::getValueVector(K const &key) const
{
	return (at(key));
}

template<typename K, typename V>
V	VecMap<K, V>::getFirstValue(K const &key) const
{
	assertHasKey(key);
	valueVec_t	const &val = getValueVector(key);
	if (val.empty())
		throw (VecMapException("No value with the key."));
	return (val.front());
}

template<typename K, typename V>
V	VecMap<K, V>::getLastValue(K const &key) const
{
	assertHasKey(key);
	valueVec_t	const &val = getValueVector(key);
	if (val.empty())
		throw (VecMapException("No value with the key."));
	return (val.back());
}

template<typename K, typename V>
V	VecMap<K, V>::getValueAtIdx(K const &key, std::size_t idx) const
{
	assertHasKey(key);
	valueVec_t	const &val = getValueVector(key);
	if (val.empty())
		throw (VecMapException("No value with the key."));
	if (idx > val.size())
		throw (VecMapException("Idx larger than size of key vector."));
	return (val.at(idx));
}

template<typename K, typename V>
std::size_t	VecMap<K, V>::getIdxOfValue(K const &key, V const &value) const
{
	assertHasKey(key);

	valueVec_t const					&vec = getValueVector(key);
	typename valueVec_t::const_iterator	iter = std::find(vec.begin(), vec.end(), value);
	if (iter != vec.end())
		return (std::distance(vec.begin(), iter) + 1);
	else
		return (0);

}

template<typename K, typename V>
typename VecMap<K, V>::vecmap_t	VecMap<K, V>::data(void) const
{
	return (data_);
}

}// end of namespace vm

#endif
