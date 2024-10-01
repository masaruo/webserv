#include "XXXBinary.hpp"

Binary::vec_bytes	Binary::fromStr(std::string const &str) const
{
	vec_bytes	bytes;
	std::string::const_iterator	iter = str.begin();
	std::string::const_iterator	end = str.end();

	while (iter != end)
	{
		bytes.push_back(static_cast<uint8_t>(*iter));
		iter++;
	}
	return (bytes);
}

Binary::Binary()
:data_()
{
	return ;
}

Binary::Binary(std::string const &str)
:data_(fromStr(str))
{
	return ;
}

Binary::Binary(vec_bytes const &bytes)
:data_(bytes)
{
	return ;
}

Binary::~Binary()
{
	return ;
}

Binary::Binary(Binary const &rhs)
:data_(rhs.data_)
{
	return ;
}

Binary &Binary::operator=(Binary const &rhs)
{
	if (this != &rhs)
	{
		data_ = rhs.data_;
	}
	return (*this);
}

Binary &Binary::operator<<(Binary const &rhs)
{
	if (this != &rhs)
	{
		data_.insert(data_.end(), rhs.data_.begin(), rhs.data_.end());
	}
	return (*this);
}

std::string	Binary::toStr(void) const
{
	std::string	str;
	const_iterator	iter = data_.begin();
	const_iterator	end = data_.end();

	while (iter != end)
	{
		str.push_back(static_cast<char>(*iter));
		iter++;
	}
	return (str);
}

Binary::vec_bytes	Binary::data(void) const
{
	return (data_);
}
