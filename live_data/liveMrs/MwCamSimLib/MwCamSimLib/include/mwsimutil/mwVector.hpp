// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWVECTOR_HPP_
#define MW_MWVECTOR_HPP_
#include "mwMathException.hpp"
#include "mwRealArray.hpp"

namespace cadcam
{
/// This struct represents a vector
template <class T, int nrelems>
struct mwVector
{
public:
	mwVector() {}

	/// Access element via index
	///
	/// Returns, for a given index, the element in the Vector
	///	@param index position of the element
	///	@returns a T
	T& operator[](const unsigned long& index) { return mArray[index]; }
	/// Indexer operator for const values
	///
	/// Returns, for a given index, the element in the Vector
	///	@param index position of the element
	///	@returns a T
	const T& operator[](const unsigned long& index) const { return mArray[index]; }
	/// += operator
	///
	/// Add vectors
	///	@param oth const reference to the other vector
	void operator+=(const mwVector<T, nrelems>& oth)
	{
		for (int r = 0; r < nrelems; ++r)
			mArray[r] += oth[r];
	}
	/// += operator
	///
	/// Add a scalar to each element of a vector
	///	@param oth const reference to the scalar of T type
	void operator+=(const T& oth)
	{
		for (int r = 0; r < nrelems; ++r)
			mArray[r] += oth;
	}
	/// -= operator
	///
	/// Subtract vectors
	///	@param oth const reference to the other vector
	void operator-=(const mwVector<T, nrelems>& oth)
	{
		for (int r = 0; r < nrelems; ++r)
			mArray[r] -= oth[r];
	}

	/// -= operator
	///
	/// Subtract a scalar from each element of a vector
	///	@param oth const reference to the scalar of T type
	void operator-=(const T& oth)
	{
		for (int r = 0; r < nrelems; ++r)
			mArray[r] -= oth;
	}


	/// *= operator
	///
	/// Multiply each element of a vector with a scalar
	///	@param oth const reference to the scalar of T type
	void operator*=(const T& oth)
	{
		for (int r = 0; r < nrelems; ++r)
		{
			mArray[r] *= oth;
		}
	}

	//// = operator
	///
	/// Divide each element of a vector by a scalar
	///	@param oth const reference to the scalar of T type
	void operator/=(const T& oth)
	{
		for (int r = 0; r < nrelems; ++r)
		{
			mArray[r] /= oth;
		}
	}
	const mwVector operator-(const mwVector& sec)
	{
		mwVector<T, nrelems> tmp;
		for (int i = 0; i < nrelems; ++i)
		{
			tmp[i] = (*this)[i] - sec[i];
		}
		return tmp;
	}

	bool operator==(const mwVector& rhs) const
	{
		for (int i = 0; i < nrelems; ++i)
		{
			if ((*this)[i] != rhs[i])
				return false;
		}
		return true;
	}

	bool operator!=(const mwVector& rhs) const { return !(*this == rhs); }

private:
	T mArray[nrelems];
};

}  // namespace cadcam
#endif  //	MW_MWVECTOR_HPP_
