#pragma once
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include "define.hpp"

namespace svm
{

class StrVecMap
{
public:
	typedef std::map<std::string, std::vector<std::string> >	map_vec_t;
	typedef map_vec_t::iterator									iterator;
	typedef map_vec_t::const_iterator							const_iterator;
	typedef map_vec_t::size_type								size_type;
	typedef map_vec_t::difference_type							difference_type;
private:
	map_vec_t	data_;
protected:
	void			setElem(std::string const &key, std::string const &value);
	virtual void	setElem(std::string const &line);
public:
	StrVecMap();
	virtual ~StrVecMap();
	StrVecMap(StrVecMap const &rhs);
	StrVecMap &operator=(StrVecMap const &rhs);
	ft::str_vec			getValue(std::string const &key) const;
	std::string			getValueAtFirst(std::string const &key) const;
	std::string			getValueAtLast(std::string const &key) const;
	std::size_t			getIndex(std::string const &key, std::string const &value) const;
	map_vec_t			data(void) const;
	bool				hasElem(std::string const &key) const;
	bool				hasValue(std::string const &key, std::string const &value) const;

	class StrVecMapException : public std::runtime_error
	{
	public:
		StrVecMapException(std::string const &msg);
	};
};

}//end of namespace vm
