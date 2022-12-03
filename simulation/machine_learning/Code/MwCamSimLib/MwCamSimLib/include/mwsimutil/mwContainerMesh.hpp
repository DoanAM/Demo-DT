// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCONTAINERMESH_HPP_
#define MW_MWCONTAINERMESH_HPP_
#include "mw3dBoundingBox.hpp"
#include "mw3dGeometry.hpp"
#include "mwCachingInternalDefs.hpp"
#include "mwDefines.hpp"
#include "mwDeprecated.hpp"
#include "mwIdxRangeException.hpp"
#include "mwMathConstants.hpp"
#include "mwMeasurable.hpp"
#include "mwStringConversions.hpp"
#include "mwTPoint3d.hpp"
#include "mwLanguageFeatures.hpp"

#include <algorithm>
#include <iterator>
#include <vector>

#ifndef MW_FORCEINLINE
#if defined(_WIN32)
#define MW_FORCEINLINE __forceinline
#else
#define MW_FORCEINLINE inline
#endif
#endif

namespace cadcam
{
#pragma CACHING_INTERNAL_BEGIN
template <typename T, typename _TVertex, typename _TFaceNormal>
class mwContainerMesh;

/// type definitions for mwContainerMesh
template <typename T, typename _TVertex = mwTPoint3d<T>, typename _TFaceNormal = mwTPoint3d<T>>
struct MW_5AXUTIL_API mwContainerMeshDefines
{
	typedef T ValueType;
	typedef _TVertex TVertex;
	typedef _TFaceNormal TFaceNormal;

	typedef mwContainerMesh<T, TVertex, TFaceNormal> MyType;
	typedef misc::mwAutoPointer<MyType> Ptr;

	typedef typename misc::mwAutoPointer<TVertex> TVertexPtr;

	typedef typename misc::mwAutoPointer<TFaceNormal> TFaceNormalPtr;

	typedef typename std::vector<TVertex> pointArray;
	typedef typename pointArray::const_iterator constPointIt;
	typedef typename pointArray::iterator PointIt;
	typedef mwTPoint3d<T> point3d;
	typedef typename point3d::Ptr point3dPtr;
	typedef point3d vector3d;

	typedef typename std::vector<TFaceNormal> normalArray;
	typedef typename normalArray::const_iterator constNormalIt;
	typedef typename normalArray::iterator NormalIt;
};

/// This class represents a Triangle in the mesh
///
/// Contains a normal and the indices to the points in the pointArray
template <typename T, typename _TVertex = mwTPoint3d<T>, typename _TFaceNormal = mwTPoint3d<T>>
class MW_5AXUTIL_API mwTTriangle: public mwContainerMeshDefines<T, _TVertex, _TFaceNormal>
{
public:
	typedef typename ::cadcam::mwContainerMeshDefines<T, _TVertex, _TFaceNormal>
		BaseT;  ///< type definitions
	typedef typename BaseT::TFaceNormal TFaceNormal;  ///< type for the normal storage
	typedef typename BaseT::ValueType ValueType;  ///< type for coordinates
	typedef typename BaseT::point3d point3d;  ///< type to set and get the normal

public:
	inline void SetPointIndex(int iPtPos, size_t newPtIndex);
	inline void SetNormalIndex(int iNormal, int newNormalIndex);
	inline void SetNormal(const TFaceNormal& newNormal);
	inline void SetFirstPointIndex(const size_t newPtIndex);
	inline void SetSecondPointIndex(const size_t newPtIndex);
	inline void SetThirdPointIndex(const size_t newPtIndex);
	inline void SetFirstNormalIndex(const int newNormalIndex);
	inline void SetSecondNormalIndex(const int newNormalIndex);
	inline void SetThirdNormalIndex(const int newNormalIndex);
	inline void SetIndices(const size_t& v1, const size_t& v2, const size_t& v3);
	inline void SetNormalIndices(const int& v1, const int& v2, const int& v3);
	inline size_t GetPointIndex(const int iPtPos) const;
	inline int GetNormalIndex(const int iNormal) const;
	inline point3d GetNormalVector() const;
	inline void SetNormalVector(const point3d& normal);
	inline ValueType GetNormalZ() const;
	inline bool IsNormalVectorHorizontal() const;
	inline const TFaceNormal& GetData() const;
	inline TFaceNormal& GetData();
	inline size_t GetFirstPointIndex() const;
	inline size_t GetSecondPointIndex() const;
	inline size_t GetThirdPointIndex() const;
	inline int GetFirstNormalIndex() const;
	inline int GetSecondNormalIndex() const;
	inline int GetThirdNormalIndex() const;
	inline void GetIndices(size_t& v1, size_t& v2, size_t& v3) const;
	inline void GetNormalIndices(int& v1, int& v2, int& v3) const;
	MW_FORCEINLINE bool operator==(const mwTTriangle& tc) const;

	/// enum for indexing the three points
	enum dataComponents
	{
		FIRST_POINT = 0,  ///< first point
		SECOND_POINT,  ///< second point
		THIRD_POINT  ///< third point
	};

	inline mwTTriangle();
	inline mwTTriangle(
		size_t firstIndex, size_t secondIndex, size_t thirdIndex, const TFaceNormal& normal);
	inline mwTTriangle(
		size_t firstPtIndex,
		size_t secondPtIndex,
		size_t thirdPtIndex,
		int firstNormalIndex,
		int secondNormalIndex,
		int thirdNormalIndex,
		const TFaceNormal& normal);
	inline ~mwTTriangle();
	inline mwTTriangle(const mwTTriangle& toCopy);

	inline mwTTriangle& operator=(const mwTTriangle& toCopy);

	template <typename Archive>
	void serialize(Archive& ar, unsigned int);

private:
	unsigned index[3];  ///< index for the vertices into the point array
	int normalIndex[3];  ///< index for the vertices into the normal array
	TFaceNormal m_Normal;  ///< normal vector
};

/// This class represents a Triangle Vector
///
/// It is an alternative representation of a mesh.
template <typename T, typename _TVertex = mwTPoint3d<T>, typename _TFaceNormal = mwTPoint3d<T>>
class MW_5AXUTIL_API mwTTriangleVector: public mwContainerMeshDefines<T, _TVertex, _TFaceNormal>
{
public:
	typedef mwContainerMeshDefines<T, _TVertex, _TFaceNormal> BaseT;
	typedef typename BaseT::TVertex TVertex;
	typedef typename BaseT::TFaceNormal TFaceNormal;
	typedef typename BaseT::constPointIt constPointIt;
	typedef typename BaseT::pointArray pointArray;
	typedef typename BaseT::normalArray normalArray;

public:
	typedef mwTTriangle<T, _TVertex, _TFaceNormal> Triangle;
	typedef std::vector<Triangle> TriangleArray;

	inline void Reserve(size_t szSize);
	inline void Reserve(size_t vertexCount, size_t triangleCount);
	inline bool IsTriangle(const TVertex& pt1, const TVertex& pt2, const TVertex& pt3);
	inline void AddTriangle(const TVertex& pt1, const TVertex& pt2, const TVertex& pt3);
	inline void AddTriangle(
		const TVertex& pt1,
		const TVertex& pt2,
		const TVertex& pt3,
		const TFaceNormal& nr1,
		const TFaceNormal& nr2,
		const TFaceNormal& nr3);
	inline void AddTriangle(
		const TVertex& pt1, const TVertex& pt2, const TVertex& pt3, const TFaceNormal& normal);
	inline void AddTriangle(
		const TVertex& pt1,
		const TVertex& pt2,
		const TVertex& pt3,
		const TFaceNormal& nr1,
		const TFaceNormal& nr2,
		const TFaceNormal& nr3,
		const TFaceNormal& normal);
	inline size_t GetNumberOfPoints() const;
	inline size_t GetNumberOfTriangles() const;
	inline constPointIt GetPointsBegin() const;
	inline constPointIt GetPointsEnd() const;
	inline mwTTriangleVector(const T pointCoordPrec = mathdef::mw_tol(T()));
	inline ~mwTTriangleVector();

	misc::mwAutoPointer<TriangleArray> mTriangles;
	misc::mwAutoPointer<pointArray> mVertex;
	misc::mwAutoPointer<normalArray> mNormals;
	T mPointCoordPrec;
};

/// This class represents a Mesh structure.
///
/// Given a set of triangles it stores an array of points: mPoints and an array of triangles:
/// mTriangles. The triangles contain indices which direct to the points in the mPoints point array.
/// The mPoints point array contains no duplicate points, therefore, several triangles can have
/// common point indexes.
/// @tparam T can be a scalar type (for example float or double).
/// @tparam TVertex default is mwTPoint3d<T>, but it can be any kind of point with corresponding
/// interface. It may be used to store extra data in the points.
/// @tparam TFaceNormal default is mwTPoint3d<T>, but it can be any kind of point with corresponding
/// interface. It may be used to store extra data in the triangles.
template <typename T, typename _TVertex = mwTPoint3d<T>, typename _TFaceNormal = mwTPoint3d<T>>
class MW_5AXUTIL_API mwContainerMesh: public measures::mwMeasurable,
					   public mwContainerMeshDefines<T, _TVertex, _TFaceNormal>
{
public:
	typedef mwContainerMeshDefines<T, _TVertex, _TFaceNormal> Base2T;

	typedef typename Base2T::TVertex TVertex;
	typedef typename Base2T::TVertexPtr TVertexPtr;
	typedef typename Base2T::TFaceNormal TFaceNormal;
	typedef typename Base2T::TFaceNormalPtr TFaceNormalPtr;
	typedef typename Base2T::point3d point3d;
	typedef typename Base2T::pointArray pointArray;
	typedef typename Base2T::normalArray normalArray;
	typedef typename Base2T::MyType MyType;
	typedef typename Base2T::PointIt PointIt;
	typedef typename Base2T::constPointIt constPointIt;
	typedef typename Base2T::NormalIt NormalIt;
	typedef typename Base2T::constNormalIt constNormalIt;

public:
	typedef measures::mwMeasurable::Units Units;
	inline bool operator==(const mwContainerMesh& tc) const;
	inline bool operator!=(const mwContainerMesh& tc) const;
	inline static bool ComparePoints(const TVertex& pt1, const TVertex& pt2, const T prec);
	inline static const TVertexPtr Point2TVertex(const point3d& point);
	inline static const TFaceNormalPtr Point2TFaceNormal(const point3d& point);

protected:
	inline virtual void Scale(const measures::mwUnitsFactory::Units, const double& scaleFactor);

public:
	typedef mwTTriangle<T, _TVertex, _TFaceNormal> Triangle;
	typedef std::vector<Triangle> TriangleArray;

	typedef typename TriangleArray::iterator TriangleIt;
	typedef typename TriangleArray::const_iterator constTriangleIt;

	typedef mwTTriangleVector<T, _TVertex, _TFaceNormal> TriangleVector;

#if defined(_WIN32)
	MW_DEPRECATED("Deprecated in 2015.12. Use Triangle instead")
	typedef mwTTriangle<T, _TVertex, _TFaceNormal> mwTTriangle;
	MW_DEPRECATED("Deprecated in 2015.12. Use TriangleVector instead")
	typedef mwTTriangleVector<T, _TVertex, _TFaceNormal> mwTTriangleVector;
#endif

	inline mwContainerMesh(const Units& unit, const T pointCoordPrec = mathdef::mw_tol(T()));
	inline virtual ~mwContainerMesh();
	inline mwContainerMesh(const MyType& toCopy);
#ifndef MW_USE_VS2008_COMPATIBILITY
	inline mwContainerMesh(mwContainerMesh<T>&& other) noexcept;
#endif
	inline mwContainerMesh(
		const pointArray& points,
		const TriangleArray& triangles,
		const Units& unit,
		const T pointCoordPrec = mathdef::mw_tol(T()));
#ifndef MW_USE_VS2008_COMPATIBILITY
	inline mwContainerMesh(
		pointArray&& points,
		TriangleArray&& triangles,
		const Units& unit,
		const T pointCoordPrec = mathdef::mw_tol(T()));
	inline mwContainerMesh(
		pointArray&& points,
		normalArray&& normals,
		TriangleArray&& triangles,
		const Units& unit,
		const T pointCoordPrec = mathdef::mw_tol(T()));
#endif
	inline explicit mwContainerMesh(
		misc::mwAutoPointer<pointArray> points,
		misc::mwAutoPointer<TriangleArray> triangles,
		const Units& unit,
		const T pointCoordPrec = mathdef::mw_tol(T()));
	inline explicit mwContainerMesh(
		const pointArray& points,
		const normalArray& normals,
		const TriangleArray& triangles,
		const Units& unit,
		const T pointCoordPrec = mathdef::mw_tol(T()));
	inline explicit mwContainerMesh(
		misc::mwAutoPointer<pointArray> points,
		misc::mwAutoPointer<normalArray> normals,
		misc::mwAutoPointer<TriangleArray> triangles,
		const Units& unit,
		const T pointCoordPrec = mathdef::mw_tol(T()));
	inline explicit mwContainerMesh(const TriangleVector& triVectToSet, const Units& unit);

	inline void GetNormal(
		const TVertex& pt1, const TVertex& pt2, const TVertex& pt3, TFaceNormal& normal) const;
	inline point3d GetNormal(const size_t szTriangle) const;

private:
	inline void SetMesh(const MyType& toSet);

public:
	inline void CopyForWrite(bool points = true, bool triangles = true);
	inline virtual void AddMesh(const MyType& toAdd);
	inline void ReservePoints(size_t capacity);
	inline void ReserveTriangles(size_t capacity);
	inline virtual void AddMeshFastButDontCareDuplicates(const MyType& src);
	inline static bool PointsCloseEnough(
		const TVertex& pt1, const TVertex& pt2, const T fEpsilon = (T)(1e-12 * 1e-12));
	inline static bool RemoveDegeneratedTrianglePredicate(const Triangle& t);
	inline void RemoveDuplicatesSlow(const T fEpsilon = (T)(1e-12 * 1e-12));
	inline void GarbageCollect();
	inline virtual void SetTriangles(const TriangleVector& triVectToSet);
	inline const TVertex& GetTriangleFirstVertexData(const size_t szTriangle) const;
	inline const TVertex& GetTriangleSecondVertexData(const size_t szTriangle) const;
	inline const TVertex& GetTriangleThirdVertexData(const size_t szTriangle) const;
	inline point3d GetTriangleFirstVertexPosition(const size_t szTriangle) const;
	inline point3d GetTriangleSecondVertexPosition(const size_t szTriangle) const;
	inline point3d GetTriangleThirdVertexPosition(const size_t szTriangle) const;
	inline const TFaceNormal GetTriangleFirstVertexNormal(const size_t szTriangle) const;
	inline const TFaceNormal GetTriangleSecondVertexNormal(const size_t szTriangle) const;
	inline const TFaceNormal GetTriangleThirdVertexNormal(const size_t szTriangle) const;
	inline const TFaceNormal& GetTriangleData(const size_t szTriangle) const;
	inline point3d GetTriangleNormalVector(const size_t szTriangle) const;
	inline void SetTriangleNormalVector(const size_t szTriangle, const mwTPoint3d<T>& normal);
	inline T GetTriangleArea(const size_t szTriangle) const;
	inline point3d GetTriangleCentroid(const size_t szTriangle) const;
	inline size_t GetNumberOfTriangles() const;
	inline virtual PointIt GetPointsBegin();
	inline virtual PointIt GetPointsEnd();
	inline virtual constPointIt GetPointsBegin() const;
	inline virtual constPointIt GetPointsEnd() const;
	inline size_t GetNumberOfPoints() const;
	inline const TVertex& GetPoint(const size_t szPointIndex) const;
	inline virtual NormalIt GetVertexNormalsBegin();
	inline virtual NormalIt GetVertexNormalsEnd();
	inline virtual constNormalIt GetVertexNormalsBegin() const;
	inline virtual constNormalIt GetVertexNormalsEnd() const;
	inline size_t GetNumberOfVertexNormals() const;
	inline const TFaceNormal& GetVertexNormal(const size_t szNormalIndex) const;
	inline virtual void SetPoint(
		const size_t szPointIndex, const TVertex pt, const bool recalculateNormals);
	inline virtual void SetVertexPosition(
		const size_t szPointIndex, const point3d& pt, const bool recalculateNormals);
	inline void RecalculateAndNormalizeNormals();
	inline void RecalculateNormals();
	inline void RecalculateNormalsForAVertex(const size_t szVertex);
	inline void RecalculateNormalsForATriangle(const size_t szTriangle);
	inline virtual void ResetMesh();
	inline const MyType& operator=(const MyType& tc);
#ifndef MW_USE_VS2008_COMPATIBILITY
	inline MyType& operator=(MyType&& tc) noexcept;
#endif
	inline const Triangle& GetTriangle(const size_t szTriangle) const;
	inline misc::mwAutoPointer<pointArray> GetPointsAutoPointer() const;
	inline virtual void SetTriangles(
		const misc::mwAutoPointer<pointArray>& points,
		const misc::mwAutoPointer<TriangleArray>& triangles);
	inline misc::mwAutoPointer<TriangleArray> GetTrianglesAutoPointer() const;
	inline virtual const pointArray& GetPoints() const;
	inline virtual pointArray& GetPoints();
	inline virtual const normalArray& GetVertexNormals() const;
	inline virtual normalArray& GetVertexNormals();
	inline virtual const TriangleArray& GetTriangles() const;
	inline virtual TriangleArray& GetTriangles();
	inline virtual bool IsTriangleAdditionalDataSupport() const;
	inline virtual void SetTriangleAdditionalData(const size_t trNumber, const unsigned short data);
	inline virtual unsigned short GetTriangleAdditionalData(const size_t trNumber) const;
	inline const TVertex& GetTriangleVertexData(const size_t szTriangle, int iPtPos) const;
	inline const TFaceNormal& GetTriangleVertexNormal(const size_t szTriangle, int iPtPos) const;
	// needed because mwTMesh (derived from this) does not have this member in the constructor
	inline T GetPointCoordPrec() const { return mPointCoordPrec; };
	inline void SetPointCoordPrec(const T v) { mPointCoordPrec = v; };
	inline void TolerateToZeroAllPoints(const T& tol);

	/// Swap the underlying containers. Much cheaper than copying.
	void Swap(mwContainerMesh<T>& other)
	{
		// swap units
		measures::mwUnitsFactory::Units tmp = GetUnits();
		SetUnits(other.GetUnits());
		other.SetUnits(tmp);

		std::swap(mTriangles, other.mTriangles);
		std::swap(mPoints, other.mPoints);
		std::swap(mNormals, other.mNormals);
		std::swap(mPointCoordPrec, other.mPointCoordPrec);
	}


protected:
	inline void RemapTrianglePointIndices(
		const TriangleIt& first, const TriangleIt& last, const std::vector<unsigned>& indexMap);

#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<TriangleArray> mTriangles;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<pointArray> mPoints;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<normalArray> mNormals;
	T mPointCoordPrec;

private:
	template <class Value>
	inline void ReserveAndReallocate(std::vector<Value>& array, size_t newCapacity);
	inline void RecalculateNormalsForATriangleNoCheck(const size_t szTriangle);
	// the sorting predicated
	class SortPred
	{
	public:
		SortPred(const TriangleVector& triangleVec);
		bool operator()(const TVertex* pt0, const TVertex* pt1);
		T m_prec;
	};
	inline point3d GetTriangleVertexPosition(const size_t szTriangle, int iPtPos) const;
};

/// Copy constructor
///
/// @param toCopy of type const mwTTriangle<T>
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwTTriangle<T, _TVertex, _TFaceNormal>::mwTTriangle(const mwTTriangle& toCopy)
{
	index[FIRST_POINT] = toCopy.index[FIRST_POINT];
	index[SECOND_POINT] = toCopy.index[SECOND_POINT];
	index[THIRD_POINT] = toCopy.index[THIRD_POINT];
	normalIndex[FIRST_POINT] = toCopy.normalIndex[FIRST_POINT];
	normalIndex[SECOND_POINT] = toCopy.normalIndex[SECOND_POINT];
	normalIndex[THIRD_POINT] = toCopy.normalIndex[THIRD_POINT];
	m_Normal = toCopy.m_Normal;
}

/// Assignment operator
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwTTriangle<T, _TVertex, _TFaceNormal>& mwTTriangle<T, _TVertex, _TFaceNormal>::operator=(
	const mwTTriangle& toCopy)
{
	index[FIRST_POINT] = toCopy.index[FIRST_POINT];
	index[SECOND_POINT] = toCopy.index[SECOND_POINT];
	index[THIRD_POINT] = toCopy.index[THIRD_POINT];
	normalIndex[FIRST_POINT] = toCopy.normalIndex[FIRST_POINT];
	normalIndex[SECOND_POINT] = toCopy.normalIndex[SECOND_POINT];
	normalIndex[THIRD_POINT] = toCopy.normalIndex[THIRD_POINT];
	m_Normal = toCopy.m_Normal;
	return *this;
}

/// Destructor
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwTTriangle<T, _TVertex, _TFaceNormal>::~mwTTriangle()
{
}

/// Constructor setting point indices and normal.
///
/// @param firstIndex the index of the first triangle point in the pointArray
/// @param secondIndex the index of the second triangle point in the pointArray
/// @param thirdIndex the index of the third triangle point in the pointArray
/// @param normal the triangle normal
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwTTriangle<T, _TVertex, _TFaceNormal>::mwTTriangle(
	size_t firstIndex, size_t secondIndex, size_t thirdIndex, const TFaceNormal& normal)
	: m_Normal(normal)
{
	index[FIRST_POINT] = (unsigned)firstIndex;
	index[SECOND_POINT] = (unsigned)secondIndex;
	index[THIRD_POINT] = (unsigned)thirdIndex;
	normalIndex[FIRST_POINT] = normalIndex[SECOND_POINT] = normalIndex[THIRD_POINT] = -1;
}

/// Constructor setting point indices and normal.
///
/// @param firstIndex the index of the first triangle point in the pointArray
/// @param secondIndex the index of the second triangle point in the pointArray
/// @param thirdIndex the index of the third triangle point in the pointArray
/// @param firstNormalIndex the index of the first triangle vertex normal in the normalArray
/// @param secondNormalIndex the index of the second triangle vertex normal in the normalArray
/// @param thirdNormalIndex the index of the third triangle vertex normal in the normalArray
/// @param normal the triangle normal
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwTTriangle<T, _TVertex, _TFaceNormal>::mwTTriangle(
	size_t firstIndex,
	size_t secondIndex,
	size_t thirdIndex,
	int firstNormalIndex,
	int secondNormalIndex,
	int thirdNormalIndex,
	const TFaceNormal& normal)
	: m_Normal(normal)
{
	index[FIRST_POINT] = (unsigned)firstIndex;
	index[SECOND_POINT] = (unsigned)secondIndex;
	index[THIRD_POINT] = (unsigned)thirdIndex;
	normalIndex[FIRST_POINT] = firstNormalIndex, normalIndex[SECOND_POINT] = secondNormalIndex,
	normalIndex[THIRD_POINT] = thirdNormalIndex;
}
/// Default constructor.
///
/// Initializes vertex indices to 0.
/// The mwTTriangle default constructor is needed for the std::vector resize() method.
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwTTriangle<T, _TVertex, _TFaceNormal>::mwTTriangle()
{
	index[FIRST_POINT] = index[SECOND_POINT] = index[THIRD_POINT] = 0;
	normalIndex[FIRST_POINT] = normalIndex[SECOND_POINT] = normalIndex[THIRD_POINT] = -1;
}
/// Equality operator
///
/// Check if two triangles have the same vertex and normal indices (possibly in a different order).
/// The position of the vertices are not considered.
/// @param tc triangle to compare the current triangle with
/// @returns <b>true</b> if they are equal,
/// <b>false</b> otherwise
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
MW_FORCEINLINE bool mwTTriangle<T, _TVertex, _TFaceNormal>::operator==(const mwTTriangle& tc) const
{
	return ((index[0] == tc.index[0] && index[1] == tc.index[1] && index[2] == tc.index[2]) &&
			(normalIndex[0] == tc.normalIndex[0] && normalIndex[1] == tc.normalIndex[1] &&
			 normalIndex[2] == tc.normalIndex[2])) ||
		((index[0] == tc.index[1] && index[1] == tc.index[2] && index[2] == tc.index[0]) &&
		 (normalIndex[0] == tc.normalIndex[1] && normalIndex[1] == tc.normalIndex[2] &&
		  normalIndex[2] == tc.normalIndex[0])) ||
		((index[0] == tc.index[2] && index[1] == tc.index[0] && index[2] == tc.index[1]) &&
		 (normalIndex[0] == tc.normalIndex[2] && normalIndex[1] == tc.normalIndex[0] &&
		  normalIndex[2] == tc.normalIndex[1])) ||
		((index[0] == tc.index[0] && index[1] == tc.index[2] && index[2] == tc.index[1]) &&
		 (normalIndex[0] == tc.normalIndex[0] && normalIndex[1] == tc.normalIndex[2] &&
		  normalIndex[2] == tc.normalIndex[1])) ||
		((index[0] == tc.index[1] && index[1] == tc.index[0] && index[2] == tc.index[2]) &&
		 (normalIndex[0] == tc.normalIndex[1] && normalIndex[1] == tc.normalIndex[0] &&
		  normalIndex[2] == tc.normalIndex[2])) ||
		((index[0] == tc.index[2] && index[1] == tc.index[1] && index[2] == tc.index[0]) &&
		 (normalIndex[0] == tc.normalIndex[2] && normalIndex[1] == tc.normalIndex[1] &&
		  normalIndex[2] == tc.normalIndex[0]));
}

/// Get vertex indices
///
/// @return the triangle indices
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangle<T, _TVertex, _TFaceNormal>::GetIndices(
	size_t& v1, size_t& v2, size_t& v3) const
{
	v1 = index[FIRST_POINT];
	v2 = index[SECOND_POINT];
	v3 = index[THIRD_POINT];
}

/// Get vertex normal indices
///
/// @return the triangle vertex normal indices
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangle<T, _TVertex, _TFaceNormal>::GetNormalIndices(
	int& v1, int& v2, int& v3) const
{
	v1 = normalIndex[FIRST_POINT];
	v2 = normalIndex[SECOND_POINT];
	v3 = normalIndex[THIRD_POINT];
}

/// Get third point index
///
/// @return the index of the third triangle point in the pointArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline size_t mwTTriangle<T, _TVertex, _TFaceNormal>::GetThirdPointIndex() const
{
	return index[THIRD_POINT];
}
/// Get second point index
///
/// @return the index of the second triangle point in the pointArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline size_t mwTTriangle<T, _TVertex, _TFaceNormal>::GetSecondPointIndex() const
{
	return index[SECOND_POINT];
}
/// Get first point index
///
/// @return the index of the first triangle point in the pointArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline size_t mwTTriangle<T, _TVertex, _TFaceNormal>::GetFirstPointIndex() const
{
	return index[FIRST_POINT];
}

/// Get third vertex normal index
///
/// @return the index of the third triangle vertex normal in the normalArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline int mwTTriangle<T, _TVertex, _TFaceNormal>::GetThirdNormalIndex() const
{
	return normalIndex[THIRD_POINT];
}
/// Get second vertex normal index
///
/// @return the index of the second triangle vertex normal in the normalArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline int mwTTriangle<T, _TVertex, _TFaceNormal>::GetSecondNormalIndex() const
{
	return normalIndex[SECOND_POINT];
}
/// Get first vertex normal index
///
/// @return the index of the first triangle vertex normal in the normalArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline int mwTTriangle<T, _TVertex, _TFaceNormal>::GetFirstNormalIndex() const
{
	return normalIndex[FIRST_POINT];
}

/// Get normal
///
/// @return the triangle normal
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwTTriangle<T, _TVertex, _TFaceNormal>::TFaceNormal&
mwTTriangle<T, _TVertex, _TFaceNormal>::GetData()
{
	return m_Normal;
}
/// Get normal, const version
///
/// @return the triangle normal as const
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwTTriangle<T, _TVertex, _TFaceNormal>::TFaceNormal&
mwTTriangle<T, _TVertex, _TFaceNormal>::GetData() const
{
	return m_Normal;
}

/// Check if the normal is horizontal within tolerance
///
/// @return true if the triangle normal is horizontal
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline bool mwTTriangle<T, _TVertex, _TFaceNormal>::IsNormalVectorHorizontal() const
{
	if (std::fabs(m_Normal.z()) < 0.00001f)
		return true;
	else
		return false;
}
/// Get normal z coordinate
///
/// @return the triangle normal Z component
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwTTriangle<T, _TVertex, _TFaceNormal>::ValueType
mwTTriangle<T, _TVertex, _TFaceNormal>::GetNormalZ() const
{
	return m_Normal.z();
}
/// Set normal vector
///
/// @param normal the triangle normal
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangle<T, _TVertex, _TFaceNormal>::SetNormalVector(const point3d& normal)
{
	m_Normal.x(normal.x());
	m_Normal.y(normal.y());
	m_Normal.z(normal.z());
}

/// Get normal vector
///
/// @return the triangle normal
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwTTriangle<T, _TVertex, _TFaceNormal>::point3d
mwTTriangle<T, _TVertex, _TFaceNormal>::GetNormalVector() const
{
	return point3d(m_Normal.x(), m_Normal.y(), m_Normal.z());
}
/// Get point index of specified vertex
///
/// @return the index of the specified point in the pointArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline size_t mwTTriangle<T, _TVertex, _TFaceNormal>::GetPointIndex(const int iPtPos) const
{
	if (iPtPos < FIRST_POINT || iPtPos > THIRD_POINT)
		throw misc::mwIdxRangeException<size_t>(THIRD_POINT, iPtPos);

	return index[iPtPos];
}
/// Get vertex normal index of specified vertex
///
/// @return the index of the specified vertex normal in the normalArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline int mwTTriangle<T, _TVertex, _TFaceNormal>::GetNormalIndex(const int iNormal) const
{
	if (iNormal < FIRST_POINT || iNormal > THIRD_POINT)
		throw misc::mwIdxRangeException<size_t>(THIRD_POINT, iNormal);

	return normalIndex[iNormal];
}
/// Set indices
///
/// This method sets the specified point index
/// @param v1 index of the first point in the pointArray
/// @param v2 index of the second point in the pointArray
/// @param v3 index of the third point in the pointArray

template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangle<T, _TVertex, _TFaceNormal>::SetIndices(
	const size_t& v1, const size_t& v2, const size_t& v3)
{
	index[FIRST_POINT] = (unsigned)v1;
	index[SECOND_POINT] = (unsigned)v2;
	index[THIRD_POINT] = (unsigned)v3;
}
/// Set vertex normal indices
///
/// This method sets the specified vertex normal index
/// @param v1 index of the first vertex normal in the normalArray
/// @param v2 index of the second vertex normal in the normalArray
/// @param v3 index of the third vertex normal in the normalArray

template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangle<T, _TVertex, _TFaceNormal>::SetNormalIndices(
	const int& v1, const int& v2, const int& v3)
{
	normalIndex[FIRST_POINT] = v1;
	normalIndex[SECOND_POINT] = v2;
	normalIndex[THIRD_POINT] = v3;
}
/// Set third point index
///
/// This method sets the specified point index
/// @param newPtIndex index of the point in the pointArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangle<T, _TVertex, _TFaceNormal>::SetThirdPointIndex(const size_t newPtIndex)
{
	index[THIRD_POINT] = (unsigned)newPtIndex;
}
/// Set second point index
///
/// This method sets the specified point index
/// @param newPtIndex the index of the point in the pointArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangle<T, _TVertex, _TFaceNormal>::SetSecondPointIndex(const size_t newPtIndex)
{
	index[SECOND_POINT] = (unsigned)newPtIndex;
}
/// Set first point index
///
/// This method sets the specified point index
/// @param newPtIndex the index of the point in the pointArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangle<T, _TVertex, _TFaceNormal>::SetFirstPointIndex(const size_t newPtIndex)
{
	index[FIRST_POINT] = (unsigned)newPtIndex;
}
/// Set third vertex normal index
///
/// This method sets the specified vertex normal index
/// @param newNormalIndex index of the vertex normal in the normalArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangle<T, _TVertex, _TFaceNormal>::SetThirdNormalIndex(const int newNormalIndex)
{
	normalIndex[THIRD_POINT] = newNormalIndex;
}
/// Set second vertex normal index
///
/// This method sets the specified vertex normal index
/// @param newNormalIndex index of the vertex normal in the normalArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangle<T, _TVertex, _TFaceNormal>::SetSecondNormalIndex(const int newNormalIndex)
{
	normalIndex[SECOND_POINT] = newNormalIndex;
}
/// Set first vertex normal index
///
/// This method sets the specified vertex normal index
/// @param newNormalIndex index of the vertex normal in the normalArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangle<T, _TVertex, _TFaceNormal>::SetFirstNormalIndex(const int newNormalIndex)
{
	normalIndex[FIRST_POINT] = newNormalIndex;
}
/// Set normal
///
/// This method sets the triangle normal
/// @param newNormal the triangle normal
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangle<T, _TVertex, _TFaceNormal>::SetNormal(const TFaceNormal& newNormal)
{
	m_Normal = TFaceNormal(newNormal);
}

/// Set point index for specified vertex
///
/// This method sets the specified point index
/// @param iPtPos specifies the point in the triangle
/// @param newPtIndex the index of the point in the pointArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangle<T, _TVertex, _TFaceNormal>::SetPointIndex(int iPtPos, size_t newPtIndex)
{
	if (iPtPos < FIRST_POINT || iPtPos > THIRD_POINT)
		throw misc::mwIdxRangeException<size_t>(THIRD_POINT, iPtPos);

	index[iPtPos] = (unsigned)newPtIndex;
}

/// Set normal index for specified vertex
///
/// This method sets the specified normal index
/// @param iNormal specifies the normal in the triangle
/// @param newNormalIndex the index of the normal in the normalArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangle<T, _TVertex, _TFaceNormal>::SetNormalIndex(int iNormal, int newNormalIndex)
{
	if (iNormal < FIRST_POINT || iNormal > THIRD_POINT)
		throw misc::mwIdxRangeException<size_t>(THIRD_POINT, iNormal);

	normalIndex[iNormal] = newNormalIndex;
}

/// Destructor
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwTTriangleVector<T, _TVertex, _TFaceNormal>::~mwTTriangleVector()
{
}
/// Default constructor
///
/// Generates empty point and triangle vectors.
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwTTriangleVector<T, _TVertex, _TFaceNormal>::mwTTriangleVector(
	const T pointCoordPrec /*= mathdef::mw_tol(T())*/)
{
	mTriangles = new TriangleArray;
	mVertex = new pointArray;
	mNormals = new normalArray;
	mPointCoordPrec = pointCoordPrec;
}

/// Get points end iterator
///
/// @return the pointer to the end of the mVertex array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwTTriangleVector<T, _TVertex, _TFaceNormal>::constPointIt
mwTTriangleVector<T, _TVertex, _TFaceNormal>::GetPointsEnd() const
{
	return mVertex->end();
}
/// Get point begin iterator
///
///	@return the pointer to the first element in the mVertex array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwTTriangleVector<T, _TVertex, _TFaceNormal>::constPointIt
mwTTriangleVector<T, _TVertex, _TFaceNormal>::GetPointsBegin() const
{
	return mVertex->begin();
}
/// Get number of triangles
///
///	@return the number of Triangles in the TriangleVector pointArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline size_t mwTTriangleVector<T, _TVertex, _TFaceNormal>::GetNumberOfTriangles() const
{
	return mTriangles->size();
}
/// Get number of points
///
///	@return the number of Points in the TriangleVector pointArray
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline size_t mwTTriangleVector<T, _TVertex, _TFaceNormal>::GetNumberOfPoints() const
{
	return mVertex->size();
}
/// Add triangle with specified normal
///
/// Add a Triangle to the TriangleVector
/// @param pt1 first triangle point
/// @param pt2 second triangle point
/// @param pt3 third triangle point
/// @param normal the triangle normal
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangleVector<T, _TVertex, _TFaceNormal>::AddTriangle(
	const TVertex& pt1, const TVertex& pt2, const TVertex& pt3, const TFaceNormal& normal)
{
	if (!IsTriangle(pt1, pt2, pt3))
	{
		return;
	}

	mVertex->push_back(pt1);
	mVertex->push_back(pt2);
	mVertex->push_back(pt3);
	mTriangles->push_back(Triangle(
		static_cast<size_t>(mVertex->size() - 3),
		static_cast<size_t>(mVertex->size() - 2),
		static_cast<size_t>(mVertex->size() - 1),
		normal));
}

/// Checks if points are making a triangle
///
/// The pointIndex parameters have to be given in a counterclockwise order.
/// @param pt1 first triangle point
/// @param pt2 second triangle point
/// @param pt3 third triangle point
/// @return true if points form a valid triangle
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline bool mwTTriangleVector<T, _TVertex, _TFaceNormal>::IsTriangle(
	const TVertex& pt1, const TVertex& pt2, const TVertex& pt3)
{
	const T MAX_POSITIVE_VALUE = mathdef::mw_maxvalue(T());

	if (pt1.AreCoordinatesEqual(pt2, mPointCoordPrec))
	{
		return false;
	}
	if (pt2.AreCoordinatesEqual(pt3, mPointCoordPrec))
	{
		return false;
	}
	if (pt3.AreCoordinatesEqual(pt1, mPointCoordPrec))
	{
		return false;
	}

	if (mathdef::Abs(pt1.x()) > MAX_POSITIVE_VALUE || mathdef::Abs(pt1.y()) > MAX_POSITIVE_VALUE ||
		mathdef::Abs(pt1.z()) > MAX_POSITIVE_VALUE || mathdef::Abs(pt2.x()) > MAX_POSITIVE_VALUE ||
		mathdef::Abs(pt2.y()) > MAX_POSITIVE_VALUE || mathdef::Abs(pt2.z()) > MAX_POSITIVE_VALUE ||
		mathdef::Abs(pt3.x()) > MAX_POSITIVE_VALUE || mathdef::Abs(pt3.y()) > MAX_POSITIVE_VALUE ||
		mathdef::Abs(pt3.z()) > MAX_POSITIVE_VALUE)
	{
		throw misc::mwException(
			3514, misc::mwstring(_T("Operation failed because meshes have infinity points")));
	}

	const TVertex triangleNormal = (pt3 - pt2) % (pt1 - pt2);

	const T UNDERFLOW_LIMIT = sqrt(mathdef::mwMinPositiveValue(T()));
	if (mathdef::Abs(triangleNormal.x()) < UNDERFLOW_LIMIT &&
		mathdef::Abs(triangleNormal.y()) < UNDERFLOW_LIMIT &&
		mathdef::Abs(triangleNormal.z()) < UNDERFLOW_LIMIT)
	{
		return false;
	}

	return true;
}
/// Add triangle
/// Add a Triangle to the TriangleVector
///
/// The pointIndex parameters have to be given in a counterclockwise order.
/// @param pt1 first triangle point
/// @param pt2 second triangle point
/// @param pt3 third triangle point
/// @param nr1 first triangle point normal
/// @param nr2 second triangle point normal
/// @param nr3 third triangle point normal
/// @param normal the triangle normal
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangleVector<T, _TVertex, _TFaceNormal>::AddTriangle(
	const TVertex& pt1,
	const TVertex& pt2,
	const TVertex& pt3,
	const TFaceNormal& nr1,
	const TFaceNormal& nr2,
	const TFaceNormal& nr3,
	const TFaceNormal& normal)
{
	if (!IsTriangle(pt1, pt2, pt3))
	{
		return;
	}

	mVertex->push_back(pt1);
	mVertex->push_back(pt2);
	mVertex->push_back(pt3);
	mNormals->push_back(nr1);
	mNormals->push_back(nr2);
	mNormals->push_back(nr3);
	mTriangles->push_back(Triangle(
		static_cast<size_t>(mVertex->size() - 3),
		static_cast<size_t>(mVertex->size() - 2),
		static_cast<size_t>(mVertex->size() - 1),
		static_cast<int>(mNormals->size() - 3),
		static_cast<int>(mNormals->size() - 2),
		static_cast<int>(mNormals->size() - 1),
		normal));
}
/// Add triangle
/// Add a Triangle to the TriangleVector
///
/// The pointIndex parameters have to be given in a counterclockwise order.
/// @param pt1 first triangle point
/// @param pt2 second triangle point
/// @param pt3 third triangle point
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangleVector<T, _TVertex, _TFaceNormal>::AddTriangle(
	const TVertex& pt1, const TVertex& pt2, const TVertex& pt3)
{
	TFaceNormal newNormal = (pt3 - pt2) % (pt1 - pt2);
	AddTriangle(pt1, pt2, pt3, newNormal);
}
/// Add triangle
/// Add a Triangle to the TriangleVector
///
/// The pointIndex parameters have to be given in a counterclockwise order.
/// @param pt1 first triangle point
/// @param pt2 second triangle point
/// @param pt3 third triangle point
/// @param nr1 first triangle point normal
/// @param nr2 second triangle point normal
/// @param nr3 third triangle point normal
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangleVector<T, _TVertex, _TFaceNormal>::AddTriangle(
	const TVertex& pt1,
	const TVertex& pt2,
	const TVertex& pt3,
	const TFaceNormal& nr1,
	const TFaceNormal& nr2,
	const TFaceNormal& nr3)
{
	TFaceNormal newNormal = (TFaceNormal)(pt3 - pt2) % (pt1 - pt2);
	AddTriangle(pt1, pt2, pt3, nr1, nr2, nr3, newNormal);
}
/// Reserve memory for triangles and vertices
///
/// @param vertexCount number of vertices to be inserted
/// @param triangleCount number of triangles to be inserted
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangleVector<T, _TVertex, _TFaceNormal>::Reserve(
	size_t vertexCount, size_t triangleCount)
{
	mVertex->reserve(vertexCount);
	mTriangles->reserve(triangleCount);
}
/// Reserve memory for vertices
///
/// @param szSize number of triangles to be inserted
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwTTriangleVector<T, _TVertex, _TFaceNormal>::Reserve(size_t szSize)
{
	mVertex->reserve(szSize + 2);
}

template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline bool mwContainerMesh<T, _TVertex, _TFaceNormal>::SortPred::operator()(
	const TVertex* pt0, const TVertex* pt1)
{
	return ComparePoints(*pt0, *pt1, m_prec);
}

template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwContainerMesh<T, _TVertex, _TFaceNormal>::SortPred::SortPred(
	const TriangleVector& triangleVec)
{
	m_prec = triangleVec.mPointCoordPrec;
}

/// Get the vertex point of a triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @param iPtPos  index of the point in the triangle
/// @return point position
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::point3d
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleVertexPosition(
	const size_t szTriangle, int iPtPos) const
{
	const TVertex& v = GetTriangleVertexData(szTriangle, iPtPos);
	return point3d(v.x(), v.y(), v.z());
}

/// Get the vertex normal of a vertex in specified triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @param iNormal  index of the vertex normal in the triangle
/// @return either the specified normal or the triangle normal if no vertex normal has been defined
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TFaceNormal&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleVertexNormal(
	const size_t szTriangle, int iNormal) const
{
	size_t szNumOfTriangles = mTriangles->size();
	if (szTriangle >= szNumOfTriangles)
		throw misc::mwIdxRangeException<size_t>(szNumOfTriangles - 1, szTriangle);

	const int lNormalIndex = (*mTriangles)[szTriangle].GetNormalIndex(iNormal);

	if (lNormalIndex != -1)  // no vertex normal is defined
	{
		if (lNormalIndex >= static_cast<int>(mNormals->size()))
			throw misc::mwIdxRangeException<size_t>(
				static_cast<int>(mNormals->size()) - 1, lNormalIndex);
		return (*mNormals)[lNormalIndex];
	}
	else
	{
		return (*mTriangles)[szTriangle].GetData();
	}
}

/// Recalculates the normals of a given triangle, without checking the triangle index.
///
/// @param szTriangle index of the triangle in the triangleArray.
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::RecalculateNormalsForATriangleNoCheck(
	const size_t szTriangle)
{
	Triangle& triangle = (*mTriangles)[szTriangle];
	const TVertex& pt2 = (*mPoints)[triangle.GetPointIndex(Triangle::SECOND_POINT)];
	const TVertex normal = ((*mPoints)[triangle.GetPointIndex(Triangle::THIRD_POINT)] - pt2) %
		((*mPoints)[triangle.GetPointIndex(Triangle::FIRST_POINT)] - pt2);
	triangle.SetNormal(TFaceNormal(normal.x(), normal.y(), normal.z()));
}
/// Reserve and reallocate
///
/// Expands capacity of vector to new capacity or on 20%.
///	Such behaviour guarantees us to have no more than 5 reallocations of each element
///	Without 20% check it the total reallocations may be O(n^2) times instead of 5*n
///	@param array vector to reallocate
///	@param newCapacity new capacity
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
template <class Value>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::ReserveAndReallocate(
	std::vector<Value>& array, size_t newCapacity)
{
	if (array.capacity() < newCapacity)
	{
		size_t capacity120Percent = array.capacity() + array.capacity() / 5;
		if (newCapacity < capacity120Percent)
		{
			newCapacity = capacity120Percent;
		}
		array.reserve(newCapacity);
	}
}
/// Remap triangle point indices
///
/// Change the indices of the points the triangles use, according to the supplied map
/// @param first first triangle iterator
/// @param last last triangle iterator
///	@param indexMap vector where "indexMap[i]" is the new index of the point that used to be at
///index "i"
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::RemapTrianglePointIndices(
	const TriangleIt& first, const TriangleIt& last, const std::vector<unsigned>& indexMap)
{
	for (TriangleIt tri = first; tri != last; ++tri)
	{
		tri->SetFirstPointIndex(indexMap[tri->GetFirstPointIndex()]);
		tri->SetSecondPointIndex(indexMap[tri->GetSecondPointIndex()]);
		tri->SetThirdPointIndex(indexMap[tri->GetThirdPointIndex()]);
	}
}
/// Tolerate to zero for all points
///
/// Call the function cadcam::mwTPoint3d<T>::TolerateToZero(tol) on all points of the mesh
/// @param tol If the absolute value of a component of a point is smaller or equal to tol, it is set
/// to zero
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::TolerateToZeroAllPoints(const T& tol)
{
	const PointIt itEnd = GetPointsEnd();
	for (PointIt it = GetPointsBegin(); it != itEnd; ++it)
	{
		it->TolerateToZero(tol);
	}
}
/// Get the vertex point of a triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @param iPtPos index of the point in the triangle
/// @return vertex point
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TVertex&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleVertexData(
	const size_t szTriangle, int iPtPos) const
{
	size_t szNumOfTriangles = mTriangles->size();
	if (szTriangle >= szNumOfTriangles)
		throw misc::mwIdxRangeException<size_t>(szNumOfTriangles - 1, szTriangle);

	size_t lPtIndex = (*mTriangles)[szTriangle].GetPointIndex(iPtPos);
	return (*mPoints)[lPtIndex];
}
/// Check, is triangle additional data supported
///
/// @return true if triangle additional data supported
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
bool mwContainerMesh<T, _TVertex, _TFaceNormal>::IsTriangleAdditionalDataSupport() const
{
	return false;
}
/// Set additional data for specified triangle
///
/// @param triangleIdx triangle index
/// @param data triangle additional data
/// @return none
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
void mwContainerMesh<T, _TVertex, _TFaceNormal>::SetTriangleAdditionalData(
	const size_t triangleIdx, const unsigned short data)
{
	// Not used in general mesh container
	MW_UNREFERENCED_PARAMETER(triangleIdx);
	MW_UNREFERENCED_PARAMETER(data);
	MW_EXCEPTION("Not implemented");
}
/// Get additional data from specified triangle
/// This is only used for sub-classes e.g. cadcam::mwColoredMesh
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
	unsigned short mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleAdditionalData(
		const size_t) const
{
	// Not used in general mesh container
	MW_EXCEPTION("Not implemented");
}
/// Get the triangles of this mesh
///
/// @note A triangle contains only indices to the points in the point array of this mesh!
/// @return the mTriangles array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TriangleArray&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangles()
{
	return *mTriangles;
}
/// Get the triangles of this mesh, const version
///
/// @note A triangle contains only indices to the points in the point array of this mesh!
/// @return the mTriangles array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TriangleArray&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangles() const
{
	return *mTriangles;
}
/// Get points
///
/// @return the mPoints array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::pointArray&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetPoints()
{
	return *mPoints;
}
/// Get points
///
/// @return the mPoints array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::pointArray&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetPoints() const
{
	return *mPoints;
}
/// Get vertex normals
///
/// @return the mNormals array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::normalArray&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetVertexNormals()
{
	return *mNormals;
}
/// Get vertex normals
///
/// @return the mNormals array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::normalArray&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetVertexNormals() const
{
	return *mNormals;
}
/// Get triangles as mwAutoPointer
///
/// Get the triangles of this mesh
/// @note A triangle contains only indices to the points in the point array of this mesh!
/// @return the mTriangles array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline misc::mwAutoPointer<typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TriangleArray>
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTrianglesAutoPointer() const
{
	return mTriangles;
}
/// Set new points and triangles of the mesh, discarding whatever was previous in mesh
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::SetTriangles(
	const misc::mwAutoPointer<pointArray>& points,
	const misc::mwAutoPointer<TriangleArray>& triangles)
{
	mPoints = points;
	mTriangles = triangles;
}
/// Get points as mwAutoPointer
///
/// @return the mPoints array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline misc::mwAutoPointer<typename mwContainerMesh<T, _TVertex, _TFaceNormal>::pointArray>
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetPointsAutoPointer() const
{
	return mPoints;
}
/// Get specified triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @return the triangle
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::Triangle&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangle(const size_t szTriangle) const
{
	return (*mTriangles)[szTriangle];
}
/// Assignment operator
///
/// @param tc mesh to assign
/// @return the mesh
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::MyType&
mwContainerMesh<T, _TVertex, _TFaceNormal>::operator=(const MyType& tc)
{
	if (&tc == this)
		return *this;
	SetMesh(tc);
	return *this;
}
/// Reset mesh
///
/// Clears the array of Vertices and the array of Triangles.
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::ResetMesh()
{
	mPoints->clear();
	mTriangles->clear();
	mNormals->clear();
}
/// Recalculate the normals of a given triangle.
///
/// @param szTriangle index of the triangle in the triangleArray.
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::RecalculateNormalsForATriangle(
	const size_t szTriangle)
{
	size_t szNumOfTriangles = mTriangles->size();
	if (szTriangle >= szNumOfTriangles)
		throw misc::mwIdxRangeException<size_t>(szNumOfTriangles - 1, szTriangle);
	RecalculateNormalsForATriangleNoCheck(szTriangle);
}
/// Recalculate the normals of the triangles that contains the given vertex.
///
/// @param szVertex index of the vertex in the pointArray.
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::RecalculateNormalsForAVertex(
	const size_t szVertex)
{
	const size_t iSize = mTriangles->size();
	int iCnt = 0;
	for (size_t i = 0; i < iSize && iCnt < 3; ++i)
	{
		if ((*mTriangles)[i].GetFirstPointIndex() == szVertex ||
			(*mTriangles)[i].GetSecondPointIndex() == szVertex ||
			(*mTriangles)[i].GetThirdPointIndex() == szVertex)
		{
			RecalculateNormalsForATriangleNoCheck(i);
			++iCnt;
		}
	}
}
/// Recalculate the normals of the triangles.
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::RecalculateNormals()
{
	for (size_t i = 0; i < mTriangles->size(); ++i)
	{
		RecalculateNormalsForATriangleNoCheck(i);
	}
}
/// Recompute and normalize the normals of the triangles.
///
/// Throws an exception if any degenerate triangle.
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::RecalculateAndNormalizeNormals()
{
	const size_t iSize = mTriangles->size();
	for (size_t i = 0; i < iSize; ++i)
	{
		Triangle& triangle = (*mTriangles)[i];
		const TVertex& pt1 = (*mPoints)[triangle.GetPointIndex(Triangle::FIRST_POINT)];
		const TVertex& pt2 = (*mPoints)[triangle.GetPointIndex(Triangle::SECOND_POINT)];
		const TVertex& pt3 = (*mPoints)[triangle.GetPointIndex(Triangle::THIRD_POINT)];
		TVertex normal = (pt3 - pt2) % (pt1 - pt2);
		normal.Normalize();
		triangle.SetNormal(TFaceNormal(normal.x(), normal.y(), normal.z()));
	}
}
/// Set the point's position
///
/// This method changes the position of a vertex, so please make sure you recalculate
/// the normals for the affected triangles, by calling RecalculateNormals()
/// or RecalculateNormalsForAVertex().
/// @param szPointIndex index of the point in the pointArray
/// @param pt vertex to set
/// @param recalculateNormals should vertex normals be recalculated?
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::SetVertexPosition(
	const size_t szPointIndex, const point3d& pt, const bool recalculateNormals)
{
	size_t szPtSize = mPoints->size();
	if (szPointIndex >= szPtSize)
		throw misc::mwIdxRangeException<size_t>(szPtSize - 1, szPointIndex);

	(*mPoints)[szPointIndex].x(pt.x());
	(*mPoints)[szPointIndex].y(pt.y());
	(*mPoints)[szPointIndex].z(pt.z());
	if (recalculateNormals)
		RecalculateNormalsForAVertex(szPointIndex);
}
/// Set the point
///
/// This method changes the position of a vertex, so please make sure you recalculate
/// the normals for the affected triangles, by calling RecalculateNormals()
/// or RecalculateNormalsForAVertex().
/// @param szPointIndex index of the point in the pointArray
/// @param pt point to set
/// @param recalculateNormals should we recalculate normals for a vertex?
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::SetPoint(
	const size_t szPointIndex, const TVertex pt, const bool recalculateNormals)
{
	size_t szPtSize = mPoints->size();
	if (szPointIndex >= szPtSize)
		throw misc::mwIdxRangeException<size_t>(szPtSize - 1, szPointIndex);

	(*mPoints)[szPointIndex] = pt;
	if (recalculateNormals)
		RecalculateNormalsForAVertex(szPointIndex);
}
/// Get number of points
///
/// @return the number of points in the mesh
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline size_t mwContainerMesh<T, _TVertex, _TFaceNormal>::GetNumberOfPoints() const
{
	return mPoints->size();
}
/// Get number of normals
///
/// @return the number of normals in the mesh
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline size_t mwContainerMesh<T, _TVertex, _TFaceNormal>::GetNumberOfVertexNormals() const
{
	return mNormals->size();
}
/// Get the point
///
/// @param szPointIndex index of the point in the pointArray
/// @return the vertex point
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TVertex&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetPoint(const size_t szPointIndex) const
{
	size_t szPtSize = mPoints->size();
	if (szPointIndex >= szPtSize)
		throw misc::mwIdxRangeException<size_t>(szPtSize - 1, szPointIndex);

	return (*mPoints)[szPointIndex];
}
/// Get the normal
///
/// @param szNormalIndex index of the normal in the normalArray
/// @return the vertex normal
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TFaceNormal&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetVertexNormal(const size_t szNormalIndex) const
{
	size_t szNormSize = mNormals->size();
	if (szNormalIndex >= szNormSize)
		throw misc::mwIdxRangeException<size_t>(szNormSize - 1, szNormalIndex);

	return (*mNormals)[szNormalIndex];
}
/// Get points end iterator - const version
///
/// @return the pointer to the end of the mPoints array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::constPointIt
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetPointsEnd() const
{
	return mPoints->end();
}
/// Get points begin iterator - const version
///
/// @return the pointer to the first element in the mPoints array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::constPointIt
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetPointsBegin() const
{
	return mPoints->begin();
}
/// Get points end iterator
///
/// @return the pointer to the end of the mPoints array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::PointIt
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetPointsEnd()
{
	return mPoints->end();
}
/// Get points begin iterator
///
/// @return the pointer to the first element in the mPoints array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::PointIt
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetPointsBegin()
{
	return mPoints->begin();
}
/// Get normal end iterator - const version
///
/// @return the pointer to the end of the mNormals array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::constNormalIt
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetVertexNormalsEnd() const
{
	return mNormals->end();
}
/// Get normal begin iterator - const version
///
/// @return the pointer to the first element in the mNormals array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::constNormalIt
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetVertexNormalsBegin() const
{
	return mNormals->begin();
}
/// Get normal end iterator
///
/// @return the pointer to the end of the mNormals array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::NormalIt
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetVertexNormalsEnd()
{
	return mNormals->end();
}
/// Get normal begin iterator
///
/// @return the pointer to the first element in the mNormals array
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::NormalIt
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetVertexNormalsBegin()
{
	return mNormals->begin();
}
/// Get number of triangles in the mesh
///
/// @return the number of triangles in the mesh
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline size_t mwContainerMesh<T, _TVertex, _TFaceNormal>::GetNumberOfTriangles() const
{
	return mTriangles->size();
}

/// Set normal vector of specified triangle
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::SetTriangleNormalVector(
	const size_t szTriangle, const mwTPoint3d<T>& normal)
{
	size_t szNumOfTriangles = mTriangles->size();
	if (szTriangle >= szNumOfTriangles)
		throw misc::mwIdxRangeException<size_t>(szNumOfTriangles - 1, szTriangle);

	if (mathdef::is_zero(normal.Length2()))
	{
		MW_EXCEPTION("Triangle invalid normal. ");
	}

	(*mTriangles)[szTriangle].SetNormalVector(normal);
}

/// Compute the area of the specified triangle
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline T mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleArea(const size_t szTriangle) const
{
	size_t szNumOfTriangles = mTriangles->size();
	if (szTriangle >= szNumOfTriangles)
		throw misc::mwIdxRangeException<size_t>(szNumOfTriangles - 1, szTriangle);

	point3d pt1 = GetTriangleFirstVertexPosition(szTriangle);
	point3d pt2 = GetTriangleSecondVertexPosition(szTriangle);
	point3d pt3 = GetTriangleThirdVertexPosition(szTriangle);
	return (T)0.5 * ~((pt3 - pt2) % (pt1 - pt2));
}

/// Get the normal vector of the specified triangle
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::point3d
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetNormal(const size_t szTriangle) const
{
	size_t szNumOfTriangles = mTriangles->size();
	if (szTriangle >= szNumOfTriangles)
		throw misc::mwIdxRangeException<size_t>(szNumOfTriangles - 1, szTriangle);

	point3d pt1 = GetTriangleFirstVertexPosition(szTriangle);
	point3d pt2 = GetTriangleSecondVertexPosition(szTriangle);
	point3d pt3 = GetTriangleThirdVertexPosition(szTriangle);
	return point3d((pt3 - pt2) % (pt1 - pt2));
}

/// Compute the triangles centroid
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::point3d
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleCentroid(const size_t szTriangle) const
{
	size_t szNumOfTriangles = mTriangles->size();
	if (szTriangle >= szNumOfTriangles)
		throw misc::mwIdxRangeException<size_t>(szNumOfTriangles - 1, szTriangle);

	const point3d pt1 = GetTriangleFirstVertexPosition(szTriangle);
	const point3d pt2 = GetTriangleSecondVertexPosition(szTriangle);
	const point3d pt3 = GetTriangleThirdVertexPosition(szTriangle);
	return point3d((pt1 + pt2 + pt3) / static_cast<T>(3.0));
}

/// Get the normal vector of a triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @return the triangle normal vector
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::point3d
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleNormalVector(const size_t szTriangle) const
{
	size_t szNumOfTriangles = mTriangles->size();
	if (szTriangle >= szNumOfTriangles)
		throw misc::mwIdxRangeException<size_t>(szNumOfTriangles - 1, szTriangle);

	return (*mTriangles)[szTriangle].GetNormalVector();
}
/// Get the Data of a triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @return the triangle normal vector
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TFaceNormal&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleData(const size_t szTriangle) const
{
	size_t szNumOfTriangles = mTriangles->size();
	if (szTriangle >= szNumOfTriangles)
		throw misc::mwIdxRangeException<size_t>(szNumOfTriangles - 1, szTriangle);

	return (*mTriangles)[szTriangle].GetData();
}
/// Get the third vertex point of a triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @return the third vertex point of the triangle
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::point3d
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleThirdVertexPosition(
	const size_t szTriangle) const
{
	return GetTriangleVertexPosition(szTriangle, 2);
}
/// Get the second vertex point of a triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @return the second vertex point of the triangle
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::point3d
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleSecondVertexPosition(
	const size_t szTriangle) const
{
	return GetTriangleVertexPosition(szTriangle, 1);
}
/// Get the first vertex point of a triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @return the first vertex point of the triangle
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::point3d
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleFirstVertexPosition(
	const size_t szTriangle) const
{
	return GetTriangleVertexPosition(szTriangle, 0);
}
/// Get the third vertex normal of a triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @return the third vertex normal of the triangle
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TFaceNormal
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleThirdVertexNormal(
	const size_t szTriangle) const
{
	return GetTriangleVertexNormal(szTriangle, 2);
}
/// Get the second vertex normal of a triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @return the second vertex normal of the triangle
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TFaceNormal
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleSecondVertexNormal(
	const size_t szTriangle) const
{
	return GetTriangleVertexNormal(szTriangle, 1);
}
/// Get the first vertex normal of a triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @return the first vertex normal of the triangle
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TFaceNormal
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleFirstVertexNormal(
	const size_t szTriangle) const
{
	return GetTriangleVertexNormal(szTriangle, 0);
}
/// Get the third vertex point of a triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @return the third vertex point of the triangle
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TVertex&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleThirdVertexData(
	const size_t szTriangle) const
{
	return GetTriangleVertexData(szTriangle, 2);
}
/// Get the second vertex point of a triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @return the second vertex point of the triangle
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TVertex&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleSecondVertexData(
	const size_t szTriangle) const
{
	return GetTriangleVertexData(szTriangle, 1);
}
/// Get the first vertex point of a triangle
///
/// @param szTriangle index of the triangle in the triangleArray
/// @return the first vertex point of the triangle
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TVertex&
mwContainerMesh<T, _TVertex, _TFaceNormal>::GetTriangleFirstVertexData(
	const size_t szTriangle) const
{
	return GetTriangleVertexData(szTriangle, 0);
}

/// Remove unreferenced points from mPoints and updates mTriangles
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::GarbageCollect()
{
	const size_t initPointCount = mPoints->size();
	unsigned pointCount = 0;

	std::vector<unsigned> indexMap(initPointCount, (unsigned)-1);
	typename TriangleArray::iterator triEnd = mTriangles->end();
	for (typename TriangleArray::iterator tri = mTriangles->begin(); tri != triEnd; ++tri)
	{
		for (int p = 0; p != 3; ++p)
		{
			size_t pIndex = tri->GetPointIndex(p);
			if (indexMap[pIndex] == (unsigned)-1)
			{
				indexMap[pIndex] = pointCount++;
			}
		}
	}

	// There is no garbage
	if (pointCount == initPointCount)
		return;

	// create new points vector
	misc::mwAutoPointer<std::vector<TVertex>> duplicateFree = new std::vector<TVertex>(pointCount);

	for (size_t pIndex = 0; pIndex < initPointCount; ++pIndex)
	{
		if (indexMap[pIndex] != (unsigned)-1)
		{
			(*duplicateFree)[indexMap[pIndex]] = (*mPoints)[pIndex];
		}
	}

	RemapTrianglePointIndices(mTriangles->begin(), mTriangles->end(), indexMap);

	// replace the points vector by the new one
	mPoints = duplicateFree;
}
/// Set Triangles from the given array of triangles to current mesh
///
/// This method initializes the Mesh with a set of triangles.
/// The set of triangles is created using the mwTTriangleVector class.
/// Please refer to the mwTTriangleVector its documentation.
/// @param triVectToSet triangles to set
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::SetTriangles(
	const TriangleVector& triVectToSet)
{
	if (triVectToSet.GetNumberOfTriangles() <= 0)
	{
		ResetMesh();
		return;
	}

	// obtain precision
	mPointCoordPrec = triVectToSet.mPointCoordPrec;

	// build help vector for sorting
	std::vector<const TVertex*> vertexArray;
	vertexArray.reserve(triVectToSet.mVertex->size());

	{
		const size_t size = triVectToSet.mVertex->size();
		const pointArray& mVertex = *(triVectToSet.mVertex);
		for (size_t cnt = 0; cnt < size; ++cnt)
		{
			vertexArray.push_back(&(mVertex[cnt]));
		}
	}

	// perform sorting
	// instead of sorting the points we sort the pointers
	{
		std::sort(vertexArray.begin(), vertexArray.end(), SortPred(triVectToSet));
	}

	unsigned newIdx = 0;
	{
		// first vertex in point array - these is needed for pointer arithmetic based
		// index calculation
		const TVertex* const base = &((*triVectToSet.mVertex)[0]);

		// map the old idx in triVectToSet.mVertex to the idx in new pointArray,
		// which will be created below
		const size_t size = vertexArray.size();
		const TVertex* pt0 = vertexArray[0];

		std::vector<unsigned> oldIdx2NewIdx(size);
		oldIdx2NewIdx.at((pt0 - base)) = newIdx;

		for (size_t i = 1; i < size; ++i)
		{
			const TVertex* pt1 = vertexArray[i];

			// compute index of pt1 in triVectToSet.mVertex
			const size_t idx = (pt1 - base);

			if (pt0->AreCoordinatesEqual(*pt1))
			{
				oldIdx2NewIdx[idx] = newIdx;
				vertexArray[i] = pt0;
			}
			else
			{
				++newIdx;
				oldIdx2NewIdx[idx] = newIdx;
				std::swap(pt0, pt1);  // update new reference point value
			}
		}

		bool shareTrianglesPointer =
			(mTriangles.operator->() == triVectToSet.mTriangles.operator->());
		if (!shareTrianglesPointer)
		{
			// create a copy of triangles
			mTriangles = new TriangleArray(*triVectToSet.mTriangles);
		}

		// map the triangle point indices to the new indices of points
		RemapTrianglePointIndices(mTriangles->begin(), mTriangles->end(), oldIdx2NewIdx);
	}

	{
		// copy the different points to new pointArray
		bool sharePointsPointer =
			(mPoints.operator->() == triVectToSet.mVertex.operator->());

		misc::mwAutoPointer<pointArray> differentPoints =
			(sharePointsPointer) ? new pointArray() : mPoints;
		differentPoints->clear();
		differentPoints->resize(newIdx + 1);
		(*differentPoints)[0] = *(vertexArray[0]);

		TVertex* nextPoint = &((*differentPoints)[1]);

		// copy different points
		const size_t size = vertexArray.size();
		for (size_t i = 1; i < size; ++i)
		{
			if (vertexArray[i] != vertexArray[i - 1])
			{
				(*nextPoint) = *(vertexArray[i]);
				++nextPoint;
			}
		}
		mPoints = differentPoints;
	}

	{
		bool shareNormalsPointer =
			(mNormals.operator->() == triVectToSet.mNormals.operator->());
		if (!shareNormalsPointer)
		{
			// copy the normals
			mNormals = new normalArray(*triVectToSet.mNormals);
		}
	}
}
/// Remove repeated points in mPoints and updates mTriangles
///
/// Removes points considered to be equal according to PointsCloseEnough
/// and updates the triangle indexes so that the geometry is preserved.
/// @param fEpsilon square of the minimum distance between points to be considered close enough to
/// be considered equal
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::RemoveDuplicatesSlow(const T fEpsilon)
{
	// copy the points from mPoints to a new vector

	const size_t initPointCount = mPoints->size();
	// create new points vector
	std::vector<TVertex> duplicateFree;
	duplicateFree.reserve(initPointCount);

	// indexMap is used to remap the points of the triangles to the points in the vector
	//"indexMap[i]" is the new index of the point at index "i" in the old vector
	std::vector<unsigned> indexMap(initPointCount, 0);
	bool hadDuplicates = false;

	for (size_t idx1 = 0; idx1 < initPointCount; ++idx1)
	{
		// check if it exists already in the new vector
		bool point_found = false;
		const size_t duplicateFreeSize = duplicateFree.size();
		for (size_t idx2 = 0; idx2 < duplicateFreeSize; ++idx2)
		{
			if (PointsCloseEnough((*mPoints)[idx1], duplicateFree[idx2], fEpsilon))
			{
				// duplicate point found, use the point that is already in the vector and its' index
				point_found = true;
				indexMap[idx1] = (unsigned)idx2;
			}
		}

		if (point_found == false)
		{
			// not a duplicate, so insert it and set its' new index at the correct position in the
			// new vector
			indexMap[idx1] = (unsigned)duplicateFreeSize;
			duplicateFree.push_back((*mPoints)[idx1]);
		}
		else
		{
			hadDuplicates = true;
		}
	}

	if (hadDuplicates)
	{
		RemapTrianglePointIndices(mTriangles->begin(), mTriangles->end(), indexMap);
	}

	// replace the points vector by the new one
	mPoints->swap(duplicateFree);

	//// debug code -create degenerate triangles
	/// TriangleArray::iterator dt_it_end = mTriangles->end();
	/// for(TriangleArray::iterator t_it = mTriangles->begin(); t_it != dt_it_end ; ++t_it )
	/// {
	///	if( t_it->GetFirstPointIndex() == 9 ||  t_it->GetFirstPointIndex() == 10 ||
	///t_it->GetFirstPointIndex() == 11)
	///	{
	///		t_it->SetFirstPointIndex(1);
	///	}
	///	if( t_it->GetSecondPointIndex() == 9 || t_it->GetSecondPointIndex() == 10 ||
	///t_it->GetSecondPointIndex() == 11)
	///	{
	///		t_it->SetSecondPointIndex(1);
	///	}
	///	if(	t_it->GetThirdPointIndex() == 9 || t_it->GetThirdPointIndex() == 10 ||
	///t_it->GetThirdPointIndex() == 11)
	///	{
	///		t_it->SetThirdPointIndex(1);
	///	}
	/// }
	//// end debug code

	/// erase possible degenerate triangles
	mTriangles->erase(
		std::remove_if(mTriangles->begin(), mTriangles->end(), RemoveDegeneratedTrianglePredicate),
		mTriangles->end());

	// remove non referenced points
	std::vector<TVertex> unreferencedFree;
	const size_t uniquePointCount = mPoints->size();
	unreferencedFree.reserve(uniquePointCount);
	std::vector<bool> isReferenced(uniquePointCount, false);

	typename TriangleArray::iterator triEnd = mTriangles->end();
	for (typename TriangleArray::iterator tri = mTriangles->begin(); tri != triEnd; ++tri)
	{
		isReferenced[tri->GetFirstPointIndex()] = true;
		isReferenced[tri->GetSecondPointIndex()] = true;
		isReferenced[tri->GetThirdPointIndex()] = true;
	}

	for (size_t idx1 = 0; idx1 < uniquePointCount; ++idx1)
	{
		if (isReferenced[idx1])
		{
			indexMap[idx1] = (unsigned)unreferencedFree.size();
			unreferencedFree.push_back((*mPoints)[idx1]);
		}
	}

	RemapTrianglePointIndices(mTriangles->begin(), mTriangles->end(), indexMap);

	// replace the points vector by the new one
	mPoints->swap(unreferencedFree);
}
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline bool mwContainerMesh<T, _TVertex, _TFaceNormal>::RemoveDegeneratedTrianglePredicate(
	const Triangle& t)
{
	return (
		t.GetFirstPointIndex() == t.GetSecondPointIndex() ||
		t.GetSecondPointIndex() == t.GetThirdPointIndex() ||
		t.GetFirstPointIndex() == t.GetThirdPointIndex());
}
/// Check if two points are close to each other
///
/// Check if the squared distance between two points is no more than fEpsilon
/// @param pt1 first point
/// @param pt2 second point
/// @param fEpsilon square of the minimum distance between points to be considered close enough
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline bool mwContainerMesh<T, _TVertex, _TFaceNormal>::PointsCloseEnough(
	const TVertex& pt1, const TVertex& pt2, const T fEpsilon /*= (T)mathdef::MW_MATH_TOL_SQR*/)
{
	point3d fDiff = pt1 - pt2;
	if (fDiff.Length2() <= fEpsilon)
		return true;
	return false;
}
/// Add triangles from the given mesh to current mesh
///
/// This method combines two meshes into one.
/// It doesn't examine src mesh but just appends the points from it to the mPoints point
/// array. We should not look for duplicate point searching since this takes time and benefits will
/// not be too high, since only some common boundary points will be duplicate and we will not save
/// much.(Yavuz) The triangles are simply appended to the mTriangles triangle array.
/// @param src mesh to add
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::AddMeshFastButDontCareDuplicates(
	const MyType& src)
{
	if (GetUnits() != src.GetUnits())
		throw misc::mwException(3512, _T("Could not merge two meshes with different units type"));

	if (mathdef::is_neq(GetPointCoordPrec(), src.GetPointCoordPrec()))
		throw misc::mwException(
			3515, _T("Could not merge two meshes with different point coordinates precision"));

	const size_t thisPntCount = GetNumberOfPoints();
	const size_t srcPntCount = src.GetNumberOfPoints();

	if (!srcPntCount)
		return;  // source mesh is empty

	if (!thisPntCount)
	{  // myself is an empty mesh
		SetMesh(src);
		RecalculateNormals();
		return;
	}

	const size_t thisTriangleCount = GetNumberOfTriangles();
	const size_t srcTriangleCount = src.GetNumberOfTriangles();

	const size_t thisNormalCount = GetNumberOfVertexNormals();
	const size_t srcNormalCount = src.GetNumberOfVertexNormals();


	ReserveAndReallocate(*mPoints, thisPntCount + srcPntCount);
	ReserveAndReallocate(*mNormals, thisNormalCount + srcNormalCount);
	ReserveAndReallocate(*mTriangles, thisTriangleCount + srcTriangleCount);

	std::copy(src.GetPointsBegin(), src.GetPointsEnd(), std::back_inserter(*mPoints));
	std::copy(
		src.GetVertexNormalsBegin(), src.GetVertexNormalsEnd(), std::back_inserter(*mNormals));

	for (size_t i = 0; i < srcTriangleCount; ++i)
	{
		Triangle triangle = src.GetTriangle(i);
		for (int j = 0; j < 3; ++j)
		{
			triangle.SetPointIndex(j, triangle.GetPointIndex(j) + thisPntCount);
			if (triangle.GetNormalIndex(j) > -1)
			{
				triangle.SetNormalIndex(j, triangle.GetNormalIndex(j) + (int)thisNormalCount);
			}
		}
		mTriangles->push_back(triangle);
		RecalculateNormalsForATriangleNoCheck(mTriangles->size() - 1);
	}
}
///	Reserve memory for mesh points
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::ReserveTriangles(size_t capacity)
{
	mTriangles->reserve(capacity);
}
///	Reserve memory for mesh points
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::ReservePoints(size_t capacity)
{
	mPoints->reserve(capacity);
}
/// Add triangles from the given mesh to current mesh
///
/// This method combines two meshes into one.
/// It examines the toAdd mesh and inserts the points from it into the mPoints point array
/// preserving the sorted order. The triangles are simply appended to the mTriangles triangle array.
/// @param toAdd mesh to add
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::AddMesh(const MyType& toAdd)
{
	if (GetUnits() != toAdd.GetUnits())
	{
		throw misc::mwException(
			3512, misc::mwstring(_T("Could not merge two meshes with different units type")));
	}

	if (mathdef::is_neq(GetPointCoordPrec(), toAdd.GetPointCoordPrec()))
	{
		throw misc::mwException(
			3515,
			misc::mwstring(
				_T("Could not merge two meshes with different point coordinates precision")));
	}

	const size_t szPtSize = GetNumberOfPoints();
	const size_t szNewPtSize = toAdd.GetNumberOfPoints();
	if (szPtSize == 0)
	{
		SetMesh(toAdd);
	}
	else
	{
		pointArray aOldPoints;
		aOldPoints.swap(*mPoints);

		mPoints->clear();
		mPoints->reserve(szPtSize + szNewPtSize + 2);
		mTriangles->reserve(GetNumberOfTriangles() + toAdd.GetNumberOfTriangles() + 2);

		std::vector<unsigned> aOldOffsets;
		std::vector<unsigned> aNewOffsets;
		aOldOffsets.reserve(szPtSize + 2);
		aNewOffsets.reserve(szNewPtSize + 2);

		{
			constPointIt it = toAdd.GetPointsBegin();
			constPointIt ite = toAdd.GetPointsEnd();

			size_t sz1 = 0;
			TVertex pt1;
			TVertex pt2;

			while (sz1 < szPtSize && it != ite)
			{
				pt1 = aOldPoints[sz1];
				pt2 = *(it);

				if (ComparePoints(pt1, pt2, mPointCoordPrec))
				{
					aOldOffsets.push_back((unsigned)mPoints->size());
					mPoints->push_back(pt1);
					sz1++;
				}
				else if (ComparePoints(pt2, pt1, mPointCoordPrec))
				{
					aNewOffsets.push_back((unsigned)mPoints->size());
					mPoints->push_back(pt2);
					++it;
				}
				else
				{
					aOldOffsets.push_back((unsigned)mPoints->size());
					aNewOffsets.push_back((unsigned)mPoints->size());
					mPoints->push_back(pt1);
					++sz1;
					++it;
				}
			}
			while (sz1 < szPtSize)
			{
				pt1 = aOldPoints[sz1];
				aOldOffsets.push_back((unsigned)mPoints->size());
				mPoints->push_back(pt1);
				++sz1;
			}
			while (it != ite)
			{
				pt2 = *(it);
				aNewOffsets.push_back((unsigned)mPoints->size());
				mPoints->push_back(pt2);
				++it;
			}
		}

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4239)
#endif
		std::vector<TVertex> tmpPoints(*mPoints);
		mPoints->swap(tmpPoints);
#ifdef _WIN32
#pragma warning(pop)
#endif

		const TriangleIt oldEnd = mTriangles->end();
		for (TriangleIt tri = mTriangles->begin(); tri != oldEnd; ++tri)
		{
			tri->SetFirstPointIndex(aOldOffsets[tri->GetFirstPointIndex()]);
			tri->SetSecondPointIndex(aOldOffsets[tri->GetSecondPointIndex()]);
			tri->SetThirdPointIndex(aOldOffsets[tri->GetThirdPointIndex()]);
		}

		const unsigned lastVertexNormalIdx = (unsigned)this->mNormals->size();
		// Add vertex normals into the current mesh
		this->mNormals->insert(
			this->mNormals->end(), toAdd.mNormals->begin(), toAdd.mNormals->end());

		const constTriangleIt newEnd = toAdd.mTriangles->end();
		for (constTriangleIt it = toAdd.mTriangles->begin(); it != newEnd; ++it)
		{
			mTriangles->push_back(*it);
			Triangle& triangle = mTriangles->back();
			triangle.SetFirstPointIndex(aNewOffsets[triangle.GetFirstPointIndex()]);
			triangle.SetSecondPointIndex(aNewOffsets[triangle.GetSecondPointIndex()]);
			triangle.SetThirdPointIndex(aNewOffsets[triangle.GetThirdPointIndex()]);

			if (toAdd.mNormals->begin() != toAdd.mNormals->end())
			{
				int n1, n2, n3;
				triangle.GetNormalIndices(n1, n2, n3);
				triangle.SetNormalIndices(
					n1 > -1 ? n1 + lastVertexNormalIdx : n1,
					n2 > -1 ? n2 + lastVertexNormalIdx : n2,
					n3 > -1 ? n3 + lastVertexNormalIdx : n3);
			}
		}
	}
}
/// Set Triangles from the given mesh to current mesh
///
/// @param toSet mesh to set
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::SetMesh(const MyType& toSet)
{
	if (mPoints.use_count() > 1)
		mPoints = new pointArray;
	if (mTriangles.use_count() > 1)
		mTriangles = new TriangleArray;
	if (mNormals.use_count() > 1)
		mNormals = new normalArray;
	*mPoints = *toSet.mPoints;
	*mTriangles = *toSet.mTriangles;
	*mNormals = *toSet.mNormals;
	SetUnits(toSet.GetUnits(), true);
	mPointCoordPrec = toSet.mPointCoordPrec;
}
/// Copies the points and/or triangles if they are referenced more than once.
///
/// Call shortly before you plan to modify either of them to avoid corrupting
/// ....other meshes that use the same point and/or triangle vector
/// @param points if true, points will be copied when referenced more than once
/// @param triangles if true, triangles will be copied when referenced more than once
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::CopyForWrite(bool points, bool triangles)
{
	if (points && mPoints.use_count() > 1)
		mPoints = new pointArray(*mPoints);
	if (triangles && mTriangles.use_count() > 1)
		mTriangles = new TriangleArray(*mTriangles);
}
/// Get normal vector of the Triangle surface
///
/// @param pt1 first point of the triangle
/// @param pt2 second point of the triangle
/// @param pt3 third point of the triangle
/// @param normal normal point of the mTriangles surface
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::GetNormal(
	const TVertex& pt1, const TVertex& pt2, const TVertex& pt3, TFaceNormal& normal) const
{
	if (mathdef::is_eq(normal.x(), 0, mPointCoordPrec) &&
		(mathdef::is_eq(normal.y(), 0, mPointCoordPrec)) &&
		(mathdef::is_eq(normal.z(), 0, mPointCoordPrec)))
		normal = ((pt3 - pt2) % (pt1 - pt2));
	normal.Normalize();
}

/// Constructor from TriangleVector
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwContainerMesh<T, _TVertex, _TFaceNormal>::mwContainerMesh(
	const TriangleVector& triVectToSet, const Units& unit)
	: measures::mwMeasurable(unit)
{
	mPoints = new pointArray;
	mTriangles = new TriangleArray;
	mNormals = new normalArray;
	SetTriangles(triVectToSet);
}

/// Constructor setting point, triangles as mwAutoPointer
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
mwContainerMesh<T, _TVertex, _TFaceNormal>::mwContainerMesh(
	misc::mwAutoPointer<pointArray> points,
	misc::mwAutoPointer<TriangleArray> triangles,
	const Units& unit,
	const T pointCoordPrec /*= mathdef::mw_tol(T())*/)
	: measures::mwMeasurable(unit)
{
	mPoints = points;
	mTriangles = triangles;
	mNormals = new normalArray;
	mPointCoordPrec = pointCoordPrec;
}

/// Constructor setting point, triangles
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwContainerMesh<T, _TVertex, _TFaceNormal>::mwContainerMesh(
	const pointArray& points,
	const TriangleArray& triangles,
	const Units& unit,
	const T pointCoordPrec)
	: measures::mwMeasurable(unit)
{
	mPoints = new pointArray(points);
	mTriangles = new TriangleArray(triangles);
	mNormals = new normalArray;
	mPointCoordPrec = pointCoordPrec;
}

#ifndef MW_USE_VS2008_COMPATIBILITY
/// Constructor setting point, triangles
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwContainerMesh<T, _TVertex, _TFaceNormal>::mwContainerMesh(
	pointArray&& points, TriangleArray&& triangles, const Units& unit, const T pointCoordPrec)
	: measures::mwMeasurable(unit)
{
	mPoints = new pointArray(std::move(points));
	mTriangles = new TriangleArray(std::move(triangles));
	mNormals = new normalArray;
	mPointCoordPrec = pointCoordPrec;
}
#endif

/// Constructor setting point, normals, triangles as mwAutoPointer
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
mwContainerMesh<T, _TVertex, _TFaceNormal>::mwContainerMesh(
	misc::mwAutoPointer<pointArray> points,
	misc::mwAutoPointer<normalArray> normals,
	misc::mwAutoPointer<TriangleArray> triangles,
	const Units& unit,
	const T pointCoordPrec /*= mathdef::mw_tol(T())*/)
	: measures::mwMeasurable(unit)
{
	mPoints = points;
	mTriangles = triangles;
	mNormals = normals;
	mPointCoordPrec = pointCoordPrec;
}

/// Constructor setting point, normals, triangles
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwContainerMesh<T, _TVertex, _TFaceNormal>::mwContainerMesh(
	const pointArray& points,
	const normalArray& normals,
	const TriangleArray& triangles,
	const Units& unit,
	const T pointCoordPrec)
	: measures::mwMeasurable(unit)
{
	mPoints = new pointArray(points);
	mTriangles = new TriangleArray(triangles);
	mNormals = new normalArray(normals);
	mPointCoordPrec = pointCoordPrec;
}

#ifndef MW_USE_VS2008_COMPATIBILITY
/// Constructor setting point, normals, triangles
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwContainerMesh<T, _TVertex, _TFaceNormal>::mwContainerMesh(
	pointArray&& points,
	normalArray&& normals,
	TriangleArray&& triangles,
	const Units& unit,
	const T pointCoordPrec)
	: measures::mwMeasurable(unit)
{
	mPoints = new pointArray(std::move(points));
	mTriangles = new TriangleArray(std::move(triangles));
	mNormals = new normalArray(std::move(normals));
	mPointCoordPrec = pointCoordPrec;
}
#endif

/// Copy constructor
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwContainerMesh<T, _TVertex, _TFaceNormal>::mwContainerMesh(const MyType& toCopy)
	: measures::mwMeasurable(toCopy.GetUnits())
{
	mPoints = new pointArray(*toCopy.mPoints);
	mTriangles = new TriangleArray(*toCopy.mTriangles);
	mNormals = new normalArray(*toCopy.mNormals);
	mPointCoordPrec = toCopy.mPointCoordPrec;
}
#ifndef MW_USE_VS2008_COMPATIBILITY
/// Move Constructor
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwContainerMesh<T, _TVertex, _TFaceNormal>::mwContainerMesh(
	mwContainerMesh<T>&& other) noexcept
	: measures::mwMeasurable(other.GetUnits()),
	  mPoints(std::move(other.mPoints)),
	  mTriangles(std::move(other.mTriangles)),
	  mNormals(std::move(other.mNormals)),
	  mPointCoordPrec(other.mPointCoordPrec)
{
	other.mPoints = NULL;
	other.mTriangles = NULL;
	other.mNormals = NULL;
}
/// Move assignment operator
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline typename mwContainerMesh<T, _TVertex, _TFaceNormal>::MyType&
mwContainerMesh<T, _TVertex, _TFaceNormal>::operator=(MyType&& other) noexcept
{
	if (&other == this)
		return *this;
	SetUnits(other.GetUnits(), true);
	mPoints = std::move(other.mPoints);
	mTriangles = std::move(other.mTriangles);
	mNormals = std::move(other.mNormals);
	mPointCoordPrec = other.mPointCoordPrec;
	other.mPoints = NULL;
	other.mTriangles = NULL;
	other.mNormals = NULL;
	return *this;
}
#endif
/// Constructor for empty mesh
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwContainerMesh<T, _TVertex, _TFaceNormal>::mwContainerMesh(
	const Units& unit, const T pointCoordPrec)
	: measures::mwMeasurable(unit)
{
	mPoints = new pointArray;
	mTriangles = new TriangleArray;
	mNormals = new normalArray;
	mPointCoordPrec = pointCoordPrec;
}
/// Destructor
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline mwContainerMesh<T, _TVertex, _TFaceNormal>::~mwContainerMesh()
{
}

/// Scale the mesh
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline void mwContainerMesh<T, _TVertex, _TFaceNormal>::Scale(
	const measures::mwUnitsFactory::Units, const double& scaleFactor)
{
	typename MyType::PointIt ItBeg = GetPointsBegin();
	typename MyType::PointIt ItEnd = GetPointsEnd();

	for (; ItBeg != ItEnd; ++ItBeg)
	{
		(*ItBeg) *= static_cast<float>(scaleFactor);
	}
}

/// Convert point to normal type
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TFaceNormalPtr
mwContainerMesh<T, _TVertex, _TFaceNormal>::Point2TFaceNormal(const point3d& point)
{
	return new TFaceNormal(point.x(), point.y(), point.z());
}

/// Convert point type to vertex type
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline const typename mwContainerMesh<T, _TVertex, _TFaceNormal>::TVertexPtr
mwContainerMesh<T, _TVertex, _TFaceNormal>::Point2TVertex(const point3d& point)
{
	return new TVertex(point.x(), point.y(), point.z());
}
/// Compares two points and returns true iff the first point is smaller according the lexicographic
/// order of the axis with tolerance
///
/// @param pt1 first point to compare
/// @param pt2 second point to compare
/// @param prec delta to check along each of the axes
/// @return true/false
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline bool mwContainerMesh<T, _TVertex, _TFaceNormal>::ComparePoints(
	const TVertex& pt1, const TVertex& pt2, const T prec)
{
	if (mathdef::is_eq(pt1.x(), pt2.x(), prec))
	{
		if (mathdef::is_eq(pt1.y(), pt2.y(), prec))
		{
			if (mathdef::is_eq(pt1.z(), pt2.z(), prec))
				return false;
			else if (pt1.z() < pt2.z())
				return true;
			else
				return false;
		}
		else if (pt1.y() < pt2.y())
			return true;
		else
			return false;
	}
	else if (pt1.x() < pt2.x())
		return true;
	else
		return false;
}

/// Inequality operator
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline bool mwContainerMesh<T, _TVertex, _TFaceNormal>::operator!=(const mwContainerMesh& tc) const
{
	return !(*this == tc);
}

/// Equality operator
///
/// Meshes are considered equal if they have the same point precision and the triangles
/// are the same in terms of their order, order of vertices in the triangle and exact
/// point coordinates and normals. The order of the point data is not checked.
template <
	typename T,
	typename _TVertex /*= mwTPoint3d<T>*/,
	typename _TFaceNormal /*= mwTPoint3d<T> */>
inline bool mwContainerMesh<T, _TVertex, _TFaceNormal>::operator==(const mwContainerMesh& tc) const
{
	if (this == &tc)
		return true;

	// Triangles comparison
	{
		if (mTriangles.IsNull() ^ tc.mTriangles.IsNull())
		{
			return false;
		}

		if (!mTriangles.IsNull())
		{
			if (mTriangles->size() != tc.mTriangles->size())
			{
				return false;
			}
			if (mTriangles->size() > 0)
			{
				if (mPoints.IsNull())
				{
					return false;
				}

				try
				{
					const pointArray& points = (*mPoints);
					const pointArray& tcPoints = (*tc.mPoints);
					// Individual indices or points in containers maybe different, but it is only
					// important that actual TRIANGLE points and normals are equal
					typename TriangleArray::const_iterator it = mTriangles->begin();
					typename TriangleArray::const_iterator endIt = mTriangles->end();
					typename TriangleArray::const_iterator tcIt = tc.mTriangles->begin();
					for (size_t k = 0; it != endIt; ++it, ++tcIt, ++k)
					{
						const Triangle& t0 = (*it);
						const Triangle& t1 = (*tcIt);

						if (points[t0.GetFirstPointIndex()] != tcPoints[t1.GetFirstPointIndex()] ||
							points[t0.GetSecondPointIndex()] !=
								tcPoints[t1.GetSecondPointIndex()] ||
							points[t0.GetThirdPointIndex()] != tcPoints[t1.GetThirdPointIndex()] ||
							t0.GetNormalVector() != t1.GetNormalVector() ||
							GetTriangleFirstVertexNormal(k) != tc.GetTriangleFirstVertexNormal(k) ||
							GetTriangleSecondVertexNormal(k) !=
								tc.GetTriangleSecondVertexNormal(k) ||
							GetTriangleThirdVertexNormal(k) != tc.GetTriangleThirdVertexNormal(k))
						{
							return false;
						}
					}
				}
				catch (...)
				{
					return false;
				}
			}
		}
	}

	if (mPointCoordPrec != tc.mPointCoordPrec)
	{
		return false;
	}

	if (GetUnits() != tc.GetUnits())
	{
		return false;
	}

	return true;
}

template <typename T>
inline misc::mwLogger& operator<<(misc::mwLogger& os, const mwContainerMesh<T>& toDump)
{
	os << _T("class cadcam::mwContainerMesh\n");
	// public properties from cadcam::mwContainerMesh class.
	os << _T("GetNumberOfTriangles            = ") << toDump.GetNumberOfTriangles() << _T("\n");
	os << _T("GetNumberOfPoints               = ") << toDump.GetNumberOfPoints() << _T("\n");
	return os;
}
#pragma CACHING_INTERNAL_END
}  // namespace cadcam
#endif  //	MW_MWCONTAINERMESH_HPP_
