// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWCLAMPEDVALUE_HPP_
#define MW_MWCLAMPEDVALUE_HPP_
#include "mwRangeException.hpp"
#include <limits>


namespace misc
{
template<class T> class mwClampedValue;
template<class Archive, class T>
void serialize(Archive& ar, misc::mwClampedValue<T>& cv, unsigned int);
//!This class represents a clamped value.
template <class T>
class MW_5AXUTIL_API mwClampedValue
{
	template<class Archive, class Ty>
	friend void serialize(Archive& ar, misc::mwClampedValue<Ty>& cv, unsigned int);

public:
	//!Default constructor
	inline mwClampedValue();

	//!Constructor
	/*!Constructor with given parameters:
		\param	min	const reference to a min value
		\param	max	const reference to a max value
	*/
	inline mwClampedValue(const T& min, const T& max);

	//!Constructor
	/*!Constructor with given parameters:
		\param	min	const reference to 
		\param	max	const reference to 
		\param	value const reference to 
	*/
	inline mwClampedValue(const T& min, const T& max, const T& value);

	//!Get min value
	/*!Get min value
		\return const reference to min value
	*/
	const T& GetMinValue() const;

	//!Get max value
	/*!Get max value
		\return const reference to max value
	*/
	const T& GetMaxValue() const;

	//!Get value
	/*!Get value
		\return const reference to value
	*/
	const T& GetValue() const;

	//!Set min value
	/*!Set min value
		\param min const reference to min value
	*/
	void SetMinValue(const T& min);

	//!Set max value
	/*!Set max value
		\param max const reference to max value
	*/
	void SetMaxValue(const T& max);

	//!Set value
	/*!Set value
		\param value const reference to value
	*/
	void SetValue(const T& value);

	//!Assigment oeprator
	/*!Assigns one value object to another
		If the value isn't within allowed range	an exception will be thrown.
		\param tc value to copy the information from
		\returns current value with copied information
	*/
	void operator=(const T& tc);

	bool operator==(const mwClampedValue<T>& tc) const;

private:
	T m_min;
	T m_max;
	T m_value;
};

template <class T>
inline mwClampedValue<T>::mwClampedValue():
	m_min(-(std::numeric_limits<T>::max)()),
	m_max((std::numeric_limits<T>::max)()),
	m_value(0)
{
}

template <class T>
inline mwClampedValue<T>::mwClampedValue(const T& min, const T& max):
	m_min(min),
	m_max(max)
{
}

template <class T>
inline mwClampedValue<T>::mwClampedValue(const T& min, const T& max, const T& value):
	m_min(min),
	m_max(max),
	m_value(value)
{
}

template <class T>
inline const T& mwClampedValue<T>::GetMinValue() const
{
	return m_min;
}

template <class T>
inline const T& mwClampedValue<T>::GetMaxValue() const
{
	return m_max;
}

template <class T>
inline const T& mwClampedValue<T>::GetValue() const
{
	return m_value;
}

template <class T>
inline void mwClampedValue<T>::SetMinValue(const T& min)
{
	m_min = min;
}

template <class T>
inline void mwClampedValue<T>::SetMaxValue(const T& max)
{
	m_max = max;
}

template <class T>
inline void mwClampedValue<T>::SetValue(const T& value)
{
	if(value < m_min || value > m_max)
		throw misc::mwRangeException<T>(m_min, m_max, value);

	m_value = value;
}

template <class T>
inline void mwClampedValue<T>::operator=(const T& tc)
{
	if(tc < m_min || tc > m_max)
		throw misc::mwRangeException<T>(m_min, m_max, tc);

	m_value = tc;
}

template <class T>
inline bool mwClampedValue<T>::operator==(const mwClampedValue<T>& tc) const
{
	return m_min == tc.m_min
		&& m_max == tc.m_max
		&& m_value == tc.m_value;
}
}  // namespace misc
#endif	//	MW_MWCLAMPEDVALUE_HPP_
