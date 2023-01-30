// (C) 2018-2019 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWOPTIONAL_HPP_
#define MW_MWOPTIONAL_HPP_
#include "mwException.hpp"

namespace misc
{

// This struct is the nullOpt for mwOptional
struct mwNullOpt
{
	inline mwNullOpt() {}
};

// This class contains a restricted part of the functionality of optional, securing uninitialized
// access with misc::mwException
template<typename T>
class mwOptional
{
public:
	mwOptional()
		: m_hasValue(false)
		, m_value(T())
	{}

	mwOptional(mwNullOpt)
		: m_hasValue(false)
		, m_value(T())
	{}

	mwOptional(const T& value)
		: m_hasValue(true)
		, m_value(value)
	{}

	bool HasValue() const
	{
		return m_hasValue;
	}

	const T& GetValue() const
	{
		if (!m_hasValue)
		{
			throw misc::mwException(0, _T("Accessing empty misc::optional"));
		}
		return m_value;
	}

	T& GetValue()
	{
		if (!m_hasValue)
		{
			throw misc::mwException(0, _T("Accessing empty misc::optional"));
		}
		return m_value;
	}

	const T& GetValueOr(const T& value) const
	{
		return m_hasValue ? m_value : value;
	}

private:
	bool m_hasValue;
	T m_value;
};

template<typename T>
bool operator==(const mwNullOpt&, const mwOptional<T>& rhs)
{
	return !rhs.HasValue();
}
template<typename T>
bool operator==(const mwOptional<T>& lhs, const mwNullOpt&)
{
	return !lhs.HasValue();
}

template<typename T>
bool operator==(const mwOptional<T>& lhs, const mwOptional<T>& rhs)
{
	if (lhs.HasValue())
		return rhs.HasValue() ? lhs.GetValue() == rhs.GetValue() : false;
	else
		return !rhs.HasValue();
}

template<typename T>
bool operator==(const T& lhs, const mwOptional<T>& rhs)
{
	return rhs.HasValue() ? lhs == rhs.GetValue() : false;
}

template<typename T>
bool operator==(const mwOptional<T>& lhs, const T& rhs)
{
	return lhs.HasValue() ? lhs.GetValue() == rhs : false;
}


template<typename T>
bool operator!=(const mwNullOpt&lhs , const mwOptional<T>& rhs)
{
	return !(lhs == rhs);
}
template<typename T>
bool operator!=(const mwOptional<T>& lhs, const mwNullOpt& rhs)
{
	return !(lhs == rhs);
}

template<typename T>
bool operator!=(const mwOptional<T>& lhs, const mwOptional<T>& rhs)
{
	return !(lhs == rhs);
}

template<typename T>
bool operator!=(const T& lhs, const mwOptional<T>& rhs)
{
	return !(lhs == rhs);
}

template<typename T>
bool operator!=(const mwOptional<T>& lhs, const T& rhs)
{
	return !(lhs == rhs);
}


// Returns the result of transform(value) if a value is present, otherwise returns fallback
template<typename T, typename Result, typename Transform>
inline Result Match(const mwOptional<T>& opt, const Transform& transform, const Result& fallback)
{
	if (opt.HasValue())
	{
		return transform(opt.GetValue());
	}
	else
	{
		return fallback;
	}
}

// Calls action(value) if a value is present, otherwise does nothing
template<typename T, typename Action>
inline void Match(const mwOptional<T>& opt, const Action& action)
{
	if (opt.HasValue())
	{
		action(opt.GetValue());
	}
}

// Bind function for the optional monad
template<typename T, typename Transform>
inline mwOptional<T> Bind(const mwOptional<T>& opt, const Transform& transform)
{
	return Match(opt, transform, mwOptional<T>());
}

// Bind operator for the optional monad
template<typename T, typename Transform>
inline mwOptional<T> operator>>(const mwOptional<T>& option, const Transform& transform)
{
	return option.Bind(transform);
}

} // namespace misc
#endif	//	MW_MWOPTIONAL_HPP_
