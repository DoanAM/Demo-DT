// (C) 2017-2021 by ModuleWorks GmbH
// Owner: 5Axis Application

#ifndef MW_MWTPOINTDATA_HPP_
#define MW_MWTPOINTDATA_HPP_

#include "mwAutoPointer.hpp"
#include "mwTPoint3d.hpp"

namespace cadcam
{
/// This struct represents a 3d point with extra data, to be used in the mesh as TVertex or
/// TFaceNormal.
template <typename T, typename TData>
class MW_5AXUTIL_API mwTPointData
{
public:
	typedef mwTPointData<T, TData> MyType;
	typedef typename misc::mwAutoPointer<MyType> Ptr;

	mwTPointData(const T first, const T second, const T third);
	mwTPointData(const T first, const T second, const T third, const TData& data);
	explicit mwTPointData(const mwTPoint3d<T>& point);
	explicit mwTPointData(const mwTPoint3d<T>& point, const TData& data);
	mwTPointData();
	mwTPointData(const mwTPointData& tc);
	virtual ~mwTPointData();
	mwTPointData& operator=(const mwTPointData& tc);
	bool operator==(const mwTPointData& tc) const;
	bool AreCoordinatesEqual(const mwTPointData& tc, const T prec = mathdef::mw_tol(T())) const;
	bool operator!=(const mwTPointData& tc) const;
	void x(const T newx);
	void y(const T newy);
	void z(const T newz);
	T x() const;
	T y() const;
	T z() const;
	operator const T*() const;
	operator T*();
	void operator+=(const MyType& ta);
	void operator-=(const MyType& ta);
	void operator+=(const mwTPoint3d<T>& ta);
	void operator-=(const mwTPoint3d<T>& ta);
	T Length2() const;
	T operator~() const;
	void operator*=(const T& scFactor);
	void operator/=(const T& scFactor);
	const MyType& Normalize();
	MyType Normalized() const;
	virtual T GetDistance(const mwTPoint3d<T>& p) const;
	bool IsTolerant(const mwTPoint3d<T>& p) const;
	bool IsTolerant(const mwTPoint3d<T>& p, T factor) const;
	void Transform(const mwMatrix<T, 4, 4>& homomatrix);
	void Transform3d(const mwMatrix<T, 3, 3>& matrix, const mwTPoint3d<T>& translation);
	MyType operator-();
	MyType operator+(const MyType& toAdd) const;
	MyType operator-(const MyType& toSub) const;
	MyType operator+(const mwTPoint3d<T>& toAdd) const;
	MyType operator-(const mwTPoint3d<T>& toSub) const;
	MyType operator*(const T factor) const;
	MyType operator/(const T factor) const;
	MyType operator*(const MyType& toMult) const;
	MyType operator%(const MyType& toMult) const;
	const mwTPoint3d<T>& GetPoint() const;
	void SetPoint(const mwTPoint3d<T>& point);
	const TData& GetData() const;
	TData& GetData();
	TData m_Data;

private:
	void Copy(const mwTPointData& tc);
	mwTPoint3d<T> m_Point;
};

/// Copy point
template <typename T, typename TData>
inline void mwTPointData<T, TData>::Copy(const mwTPointData& tc)
{
	m_Point.x(tc.x());
	m_Point.y(tc.y());
	m_Point.z(tc.z());
	m_Data = tc.m_Data;
}
/// Getter m_Data
///
/// Getter for the m_Data
/// @returns & const on m_Data
template <typename T, typename TData>
inline TData& mwTPointData<T, TData>::GetData()
{
	return m_Data;
}
/// Getter m_Data
///
/// Getter for the m_Data
/// @returns & const on m_Data
template <typename T, typename TData>
inline const TData& mwTPointData<T, TData>::GetData() const
{
	return m_Data;
}
/// Setter m_Point
///
/// Setter for the m_Point
/// @param point & const 3d point
template <typename T, typename TData>
inline void mwTPointData<T, TData>::SetPoint(const mwTPoint3d<T>& point)
{
	m_Point.x(point.x());
	m_Point.y(point.y());
	m_Point.z(point.z());
}
/// Getter m_Point
///
/// Getter for the m_Point
/// @returns & const 3d point
template <typename T, typename TData>
inline const mwTPoint3d<T>& mwTPointData<T, TData>::GetPoint() const
{
	return m_Point;
}

/// Cross (vector) product of to 3d points
/// @param toMult const reference to a 3d point
/// @returns const 3d point
template <typename T, typename TData>
inline typename mwTPointData<T, TData>::MyType mwTPointData<T, TData>::operator%(
	const MyType& toMult) const
{
	MyType ret = *this;
	ret.m_Point = ret.m_Point % toMult.m_Point;
	return ret;
}

/// Scalar(Dot) product of to 3d points.
/// @param toMult const reference to a 3d point
/// @returns const scalar
template <typename T, typename TData>
inline typename mwTPointData<T, TData>::MyType mwTPointData<T, TData>::operator*(
	const MyType& toMult) const
{
	MyType ret = *this;
	ret.m_Point *= toMult;
	return ret;
}

/// Divide each 3d component with a factor.
/// @param factor const reference to a factor to divide with
/// @returns new 3d point object
template <typename T, typename TData>
inline typename mwTPointData<T, TData>::MyType mwTPointData<T, TData>::operator/(
	const T factor) const
{
	MyType ret = *this;
	ret.m_Point /= factor;
	return ret;
}


/// Multiply each 3d component with a factor.
/// @param factor const reference to a factor to multiply with
/// @returns new 3d point object
template <typename T, typename TData>
inline typename mwTPointData<T, TData>::MyType mwTPointData<T, TData>::operator*(
	const T factor) const
{
	MyType ret = *this;
	ret.m_Point *= factor;
	return ret;
}

/// Subtract each 3d point component from a data 3d point
/// @param toSub const reference of a 3d point
/// @returns subtracted const 3d point
template <typename T, typename TData>
inline typename mwTPointData<T, TData>::MyType mwTPointData<T, TData>::operator-(
	const mwTPoint3d<T>& toSub) const
{
	MyType ret = *this;
	ret -= toSub;
	return ret;
}

/// Add each component of a 3d point to a data 3d point
/// @param toAdd const reference of a data 3d point
/// @returns added const 3d point
template <typename T, typename TData>
inline typename mwTPointData<T, TData>::MyType mwTPointData<T, TData>::operator+(
	const mwTPoint3d<T>& toAdd) const
{
	MyType ret = *this;
	ret += toAdd;
	return ret;
}

/// Subtract each 3d point component from another
/// @param toSub const reference of a 3d point
/// @returns subtracted const 3d point
template <typename T, typename TData>
inline typename mwTPointData<T, TData>::MyType mwTPointData<T, TData>::operator-(
	const MyType& toSub) const
{
	MyType ret = *this;
	ret -= toSub;
	return ret;
}

/// Add each component of a 3d point to another
/// @param toAdd const reference of a data 3d point
/// @returns added const 3d point
template <typename T, typename TData>
inline typename mwTPointData<T, TData>::MyType mwTPointData<T, TData>::operator+(
	const MyType& toAdd) const
{
	MyType ret = *this;
	ret += toAdd;
	return ret;
}

/// Change the sign of the point
/// @returns opposite const 3d point
template <typename T, typename TData>
inline typename mwTPointData<T, TData>::MyType mwTPointData<T, TData>::operator-()
{
	return MyType(-m_Point.x(), -m_Point.y(), -m_Point.z());
}
/// Transform
///
/// @param matrix const ref to a <3,3> rotation matrix
/// @param translation const ref to a translation
template <typename T, typename TData>
inline void mwTPointData<T, TData>::Transform3d(
	const mwMatrix<T, 3, 3>& matrix, const mwTPoint3d<T>& translation)
{
	m_Point.Transform3d(matrix, translation);
}
/// Transform
///
/// @param homomatrix const ref to a transformation matrix
template <typename T, typename TData>
inline void mwTPointData<T, TData>::Transform(const mwMatrix<T, 4, 4>& homomatrix)
{
	m_Point.Transform(homomatrix);
}
/// Check if the distance between two point is less than a specified tolerance.
/// @param p of type Point
/// @param factor of type T
/// @returns IsTolerant of type bool
template <typename T, typename TData>
inline bool mwTPointData<T, TData>::IsTolerant(const mwTPoint3d<T>& p, T factor) const
{
	return GetDistance(p) < factor;
}
/// Check if the distance between two point is less than a tolerance.
///
///	@param p of type Point
///	@returns IsTolerant of type bool
template <typename T, typename TData>
inline bool mwTPointData<T, TData>::IsTolerant(const mwTPoint3d<T>& p) const
{
	return IsTolerant(p, mathdef::mw_tol(T()));
}
/// Compute distance to another point
///
///	@param p of type PointPtr
///	@returns GetDistance of type virtual T
template <typename T, typename TData>
inline T mwTPointData<T, TData>::GetDistance(const mwTPoint3d<T>& p) const
{
	return ~(*this - p);
}
/// Compute normalized point
///
/// @returns normalized vector (3d point)
/// @throws exception if the point is 0.
template <typename T, typename TData>
inline typename mwTPointData<T, TData>::MyType mwTPointData<T, TData>::Normalized() const
{
	return m_Point.Normalized();
}
/// Normalize the point
///
/// Normalize this vector (3d point).
/// @throws exception if the point is 0.
template <typename T, typename TData>
inline const typename mwTPointData<T, TData>::MyType& mwTPointData<T, TData>::Normalize()
{
	m_Point.Normalize();
	return *this;
}

/// Divide each 3d component with a factor
/// @param scFactor const reference to a factor
template <typename T, typename TData>
inline void mwTPointData<T, TData>::operator/=(const T& scFactor)
{
	m_Point /= scFactor;
}

/// Multiply each 3d component with a factor
/// @param scFactor const reference to a factor
template <typename T, typename TData>
inline void mwTPointData<T, TData>::operator*=(const T& scFactor)
{
	m_Point *= scFactor;
}

/// Returns length of the vector represented by the 3d data point
/// @returns constant length of the vector represented by the 3d data point.
template <typename T, typename TData>
inline T mwTPointData<T, TData>::operator~() const
{
	return ~m_Point;
}
/// Squared length
///
/// Returns squared length of the vector represented by the 3d point
/// @returns constant length of the vector represented by the 3d point.
template <typename T, typename TData>
inline T mwTPointData<T, TData>::Length2() const
{
	return m_Point.Length2();
}

/// Subtract each component of a 3d point to a data  3d point
/// @param ta const reference of a data 3d point
template <typename T, typename TData>
inline void mwTPointData<T, TData>::operator-=(const mwTPoint3d<T>& ta)
{
	m_Point -= ta;
}

/// Add each component of a 3d point to a data  3d point
/// @param ta const reference of a data 3d point
template <typename T, typename TData>
inline void mwTPointData<T, TData>::operator+=(const mwTPoint3d<T>& ta)
{
	m_Point += ta;
}

/// Subtract each component of a data 3d point with another
/// @param ta const reference of a data 3d point
template <typename T, typename TData>
inline void mwTPointData<T, TData>::operator-=(const MyType& ta)
{
	m_Point -= ta.m_Point;
}

/// Add each component of a data 3d point to another
/// @param ta const reference of a data 3d point
template <typename T, typename TData>
inline void mwTPointData<T, TData>::operator+=(const MyType& ta)
{
	m_Point += ta.m_Point;
}
/// Get 3d point
///
/// Gets a pointer to the 3d point array.
/// @returns pointer to the 3d point array
template <typename T, typename TData>
inline mwTPointData<T, TData>::operator T*()
{
	return static_cast<T*>(m_Point);
}
/// Get 3d point
///
/// Gets a pointer to the 3d point array.
/// @returns constant pointer to the 3d point array
template <typename T, typename TData>
inline mwTPointData<T, TData>::operator const T*() const
{
	return (const T*)m_Point;
}
/// Get z-coordinate
///
/// Gets the z-coordinate of the 3d point as a reference.
/// @returns constant reference to the z-coordinate
template <typename T, typename TData>
inline T mwTPointData<T, TData>::z() const
{
	return m_Point.z();
}
/// Get y-coordinate
///
/// Gets the y-coordinate of the 3d point as a reference.
/// @returns constant reference to the y-coordinate
template <typename T, typename TData>
inline T mwTPointData<T, TData>::y() const
{
	return m_Point.y();
}
/// Get x-coordinate
///
/// Gets the x-coordinate of the 3d point as a reference.
/// @returns constant reference to the x-coordinate
template <typename T, typename TData>
inline T mwTPointData<T, TData>::x() const
{
	return m_Point.x();
}
/// Set 3d point
///
/// Sets new z-coordinate of the 3d point.
/// @param newz const z-coordinate of the 3d point
template <typename T, typename TData>
inline void mwTPointData<T, TData>::z(const T newz)
{
	m_Point.z(newz);
}
/// Set 3d point
///
/// Sets new y-coordinate of the 3d point.
/// @param newy const y-coordinate of the 3d point
template <typename T, typename TData>
inline void mwTPointData<T, TData>::y(const T newy)
{
	m_Point.y(newy);
}
/// Set 3d point
///
/// Sets new x-coordinate of the 3d point.
/// @param newx const x-coordinate of the 3d point
template <typename T, typename TData>
inline void mwTPointData<T, TData>::x(const T newx)
{
	m_Point.x(newx);
}

/// Are given data points not equal?
/// @param tc tool to compare the current tool with
/// @returns <b>false</b> if both contain the same parameters,
/// <b>true</b> otherwise
template <typename T, typename TData>
inline bool mwTPointData<T, TData>::operator!=(const mwTPointData& tc) const
{
	return !((*this) == tc);
}
/// Check for equality with tolerance
///
/// Are given data points equal?
/// @param tc data point to compare the current data point with
/// @param prec precision to use for check
/// @returns <b>true</b> if they are equal within tolerance,
/// <b>false</b> otherwise
template <typename T, typename TData>
inline bool mwTPointData<T, TData>::AreCoordinatesEqual(
	const mwTPointData& tc, const T prec /*= mathdef::mw_tol(T())*/) const
{
	return mathdef::is_eq(x(), tc.x(), prec) && mathdef::is_eq(y(), tc.y(), prec) &&
		mathdef::is_eq(z(), tc.z(), prec) && m_Data == tc.m_Data;
}

/// Are given data points equal?
/// @param tc data point to compare the current data point with
/// @returns <b>true</b> if they are equal,
/// <b>false</b> otherwise
template <typename T, typename TData>
inline bool mwTPointData<T, TData>::operator==(const mwTPointData& tc) const
{
	return x() == tc.x() && y() == tc.y() && z() == tc.z() && m_Data == tc.m_Data;
}

/// Assigns one 3d point object to another
/// @param tc tool to copy the information from
/// @returns current 3d point with copied information
template <typename T, typename TData>
inline mwTPointData<T, TData>& mwTPointData<T, TData>::operator=(const mwTPointData& tc)
{
	if (this != &tc)
	{
		Copy(tc);
	}
	return *this;
}
/// Destructor
template <typename T, typename TData>
inline mwTPointData<T, TData>::~mwTPointData()
{
}
/// Copy constructor
///
/// Creates a exact copy of a given mwTPointData
/// @param tc tool to create a copy of
template <typename T, typename TData>
inline mwTPointData<T, TData>::mwTPointData(const mwTPointData& tc)
{
	Copy(tc);
}

/// Default constructor
///
/// Point is set to origin, data is default constructed
template <typename T, typename TData>
inline mwTPointData<T, TData>::mwTPointData()
{
}

/// Constructor setting point and data
template <typename T, typename TData>
inline mwTPointData<T, TData>::mwTPointData(const mwTPoint3d<T>& point, const TData& data)
	: m_Point(point), m_Data(data)
{
}

/// Constructor setting point and default constructing data
template <typename T, typename TData>
inline mwTPointData<T, TData>::mwTPointData(const mwTPoint3d<T>& point): m_Point(point)
{
}

/// Constructor setting point coordinates and data
template <typename T, typename TData>
inline mwTPointData<T, TData>::mwTPointData(
	const T first, const T second, const T third, const TData& data)
	: m_Point(first, second, third), m_Data(data)
{
}

/// Constructor setting point coordinates and default constructing data
template <typename T, typename TData>
inline mwTPointData<T, TData>::mwTPointData(const T first, const T second, const T third)
	: m_Point(first, second, third)
{
}

/// negate each coordinate
/// @param ta point to negate
/// @returns negated point
template <class T, class TData>
inline mwTPointData<T, TData> operator-(const mwTPointData<T, TData>& ta)
{
	return mwTPointData<T, TData>(-ta.x(), -ta.y(), -ta.z());
}
}  // namespace cadcam
#endif  //	MW_MWTPOINTDATA_HPP_
