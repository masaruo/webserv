#ifndef VEC_MAP_HPP
#define VEC_MAP_HPP
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
	typedef std::vector<V>						valueVec_t;
	typedef std::map<K, valueVec_t>				vecmap_t;
	typedef typename vecmap_t::const_iterator	const_iterator;
	typedef typename vecmap_t::iterator			iterator;
	typedef typename vecmap_t::size_type		size_type;
	typedef typename vecmap_t::difference_type	difference_type;
	iterator		begin(void){ return (data_.begin()); }
	iterator		end(void){ return (data_.end()); }
	const_iterator	cbegin(void) const { return (data_.begin()); }
	const_iterator	cend(void) const { return (data_.end()); }
private:
	vecmap_t	data_;

protected:
	vecmap_t	&getDataRef(void);
	void		assertHasKey(K const &key) const;
	void		assertHasValue(K const &key, V const &value) const;
public:
	VecMap();
	virtual ~VecMap();
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
	virtual	valueVec_t	at(K const &key) const;
	virtual valueVec_t	getValueVector(K const &key) const;
	virtual V			getFirstValue(K const &key) const;
	virtual V			getLastValue(K const &key) const;
	virtual V			getValueAtIdx(K const &key, std::size_t idx) const;
	virtual std::size_t	getIdxOfValue(K const &key, V const &value) const;
	vecmap_t			data(void) const;
	typename vecmap_t::size_type	size(void) const;

	// exception
	class VecMapException : public std::runtime_error
	{
	public:
		explicit VecMapException(std::string const &msg)
		:std::runtime_error(msg){ return; }
	};

};

}// end of namespace ft

#include "VecMap.tpp"

#endif
