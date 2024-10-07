#include "StrVecMap.hpp"
#include "string.hpp"
#include <limits>
#include <algorithm>

svm::StrVecMap::StrVecMap()
{
	return ;
}

svm::StrVecMap::~StrVecMap()
{
	return ;
}

svm::StrVecMap::StrVecMap(StrVecMap const &rhs)
:data_(rhs.data_)
{
	return ;
}

svm::StrVecMap &svm::StrVecMap::operator=(StrVecMap const &rhs)
{
	if (this != &rhs)
	{
		data_ = rhs.data_;
	}
	return (*this);
}

void	svm::StrVecMap::setElem(std::string const &key, std::string const &value)
{
	ft::string	ftKey(key);
	ftKey.to_lower();
	data_[ftKey].push_back(value);
}

void	svm::StrVecMap::setElem(std::string const &line)
{
	ft::string					ftLine(line);
	ft::string::string_vector	split_by_delims = ftLine.split(":");
	std::string					key = "";
	ft::string::string_vector_const_iterator iter = split_by_delims.begin();
	ft::string::string_vector_const_iterator end = split_by_delims.end();
	
	if (iter != end)
	{
		if (iter == split_by_delims.begin())
			key = *iter;
		else
		{
			setElem(key, *iter);
		}
		iter++;
	}
}

ft::str_vec	svm::StrVecMap::getValueVector(std::string const &key) const
{
	ft::str_vec strVec;

	if (hasElem(key))
		strVec = data_.at(key);

	return (strVec);
}

std::string	svm::StrVecMap::getValueAtFirst(std::string const &key) const
{
	ft::str_vec strVec = getValueVector(key);

	if (strVec.empty())
		return ("");
	else
		return (strVec.at(0));
}

std::string	svm::StrVecMap::getValueAtLast(std::string const &key) const
{
	ft::str_vec strVec = getValueVector(key);

	if (strVec.empty())
		return ("");
	else
		return (strVec.at(strVec.size() - 1));
}

std::size_t	svm::StrVecMap::getIndex(std::string const &key, std::string const &value) const
{
	ft::str_vec const	strVec = getValueVector(key);
	ft::str_vec::const_iterator	iter = strVec.begin();
	ft::str_vec::const_iterator	end = strVec.end();
	ft::str_vec::size_type		index = std::numeric_limits<std::size_t>::max();

	if (strVec.empty())
		return (index);

	iter = std::find(strVec.begin(), end, value);

	if (iter != end)
	{
		index = std::distance(strVec.begin(), iter);
	}
	return (index);
}

svm::StrVecMap::map_vec_t const	&svm::StrVecMap::data(void) const
{
	return (data_);
}

bool	svm::StrVecMap::hasElem(std::string const &key) const
{
	ft::string	ftKey(key);
	ftKey.to_lower();

	if (data_.find(ftKey) != data_.end())
		return (true);
	else
		return (false);
}

bool	svm::StrVecMap::hasValue(std::string const &key, std::string const &value) const
{
	std::size_t const	index = getIndex(key, value);

	if (index == std::numeric_limits<std::size_t>::max())
		return (false);
	else
		return (true);
}

svm::StrVecMap::StrVecMapException::StrVecMapException(std::string const &msg)
:std::runtime_error(msg)
{
	return ;
}
