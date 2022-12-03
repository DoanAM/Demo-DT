// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMESHVNORM_HPP_
#define MW_MWMESHVNORM_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwMesh.hpp"
#include "mwTrig.hpp"

#include <mwVector.hpp>
#include <mwVectorUtils.hpp>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <vector>

#if defined(_WIN32)
#elif defined(__linux__) || defined(__APPLE__)
#ifndef MW_FORCEINLINE
#define MW_FORCEINLINE
#endif
#endif

namespace cadcam
{
/// This class represents an extended mesh.
template <typename T>
class MW_5AXUTIL_API mwTMeshVNorm: public mwTMesh<T>
{
public:
	typedef T ValueType;
	typedef misc::mwAutoPointer<mwTMeshVNorm<T>> Ptr;
	typedef typename mwTMesh<T>::Ptr MeshPtr;
	typedef typename mwTMesh<T>::TriangleVector TriangleVector;
	typedef typename mwTMesh<T>::Triangle Triangle;
	typedef typename mwTMesh<T>::TriangleArray TriangleArray;

	typedef mwTPoint3d<T> point3d;
	typedef std::vector<point3d> pointArray;
	typedef typename pointArray::const_iterator constPointIt;
	typedef typename pointArray::iterator PointIt;

	typedef typename mwTMesh<T>::TVertex TVertex;

	/// Mesh units type
	typedef measures::mwMeasurable::Units Units;

private:
	class mwTPoint3dTInd
	{
	public:
		/// Default constructor
		inline mwTPoint3dTInd(): mTriIndex(0), mPtIndex(0) {}

		/// Get point
		///
		/// @return the actual point
		inline const TVertex& GetPoint() const { return mPoint; }

		/// Get triangle index
		///
		/// @return the index of the triangle in the triangleArray
		inline size_t GetTriangleIndex() const { return mTriIndex; }

		/// Get point index
		///
		/// @return the index of the point in the triangle
		inline int GetPointIndex() const { return mPtIndex; }

		/// Set point index
		///
		/// @param PtIndex the index of the point in the triangle
		inline void SetPointIndex(int PtIndex) { mPtIndex = PtIndex; }

		/// Constructor
		///
		/// @param ptPoint actual point
		/// @param szTriIndex index of the triangle in the triangleArray
		/// @param iPtIndex the index of the point in the triangle
		inline mwTPoint3dTInd(const TVertex& ptPoint, size_t szTriIndex, int iPtIndex)
		{
			mPoint = ptPoint;
			mTriIndex = (unsigned)szTriIndex;
			mPtIndex = iPtIndex;
		}

		/// Destructor
		inline ~mwTPoint3dTInd() {}

	private:
		TVertex mPoint;
		unsigned mTriIndex;
		int mPtIndex;
	};

	typedef mwTPoint3dTInd point3dTInd;
	typedef std::vector<point3dTInd> pointTIndArray;
	typedef typename pointTIndArray::const_iterator constPointTIndIt;

public:
	/// This class represents TriangleNeighbors
	/// and contains the indexes to the triangles in the TriangleArray
	template <typename Y>
	class mwTTriangleNeighbors
	{
	public:
		/// Sets the specified point index
		/// @param iTriNeighbor specifies the index of triangle neighbor
		/// @param szNewTriIndex of type size_t - the index of the point in the pointArray
		MW_FORCEINLINE void SetNeighborIndex(int iTriNeighbor, size_t szNewTriIndex)
		{
			if (iTriNeighbor < FIRST_NEIGHBOR || iTriNeighbor > THIRD_NEIGHBOR)
				throw misc::mwException(22639, _T("Invalid array access"));

			m_szTriangleNeighbor[iTriNeighbor] = szNewTriIndex;
		}

		/// @param szNewTriIndex set first neighbor triangle index
		MW_FORCEINLINE void SetFirstNeighborIndex(size_t szNewTriIndex)
		{
			m_szTriangleNeighbor[FIRST_NEIGHBOR] = (unsigned)szNewTriIndex;
		}

		/// @param szNewTriIndex set second neighbor triangle index
		MW_FORCEINLINE void SetSecondNeighborIndex(size_t szNewTriIndex)
		{
			m_szTriangleNeighbor[SECOND_NEIGHBOR] = (unsigned)szNewTriIndex;
		}

		/// @param szNewTriIndex set third neighbor triangle index
		MW_FORCEINLINE void SetThirdNeighborIndex(size_t szNewTriIndex)
		{
			m_szTriangleNeighbor[THIRD_NEIGHBOR] = (unsigned)szNewTriIndex;
		}

		/// GetNeighborIndex method
		///
		/// @return the index of the specified triangle in the triangleArray
		MW_FORCEINLINE size_t GetNeighborIndex(int iTriNeighbor) const
		{
			if (iTriNeighbor < FIRST_NEIGHBOR || iTriNeighbor > THIRD_NEIGHBOR)
				throw misc::mwException(22639, _T("Invalid array access"));

			return m_szTriangleNeighbor[iTriNeighbor];
		}

		/// @return the index of the first triangle point in the pointArray
		MW_FORCEINLINE size_t GetFirstNeighborIndex() const
		{
			return m_szTriangleNeighbor[FIRST_NEIGHBOR];
		}

		/// @return the index of the second triangle point in the pointArray
		MW_FORCEINLINE size_t GetSecondNeighborIndex() const
		{
			return m_szTriangleNeighbor[SECOND_NEIGHBOR];
		}

		/// @return the index of the third triangle point in the pointArray
		MW_FORCEINLINE size_t GetThirdNeighborIndex() const
		{
			return m_szTriangleNeighbor[THIRD_NEIGHBOR];
		}

		enum dataComponents
		{
			FIRST_NEIGHBOR = 0,
			SECOND_NEIGHBOR,
			THIRD_NEIGHBOR
		};

		/// mwTTriangleNeighbors default constructor
		///
		/// The mwTTriangleNeighbors default constructor is needed for the std::vector resize()
		/// method
		mwTTriangleNeighbors()
		{
			m_szTriangleNeighbor[FIRST_NEIGHBOR] = m_szTriangleNeighbor[SECOND_NEIGHBOR] =
				m_szTriangleNeighbor[THIRD_NEIGHBOR] = NO_NEIGHBOR;
		}

		/// mwTTriangleNeighbors constructor
		///
		/// @param szFirstIndex of type size_t - the index of the first triangle point in the pointArray
		/// @param szSecondIndex of type size_t - the index of the second triangle point in the pointArray
		/// @param szThirdIndex of type size_t - the index of the third triangle point in the pointArray
		mwTTriangleNeighbors(size_t szFirstIndex, size_t szSecondIndex, size_t szThirdIndex)
		{
			m_szTriangleNeighbor[FIRST_NEIGHBOR] = szFirstIndex;
			m_szTriangleNeighbor[SECOND_NEIGHBOR] = szSecondIndex;
			m_szTriangleNeighbor[THIRD_NEIGHBOR] = szThirdIndex;
		}

		~mwTTriangleNeighbors() {}

		mwTTriangleNeighbors(const mwTTriangleNeighbors<T>& toCopy)
		{
			m_szTriangleNeighbor[FIRST_NEIGHBOR] = (unsigned)toCopy.GetFirstNeighborIndex();
			m_szTriangleNeighbor[SECOND_NEIGHBOR] = (unsigned)toCopy.GetSecondNeighborIndex();
			m_szTriangleNeighbor[THIRD_NEIGHBOR] = (unsigned)toCopy.GetThirdNeighborIndex();
		}

		unsigned m_szTriangleNeighbor[3];
	};

	typedef mwTTriangleNeighbors<T> TriNeighbors;
	typedef std::vector<TriNeighbors> TriNeighborsArray;
	TriNeighborsArray mTriNeighbor;

private:
	static const unsigned NO_NEIGHBOR;


	void InitializeDefaults()
	{
		m_flipTriangles = 0;
		m_dAngleLimit = 15.0;
		mlastKnownUnvisited = 0;
	}

public:
	/// Default constructor
	mwTMeshVNorm(const Units& unit): mwTMesh<T>(unit) { InitializeDefaults(); }

	/// Constructor with the Smoothing limit and mesh measurement unit
	mwTMeshVNorm(double dAngleLimit, const Units& unit): mwTMesh<T>(unit)
	{
		InitializeDefaults();
		m_dAngleLimit = dAngleLimit;
	}

	/// Copy constructor
	mwTMeshVNorm(const mwTMeshVNorm<T>& toCopy): mwTMesh<T>(toCopy.GetUnits())
	{
		InitializeDefaults();
		*this = toCopy;
	}

	/// Constructor using an old Mesh
	mwTMeshVNorm(const MeshPtr& toCopy): mwTMesh<T>(toCopy->GetUnits())
	{
		InitializeDefaults();
		ConstructMeshCopy(*toCopy);
	}

	/// Constructor using an old Mesh and the Smoothing limit
	mwTMeshVNorm(const MeshPtr& toCopy, double dAngleLimit): mwTMesh<T>(toCopy->GetUnits())
	{
		InitializeDefaults();
		ConstructMeshCopy(*toCopy, dAngleLimit);
	}

	/// Constructor using an old Mesh, the Smoothing limit and a flag for adjusting the mesh
	/// orientation
	mwTMeshVNorm(const MeshPtr& toCopy, double dAngleLimit, bool adjustMoreOrientations)
		: mwTMesh<T>(toCopy->GetUnits())
	{
		InitializeDefaults();
		ConstructMeshCopy(*toCopy, dAngleLimit, adjustMoreOrientations);
	}

	/// Constructor using an old Mesh
	mwTMeshVNorm(const mwTMesh<T>& toCopy): mwTMesh<T>(toCopy.GetUnits())
	{
		InitializeDefaults();
		ConstructMeshCopy(toCopy);
	}

	/// Constructor using an old Mesh and the Smoothing limit
	mwTMeshVNorm(const mwTMesh<T>& toCopy, double dAngleLimit): mwTMesh<T>(toCopy.GetUnits())
	{
		InitializeDefaults();
		ConstructMeshCopy(toCopy, dAngleLimit);
	}

	/// Constructor using an old Mesh, the Smoothing limit and a flag for adjusting the mesh
	/// orientation
	mwTMeshVNorm(const mwTMesh<T>& toCopy, double dAngleLimit, bool adjustMoreOrientations)
		: mwTMesh<T>(toCopy.GetUnits())
	{
		InitializeDefaults();
		ConstructMeshCopy(toCopy, dAngleLimit, adjustMoreOrientations);
	}

	/// Destructor
	~mwTMeshVNorm() {}

	/// Set triangles from the given mesh to current mesh
	/// @param toSet mesh to add the triangles from
	void SetMesh(const mwTMeshVNorm<T>& toSet)
	{
		ResetMesh();
		SetUnits(toSet.GetUnits());

		m_dAngleLimit = toSet.GetAngleLimit();
		*this->mPoints = pointArray(toSet.GetPoints());
		*this->mNormals = normalArray(toSet.GetNormals());
		*this->mTriangles = TriangleArray(toSet.GetTriangles());
	}

	/// Add triangles from the given mesh to current mesh
	/// @param toAdd mesh to add the mTriangles from
	void AddMesh(const mwTMeshVNorm<T>& toAdd)
	{
		if (this->GetUnits() != toAdd.GetUnits())
		{
			throw misc::mwException(
				3513,
				misc::mwstring(_T("Operation failed because meshes have different units type")));
		}

		TriangleVector triVect;

		size_t i = 0;
		size_t szTriVectSize = this->GetNumberOfTriangles();
		for (i = 0; i < szTriVectSize; i++)
		{
			const point3d& p1 = this->GetTriangleFirstVertexPosition(i);
			const point3d& p2 = this->GetTriangleSecondVertexPosition(i);
			const point3d& p3 = this->GetTriangleThirdVertexPosition(i);
			triVect.AddTriangle(p1, p2, p3);
		}

		szTriVectSize = toAdd.GetNumberOfTriangles();
		for (i = 0; i < szTriVectSize; i++)
		{
			const point3d& p1 = toAdd.GetTriangleFirstVertexData(i);
			const point3d& p2 = toAdd.GetTriangleSecondVertexPosition(i);
			const point3d& p3 = toAdd.GetTriangleThirdVertexPosition(i);
			triVect.AddTriangle(p1, p2, p3);
		}
		SetTriangles(triVect);
	}

	/// Set triangles from the given array of triangles to current mesh
	/// 
	/// This method initializes the Mesh with a set of triangles.
	/// The set of triangles is created using the cadcam::mwTTriangleVector class.
	/// @param triVectToSet of type const TriangleVector - triangles to set
	void SetTriangles(const TriangleVector& triVectToSet)
	{
		if (triVectToSet.GetNumberOfPoints() <= 0)
			return;

		mPointsTInd.clear();
		mPointsTInd.reserve(triVectToSet.GetNumberOfPoints() + 2);

		constPointIt it = triVectToSet.GetPointsBegin();
		constPointIt ite = triVectToSet.GetPointsEnd();
		size_t i = 0;
		for (; it != ite; ++it, ++i)
		{
			mPointsTInd.push_back(point3dTInd(*(it), (size_t)(i / 3), static_cast<int>(i % 3)));
		}

		ResetMesh();
		this->mTriangles->assign(triVectToSet.mTriangles->begin(), triVectToSet.mTriangles->end());
		BuildMesh();
	}

	/// GetTriangleFirstVertexNormal method
	///
	/// Get the first vertex normal of a triangle
	/// @param szTriangle of type size_t - index of the triangle in the triangleArray
	/// @return ptRet of type const point3d
	MW_FORCEINLINE point3d GetTriangleFirstVertexNormal(size_t szTriangle) const
	{
		return GetTriangleVertexNormal(szTriangle, 0);
	}

	/// GetTriangleSecondVertexNormal method
	///
	/// Get the second vertex normal of a triangle
	/// @param szTriangle of type size_t - index of the triangle in the triangleArray
	/// @return ptRet of type const point3d
	MW_FORCEINLINE point3d GetTriangleSecondVertexNormal(size_t szTriangle) const
	{
		return GetTriangleVertexNormal(szTriangle, 1);
	}

	/// GetTriangleThirdVertexNormal method
	///
	/// Get the third vertex normal of a triangle
	/// @param szTriangle of type size_t - index of the triangle in the triangleArray
	/// @return ptRet of type const point3d
	MW_FORCEINLINE point3d GetTriangleThirdVertexNormal(size_t szTriangle) const
	{
		return GetTriangleVertexNormal(szTriangle, 2);
	}

	/// GetAngleLimit method
	///
	/// Get the smoothing limit
	/// @return the smoothing limit
	MW_FORCEINLINE double GetAngleLimit() const { return m_dAngleLimit; }

	/// GetNormalsBegin method
	///
	/// @return the pointer to the first element in the mNormals array
	MW_FORCEINLINE constPointIt GetNormalsBegin() const
	{
		return mwContainerMesh<T>::GetVertexNormalsBegin();
	}

	/// GetNormalsEnd method
	///
	/// @return the pointer to the first element in the mNormals array
	MW_FORCEINLINE constPointIt GetNormalsEnd() const
	{
		return mwContainerMesh<T>::GetVertexNormalsEnd();
	}

	/// GetNumberOfNormals method
	///
	/// Get number of normals in the mesh
	/// @return the number of normals in the mesh
	MW_FORCEINLINE size_t GetNumberOfNormals() const
	{
		return mwContainerMesh<T>::GetNumberOfVertexNormals();
	}

	/// Clear mTriangles.
	///
	/// Clear the arrays of mTriangles, mPoints and mNormals.
	void ResetMesh() { mwContainerMesh<T>::ResetMesh(); }

	/// BuildMeshOrient method
	///
	/// Orient built mesh
	void BuildMeshOrient()
	{
		TriNeighborsArray aTriNeighbors;
		MakeNeighborhood(aTriNeighbors);
		mTriNeighbor = aTriNeighbors;
		AdjustMoreOrientations(aTriNeighbors);
		AdjustPoints();
		CalculateNormals();
		// clear

#pragma warning(push)
#pragma warning(disable : 4239)

		pointTIndArray emptyList;
		mPointsTInd.swap(emptyList);

#pragma warning(pop)
	}

	/// operator=
	///
	/// @param tc of type const mwTMeshVNorm<T> &
	/// @returns operator= of type const mwTMeshVNorm<T> &
	const mwTMeshVNorm<T>& operator=(const mwTMeshVNorm<T>& tc)
	{
		SetMesh(tc);
		return *this;
	}

	/// GetNormals method
	///
	/// Get the per-vertex normals of this mesh
	/// @return the mNormals array
	inline const pointArray& GetNormals() const { return mwContainerMesh<T>::GetVertexNormals(); }

	/// GetNormals method
	///
	/// Get the per-vertex normals of this mesh
	/// @return the mNormals array
	void SetFlipTriangles(const bool flipTriangles) { m_flipTriangles = flipTriangles; }

protected:
private:
	class EdgeList
	{
	public:
		EdgeList(){};

		EdgeList(const EdgeList& e) { m_vEntrys = e.m_vEntrys; }

		EdgeList& operator=(const EdgeList& e)
		{
			m_vEntrys = e.m_vEntrys;
			return *this;
		}

		void AddEdgePoint(size_t EdgePointIndex) { m_vEntrys.push_back((unsigned)EdgePointIndex); };
		MW_FORCEINLINE bool Find(size_t key) const
		{
			for (size_t i = 0; i < Size(); ++i)
			{
				if (m_vEntrys[i] == key)
					return true;
			};
			return false;
		}

		MW_FORCEINLINE size_t Size() const { return m_vEntrys.size(); }

		MW_FORCEINLINE size_t operator[](size_t index)
		{
			assert((index >= 0) && (index < Size()));
			return m_vEntrys[index];
		}

	protected:
		std::vector<unsigned> m_vEntrys;
	};

	EdgeList m_EdgeList;

	pointTIndArray mPointsTInd;
	double m_dAngleLimit;
	std::vector<unsigned> vNeighbors;
	bool m_flipTriangles;
	size_t mlastKnownUnvisited;

	/// ConstructMeshCopy method
	///
	/// Construct the copy of specific mesh
	void ConstructMeshCopy(
		const mwTMesh<T>& toCopy, double dAngleLimit = 15.0, bool adjustMoreOrientations = false)
	{
		ResetMesh();
		this->SetUnits(toCopy.GetUnits());

		m_dAngleLimit = dAngleLimit;

		this->mTriangles->assign(toCopy.GetTriangles().begin(), toCopy.GetTriangles().end());
		ConstructPointTInd(toCopy);
		RemoveDuplicateTriangles(toCopy);
		ConstructPointTInd(toCopy);
		if (adjustMoreOrientations)
		{
			BuildMeshOrient();
		}
		else
		{
			BuildMesh();
		}
	}

	/// ConstructPointTInd method
	void ConstructPointTInd(const mwTMesh<T>& toCopy)
	{
		if (this->GetUnits() != toCopy.GetUnits())
		{
			throw misc::mwException(
				3513,
				misc::mwstring(_T("Operation failed because meshes have different units type")));
		}

		std::vector<unsigned> map;
		map.assign(toCopy.GetNumberOfPoints(), 0);

		// Calculates degree of vertexes
		size_t szTriSize = this->mTriangles->size(), i;
		for (i = 0; i < szTriSize; ++i)
		{
			const Triangle& triangle = (*this->mTriangles)[i];
			++map[triangle.GetFirstPointIndex()];
			++map[triangle.GetSecondPointIndex()];
			++map[triangle.GetThirdPointIndex()];
		}

		// Calculates indexes of point3dTInd
		size_t n = 0;
		for (std::vector<unsigned>::iterator mi = map.begin(); mi != map.end(); ++mi)
		{
			size_t size = *mi;
			*mi = (unsigned)n;
			n += size;
		}

		// Fill up the mPointsTInd and change indexes
		mPointsTInd.clear();
		mPointsTInd.resize(szTriSize * 3);

		// ASSERT(n == mPointsTInd.size());

		for (i = 0; i < szTriSize; ++i)
		{
			Triangle& triangle = (*this->mTriangles)[i];
			unsigned p1 = (unsigned)triangle.GetFirstPointIndex();
			unsigned p2 = (unsigned)triangle.GetSecondPointIndex();
			unsigned p3 = (unsigned)triangle.GetThirdPointIndex();

			unsigned& i1 = map[p1];
			unsigned& i2 = map[p2];
			unsigned& i3 = map[p3];
			mPointsTInd[i1] = point3dTInd(toCopy.GetPoints()[p1], i, 0);
			mPointsTInd[i2] = point3dTInd(toCopy.GetPoints()[p2], i, 1);
			mPointsTInd[i3] = point3dTInd(toCopy.GetPoints()[p3], i, 2);
			triangle.SetFirstPointIndex(i1);
			triangle.SetSecondPointIndex(i2);
			triangle.SetThirdPointIndex(i3);
			++i1;
			++i2;
			++i3;
		}
	}

	/// BuildMesh method
	///
	/// Mesh building

	void BuildMesh()
	{
		MakeNeighborhood(mTriNeighbor);
		AdjustOrientations(mTriNeighbor);
		AdjustPoints();
		CalculateNormals();
		// clear

#pragma warning(push)
#pragma warning(disable : 4239)

		pointTIndArray emptyList;
		mPointsTInd.swap(emptyList);

#pragma warning(pop)
	}


	/// MakeNeighborhood method
	///
	/// Creates the neighborhood info
	/// @param aTriNeighbors - array of neighbors info
	void MakeNeighborhood(TriNeighborsArray& aTriNeighbors)
	{
		size_t i = 0;
		size_t szTriSize = this->mTriangles->size();
		aTriNeighbors.clear();
		aTriNeighbors.reserve(szTriSize + 2);

		for (i = 0; i < szTriSize; ++i)
		{
			const Triangle& triangle = (*this->mTriangles)[i];
			size_t szPt1Ind = triangle.GetFirstPointIndex();
			size_t szPt2Ind = triangle.GetSecondPointIndex();
			size_t szPt3Ind = triangle.GetThirdPointIndex();

			const point3d& ptP1 = mPointsTInd[szPt1Ind].GetPoint();
			const point3d& ptP2 = mPointsTInd[szPt2Ind].GetPoint();
			const point3d& ptP3 = mPointsTInd[szPt3Ind].GetPoint();

			TriNeighbors triNeighbors;
			if (!PointsCloseEnough(ptP1, ptP2))
			{
				size_t neighbor = FindNeighbor(i, szPt1Ind, szPt2Ind);
				if (neighbor == NO_NEIGHBOR)
				{
					// switch the points and try again
					neighbor = FindNeighbor(i, szPt2Ind, szPt1Ind);
				}
				triNeighbors.SetFirstNeighborIndex(neighbor);
			}
			else
				triNeighbors.SetFirstNeighborIndex(NO_NEIGHBOR);

			if (!PointsCloseEnough(ptP2, ptP3))
			{
				size_t neighbor = FindNeighbor(i, szPt2Ind, szPt3Ind);
				if (neighbor == NO_NEIGHBOR)
				{
					// switch the points and try again
					neighbor = FindNeighbor(i, szPt3Ind, szPt2Ind);
				}
				triNeighbors.SetSecondNeighborIndex(neighbor);
			}
			else
				triNeighbors.SetSecondNeighborIndex(NO_NEIGHBOR);

			if (!PointsCloseEnough(ptP3, ptP1))
			{
				size_t neighbor = FindNeighbor(i, szPt3Ind, szPt1Ind);
				if (neighbor == NO_NEIGHBOR)
				{
					// switch the points and try again
					neighbor = FindNeighbor(i, szPt1Ind, szPt3Ind);
				}
				triNeighbors.SetThirdNeighborIndex(neighbor);
			}
			else
				triNeighbors.SetThirdNeighborIndex(NO_NEIGHBOR);

			aTriNeighbors.push_back(triNeighbors);
		}
	}

	/// RemoveDuplicateTriangles method
	///
	/// this method filters degenerated triangles also
	/// @param toCopy - all of the triangles from this excepting the duplicates will be taken by the
	/// mTriangles member
	void RemoveDuplicateTriangles(const mwTMesh<T>& toCopy)
	{
		size_t i = 0;
		size_t szTriSize = this->mTriangles->size();

		std::vector<size_t> duplicateTrianglesMap;
		duplicateTrianglesMap.assign(szTriSize, 0);

		for (i = 0; i < szTriSize; i++)
		{
			const Triangle& triangle = (*this->mTriangles)[i];

			if (duplicateTrianglesMap[i] != 0)
				continue;

			unsigned szPt1Ind = (unsigned)triangle.GetFirstPointIndex();
			unsigned szPt2Ind = (unsigned)triangle.GetSecondPointIndex();
			unsigned szPt3Ind = (unsigned)triangle.GetThirdPointIndex();

			point3d ptP1 = mPointsTInd[szPt1Ind].GetPoint();
			point3d ptP2 = mPointsTInd[szPt2Ind].GetPoint();
			point3d ptP3 = mPointsTInd[szPt3Ind].GetPoint();

			bool bLegalEdge12 = true;
			bool bLegalEdge23 = true;
			bool bLegalEdge31 = true;

			if (PointsCloseEnough(ptP1, ptP2))
				bLegalEdge12 = false;
			if (PointsCloseEnough(ptP2, ptP3))
				bLegalEdge23 = false;
			if (PointsCloseEnough(ptP3, ptP1))
				bLegalEdge31 = false;

			if (bLegalEdge12)
			{
				FindDuplicates(i, szPt1Ind, szPt2Ind, duplicateTrianglesMap);
			}
			else if (bLegalEdge23)
			{
				FindDuplicates(i, szPt2Ind, szPt3Ind, duplicateTrianglesMap);
			}
			else if (bLegalEdge31)
			{
				FindDuplicates(i, szPt3Ind, szPt1Ind, duplicateTrianglesMap);
			}

			if (duplicateTrianglesMap[i] != 0)
				continue;

			if (!bLegalEdge12 || !bLegalEdge23 || !bLegalEdge31)
			{  // degenerated triangle remove it also.
				duplicateTrianglesMap[i] = 1;
			}
		}

		misc::mwAutoPointer<TriangleArray> newTriangles = new TriangleArray();
		newTriangles->reserve(szTriSize);

		for (i = 0; i < szTriSize; ++i)
		{
			if (duplicateTrianglesMap[i] == 0)
			{
				newTriangles->push_back(toCopy.GetTriangles()[i]);
			}
		}
		(this->mTriangles)->assign(newTriangles->begin(), newTriangles->end());
	}

	/// FindNeighbor method
	///
	/// Finds a neighboring triangle which contains the two given points
	/// @param szTriInd - triangle index
	/// @param ptAInd - first point index
	/// @param ptBInd - second point index
	/// @return triangle_index
	MW_FORCEINLINE size_t FindNeighbor(size_t szTriInd, size_t ptAInd, size_t ptBInd)
	{
		size_t i = 0;
		size_t szPtSize = mPointsTInd.size();
		if (ptAInd < szPtSize && ptBInd < szPtSize)
		{
			size_t ptStart = ptAInd;
			size_t ptStop = ptAInd;
			const point3d& ptA = mPointsTInd[ptAInd].GetPoint();

			size_t tmp = 0;
			if (ptStart != 0)
			{
				tmp = ptStart - 1;
				const point3d* ptATest = &mPointsTInd[tmp].GetPoint();
				while (ptA == *ptATest)
				{
					ptStart = tmp;
					if (ptStart != 0)
					{
						tmp--;
						ptATest = &mPointsTInd[tmp].GetPoint();
					}
					else
						break;
				}
			}

			tmp = ptStop + 1;
			if (tmp < szPtSize)
			{
				const point3d* ptATest = &mPointsTInd[tmp].GetPoint();
				while (ptA == *ptATest)
				{
					ptStop = tmp;
					tmp++;
					if (tmp < szPtSize)
						ptATest = &mPointsTInd[tmp].GetPoint();
					else
						break;
				}
			}
			ptStop++;

			const point3d& ptB = mPointsTInd[ptBInd].GetPoint();
			for (i = ptStart; i < ptStop; ++i)
			{
				if (i != ptAInd)
				{
					const point3dTInd& ptTInd = mPointsTInd[i];
					size_t szTriIndex = ptTInd.GetTriangleIndex();
					if (szTriIndex != szTriInd)
					{
						const Triangle& triangle = (*this->mTriangles)[szTriIndex];
						if (ContainsPoint(triangle, ptB))
						{
							return szTriIndex;
						}
					}
				}
			}
		}
		return NO_NEIGHBOR;
	}

	bool CompareTrianglePoints(
		point3d FirstPoint,
		point3d SecondPoint,
		point3d ThirdPoint,
		point3d FirstOrigPoint,
		point3d SecondOrigPoint,
		point3d ThirdOrigPoint)
	{
		return (
			(FirstPoint == FirstOrigPoint) && (SecondPoint == SecondOrigPoint) &&
			(ThirdPoint == ThirdOrigPoint));
	}
	/// FindDuplicates method
	///
	/// Finds any duplicate triangle which contains the two given points and marks it in the
	/// duplication map
	/// @param szTriInd - triangle index
	/// @param ptAInd - first point index
	/// @param ptBInd - second point index
	/// @param duplicationMap - the duplication map
	MW_FORCEINLINE void FindDuplicates(
		size_t szTriInd, size_t ptAInd, size_t ptBInd, std::vector<size_t>& duplicationMap)
	{
		size_t i = 0;
		size_t szPtSize = mPointsTInd.size();
		if (ptAInd < szPtSize && ptBInd < szPtSize)
		{
			size_t ptStart = ptAInd;
			size_t ptStop = ptAInd;
			point3d ptA = mPointsTInd[ptAInd].GetPoint();

			size_t tmp = 0;
			if (ptStart != 0)
			{
				tmp = ptStart - 1;
				point3d ptATest = mPointsTInd[tmp].GetPoint();
				while (ptA == ptATest)
				{
					ptStart = tmp;
					if (ptStart != 0)
					{
						tmp--;
						ptATest = mPointsTInd[tmp].GetPoint();
					}
					else
						break;
				}
			}

			tmp = ptStop + 1;
			if (tmp < szPtSize)
			{
				point3d ptATest = mPointsTInd[tmp].GetPoint();
				while (ptA == ptATest)
				{
					ptStop = tmp;
					tmp++;
					if (tmp < szPtSize)
						ptATest = mPointsTInd[tmp].GetPoint();
					else
						break;
				}
			}
			ptStop++;

			point3d ptB = mPointsTInd[ptBInd].GetPoint();
			for (i = ptStop - 1; i > ptStart; --i)
			{
				if (i != ptAInd)  // wenn es ein anderer Punkt ist
				{
					point3dTInd ptTInd = mPointsTInd[i];
					size_t szTriIndex = ptTInd.GetTriangleIndex();
					if (szTriIndex != szTriInd)  // wenn es ein anderes Dreieck ist
					{
						Triangle triangle = (*this->mTriangles)[szTriIndex];
						if (ContainsPoint(triangle, ptB))  //
						{
							size_t szPt1Ind = triangle.GetFirstPointIndex();
							size_t szPt2Ind = triangle.GetSecondPointIndex();
							size_t szPt3Ind = triangle.GetThirdPointIndex();

							point3d ptP1 = mPointsTInd[szPt1Ind].GetPoint();
							point3d ptP2 = mPointsTInd[szPt2Ind].GetPoint();
							point3d ptP3 = mPointsTInd[szPt3Ind].GetPoint();

							Triangle origtriangle = (*this->mTriangles)[szTriInd];

							size_t origszPt1Ind = origtriangle.GetFirstPointIndex();
							size_t origszPt2Ind = origtriangle.GetSecondPointIndex();
							size_t origszPt3Ind = origtriangle.GetThirdPointIndex();

							point3d origptP1 = mPointsTInd[origszPt1Ind].GetPoint();
							point3d origptP2 = mPointsTInd[origszPt2Ind].GetPoint();
							point3d origptP3 = mPointsTInd[origszPt3Ind].GetPoint();

							if (CompareTrianglePoints(
									ptP1, ptP2, ptP3, origptP1, origptP2, origptP3))
							{
								duplicationMap[szTriIndex] = 1;
							}
							if (CompareTrianglePoints(
									ptP1, ptP2, ptP3, origptP2, origptP3, origptP1))
							{
								duplicationMap[szTriIndex] = 1;
							}
							if (CompareTrianglePoints(
									ptP1, ptP2, ptP3, origptP3, origptP1, origptP2))
							{
								duplicationMap[szTriIndex] = 1;
							}
							if (CompareTrianglePoints(
									ptP1, ptP2, ptP3, origptP3, origptP2, origptP1))
							{
								duplicationMap[szTriIndex] = 1;
							}
							if (CompareTrianglePoints(
									ptP1, ptP2, ptP3, origptP1, origptP3, origptP2))
							{
								duplicationMap[szTriIndex] = 1;
							}
							if (CompareTrianglePoints(
									ptP1, ptP2, ptP3, origptP2, origptP1, origptP3))
							{
								duplicationMap[szTriIndex] = 1;
							}
						}
					}
				}
			}
		}
	}

	/// AdjustOrientations method
	///
	/// Adjusts triangle orientations
	/// @param aTriNeighbors - array of neighbors info
	void AdjustOrientations(const TriNeighborsArray& aTriNeighbors)
	{
		// size_t i = 0;
		std::vector<int> visited;  // 0:	Not visited
		this->mlastKnownUnvisited = 0;
		size_t szTriSize = this->mTriangles->size();
		// 1:	Orientation and Normal Adjusted
		// 2:	Visited (means that all neighbors are Adjusted)
		visited.assign(szTriSize, 0);  // 0:	ALL initialy Not visited

		size_t szNextTriangle = 0;
		vNeighbors.clear();

		size_t szUnvisitedTriangle = ExistUnvisitedTriangle(visited);
		while (szUnvisitedTriangle >= 0 && szUnvisitedTriangle < szTriSize)
		{
			vNeighbors.push_back((unsigned)szUnvisitedTriangle);
			while (vNeighbors.size() > 0)
			{
				szNextTriangle = vNeighbors[vNeighbors.size() - 1];
				vNeighbors.pop_back();
				VisitTriangle(szNextTriangle, aTriNeighbors, visited);
			}
			szUnvisitedTriangle = ExistUnvisitedTriangle(visited);
		}

#pragma warning(push)
#pragma warning(disable : 4239)

		std::vector<unsigned> emptyList;
		vNeighbors.swap(emptyList);

#pragma warning(pop)
	}

	/// AdjustMoreOrientations method
	///
	/// Adjusts more the triangle orientations
	/// @param aTriNeighbors - array of neighbors info
	void AdjustMoreOrientations(TriNeighborsArray& aTriNeighbors)
	{
		// size_t i = 0;
		this->mlastKnownUnvisited = 0;
		std::vector<int> visited;  // 0:	Not visited
		size_t szTriSize = this->mTriangles->size();
		// 1:	Orientation and Normal Adjusted
		// 2:	Visited (means that all neighbors are Adjusted)
		visited.assign(szTriSize, 0);  // 0:	ALL initialy Not visited

		size_t szNextTriangle = 0;
		vNeighbors.clear();
		int conexcomponentID = 2;

		size_t szUnvisitedTriangle = ExistUnvisitedTriangle(visited);
		while (szUnvisitedTriangle >= 0 && szUnvisitedTriangle < szTriSize)
		{
			vNeighbors.push_back((unsigned)szUnvisitedTriangle);
			while (vNeighbors.size() > 0)
			{
				szNextTriangle = vNeighbors[vNeighbors.size() - 1];
				vNeighbors.pop_back();
				VisitMoreTriangle(szNextTriangle, aTriNeighbors, visited);
			}
			/// check the new conex component
			conexcomponentID++;
			size_t conexcomponenttri;
			ChangeConexComponentID(visited, 2, conexcomponentID, conexcomponenttri);
			/// if it is a close mesh, check orientation, and switch all orientations if needed
			if (ConexComponentIsClosed(visited, conexcomponentID))
			{
				if (!IsOrientationSetToOutside(conexcomponenttri, visited, conexcomponentID))
				{
					for (size_t szTriIndex = 0; szTriIndex < szTriSize; ++szTriIndex)
					{
						if (visited[szTriIndex] == conexcomponentID)
						{
							SwitchOrientation(szTriIndex);
							SetPositiveOrientation(szTriIndex);
						}
					}
				}
			}
			//
			szUnvisitedTriangle = ExistUnvisitedTriangle(visited);
		}

#pragma warning(push)
#pragma warning(disable : 4239)

		std::vector<unsigned> emptyList;
		vNeighbors.swap(emptyList);

#pragma warning(pop)
	}

	/// ConexComponentIsClosed method
	///
	/// Change the conex component ID from originalID to newID
	/// @param visited - list of visited triangles
	/// @param conexcomponentID - ID for the conex component members
	/// @return true if the conex component is closed, false if it the conex component is open
	bool ConexComponentIsClosed(std::vector<int>& visited, int conexcomponentID)
	{
		size_t i = 0;
		int nPoints = 0;
		int nTri = 0;

		// count points
		size_t szPtSize = mPointsTInd.size();
		point3d ptPrev;
		point3d ptCurr;
		bool prevPtcounted = false;
		for (i = 0; i < szPtSize; ++i)
		{
			ptCurr = mPointsTInd[i].GetPoint();
			if (prevPtcounted)
			{
				if (ptCurr == ptPrev)
					continue;
				else
					prevPtcounted = false;
			}
			point3dTInd ptTInd = mPointsTInd[i];
			size_t szTriIndex = ptTInd.GetTriangleIndex();
			if (visited[szTriIndex] == conexcomponentID)
			{
				nPoints++;
				prevPtcounted = true;
			}
			ptPrev = ptCurr;
		}

		// count triangles
		size_t szTriSize = visited.size();
		for (i = 0; i < szTriSize; ++i)
		{
			if (visited[i] == conexcomponentID)
			{
				nTri++;
			}
		}

		// check if the conex component is closed
		if ((nTri >= 4) && (2 * nPoints == (nTri + 4)))
			return true;
		else
			return false;
	}

	/// ChangeConexComponentID method
	///
	/// Change the conex component ID from originalID to newID
	/// @param visited - list of visited triangles
	/// @param originalID - original ID for the conex component members (usually =2)
	/// @param newID - new ID  for the conex component members
	/// @param conexcomponenttri - returns a triangle ID that is part of the conex component
	void ChangeConexComponentID(
		std::vector<int>& visited, int originalID, int newID, size_t& conexcomponenttri)
	{
		size_t szTriSize = visited.size();
		for (size_t i = 0; i < szTriSize; ++i)
		{
			if (visited[i] == originalID)
			{
				visited[i] = newID;
				conexcomponenttri = i;
			}
		}
		return;
	}

	/// ExistUnvisitedTriangle method
	///
	/// Checks if there are any unvisited triangles
	/// @param visited - list of visited triangles
	/// @return triangle_index
	size_t ExistUnvisitedTriangle(std::vector<int>& visited)
	{
		size_t szTriSize = visited.size();
		size_t i = mlastKnownUnvisited;
		for (; i < szTriSize; ++i)
		{
			if (visited[i] < 1)
			{
				mlastKnownUnvisited = i;
				return i;
			}
		}
		mlastKnownUnvisited = szTriSize;
		return NO_NEIGHBOR;
	}

	/// VisitTriangle method
	///
	/// Visits a triangle -> Adjusts the orientation of its neighbors
	/// @param szTriIndex - reference triangle
	/// @param aTriNeighbors - array of neighbors info
	/// @param visited - list of visited triangles
	MW_FORCEINLINE void VisitTriangle(
		size_t szTriIndex, const TriNeighborsArray& aTriNeighbors, std::vector<int>& visited)
	{
		if (visited[szTriIndex] < 1)  // Not adjusted -> New unconnected component!
		{
			SetPositiveOrientation(szTriIndex);
			visited[szTriIndex] = 1;  //  1:	Orientation and Normal Adjusted
		}
		if (visited[szTriIndex] < 2)  // No need to reVisit.
		{
			const TriNeighbors& triNeighbors = aTriNeighbors[szTriIndex];
			size_t szNeighbor1 = triNeighbors.GetFirstNeighborIndex();
			size_t szNeighbor2 = triNeighbors.GetSecondNeighborIndex();
			size_t szNeighbor3 = triNeighbors.GetThirdNeighborIndex();

			AdjustTriangle(szTriIndex, szNeighbor1, visited);
			AdjustTriangle(szTriIndex, szNeighbor2, visited);
			AdjustTriangle(szTriIndex, szNeighbor3, visited);
			visited[szTriIndex] = 2;  //  2:	Visited (means that all neighbors are Adjusted)
		}
	}

	/// VisitMoreTriangle method
	///
	/// Visits a triangle -> Adjusts the orientation of its neighbors
	/// @param szTriIndex - reference triangle
	/// @param aTriNeighbors - array of neighbors info
	/// @param visited - list of visited triangles
	MW_FORCEINLINE void VisitMoreTriangle(
		size_t szTriIndex, TriNeighborsArray& aTriNeighbors, std::vector<int>& visited)
	{
		if (visited[szTriIndex] < 1)  // Not adjusted -> New unconnected component!
		{
			// new unconnected component, set the first triangle with the orientation (normal)
			// outside the mesh
			SetPositiveOrientation(szTriIndex);
			if (!IsOrientationSetToOutside(szTriIndex, visited, -1))
			{
				SwitchOrientation(szTriIndex);
				SetPositiveOrientation(szTriIndex);
			}
			visited[szTriIndex] = 1;  //  1:	Orientation and Normal Adjusted
		}
		if (visited[szTriIndex] < 2)  // No need to reVisit.
		{
			TriNeighbors triNeighbors = aTriNeighbors[szTriIndex];
			size_t szNeighbor1 = triNeighbors.GetFirstNeighborIndex();
			size_t szNeighbor2 = triNeighbors.GetSecondNeighborIndex();
			size_t szNeighbor3 = triNeighbors.GetThirdNeighborIndex();

			AdjustTriangle(szTriIndex, szNeighbor1, visited);
			AdjustTriangle(szTriIndex, szNeighbor2, visited);
			AdjustTriangle(szTriIndex, szNeighbor3, visited);
			visited[szTriIndex] = 2;  //  2:	Visited (means that all neighbors are Adjusted)
		}
	}

	/// GetCommonVector method
	///
	/// Determines the common edge of two triangles
	/// @param szTri1 - triangle 1 index
	/// @param szTri2 - triangle 2 index
	point3d GetCommonVector(size_t szTri1, size_t szTri2)
	{
		int j = 0;
		int k = 0;
		Triangle triangle1 = (*this->mTriangles)[szTri1];
		Triangle triangle2 = (*this->mTriangles)[szTri2];

		for (j = 0; j < 3; ++j)
		{
			k = j < 2 ? j + 1 : 0;
			point3d ptJ = mPointsTInd[triangle1.GetPointIndex(j)].GetPoint();
			point3d ptK = mPointsTInd[triangle1.GetPointIndex(k)].GetPoint();
			if (ContainsPoint(triangle2, ptJ) && ContainsPoint(triangle2, ptK))
				return (ptK - ptJ);
		}
		return point3d(0, 0, 0);
	}

	/// AdjustTriangle method
	///
	/// Adjusts the neighbouring triangle to be oriented the same way as the refernce triangle
	/// @param szTriIndex - reference triangle
	/// @param szNeighborIndex - neighboring triangle
	/// @param visited - list of visited triangles
	void AdjustTriangle(size_t szTriIndex, size_t szNeighborIndex, std::vector<int>& visited)
	{
		if (szNeighborIndex >= 0 && szNeighborIndex < this->mTriangles->size())
		{
			if (visited[szNeighborIndex] < 1)  // No need to reAdjust.
			{
				if (m_flipTriangles)
				{
					point3d ptVect1 = GetCommonVector(szTriIndex, szNeighborIndex);
					point3d ptVect2 = GetCommonVector(szNeighborIndex, szTriIndex);

					if (PointsCloseEnough(ptVect1, ptVect2) && ptVect1 != point3d(0, 0, 0))
						SwitchOrientation(szNeighborIndex);

					SetPositiveOrientation(szNeighborIndex);
				}
				visited[szNeighborIndex] = 1;  //  1:	Orientation and Normal Adjusted
				vNeighbors.push_back((unsigned)szNeighborIndex);
			}
		}
	}

	/// SwitchOrientation method
	///
	/// Changes the order of the points in the triangle from ABC to BAC
	/// @param szTriIndex - triangle index
	void SwitchOrientation(size_t szTriIndex)
	{
		// change the points in the triangle list
		size_t szPt1 = (*this->mTriangles)[szTriIndex].GetFirstPointIndex();
		size_t szPt2 = (*this->mTriangles)[szTriIndex].GetSecondPointIndex();
		(*this->mTriangles)[szTriIndex].SetFirstPointIndex(szPt2);
		(*this->mTriangles)[szTriIndex].SetSecondPointIndex(szPt1);
		/// now inform the points list of the changed tris
		mPointsTInd[(*this->mTriangles)[szTriIndex].GetFirstPointIndex()].SetPointIndex(0);
		mPointsTInd[(*this->mTriangles)[szTriIndex].GetSecondPointIndex()].SetPointIndex(1);
		// now inform the neighbors that their position has changed
		TriNeighbors triNeighbor = mTriNeighbor[szTriIndex];
		size_t szNeighborb = triNeighbor.GetSecondNeighborIndex();
		size_t szNeighborc = triNeighbor.GetThirdNeighborIndex();
		mTriNeighbor[szTriIndex].SetSecondNeighborIndex(szNeighborc);
		mTriNeighbor[szTriIndex].SetThirdNeighborIndex(szNeighborb);
	}

	/// SetPositiveOrientation method
	///
	/// Flips the orientation of the triangle normal so that it is oriented positively
	/// @param szTriInd - triangle index
	MW_FORCEINLINE void SetPositiveOrientation(size_t szTriInd)
	{
		Triangle triangle = (*this->mTriangles)[szTriInd];
		point3d normal = triangle.GetNormalVector();
		point3d pt1 = mPointsTInd[triangle.GetFirstPointIndex()].GetPoint();
		point3d pt2 = mPointsTInd[triangle.GetSecondPointIndex()].GetPoint();
		point3d pt3 = mPointsTInd[triangle.GetThirdPointIndex()].GetPoint();
		point3d calcNormal = ((pt3 - pt2) % (pt1 - pt2));
		if ((calcNormal * normal) < 0)
			normal *= -1;
		(*this->mTriangles)[szTriInd].SetNormal(normal);
	}

	/// ContainsPoint method
	///
	/// Determines if the triangle contains the point
	/// @param triangle - the triangle
	/// @param pt - the point
	/// @return true/false
	MW_FORCEINLINE bool ContainsPoint(const Triangle& triangle, const point3d& pt)
	{
		if (PointsCloseEnough(pt, mPointsTInd[triangle.GetFirstPointIndex()].GetPoint()))
			return true;
		if (PointsCloseEnough(pt, mPointsTInd[triangle.GetSecondPointIndex()].GetPoint()))
			return true;
		if (PointsCloseEnough(pt, mPointsTInd[triangle.GetThirdPointIndex()].GetPoint()))
			return true;
		return false;
	}

	/// PointsCloseEnough method
	///
	/// Determines if two 3d points are within some very small treshhold
	/// @param pt1 - first point
	/// @param pt2 - second point
	MW_FORCEINLINE bool PointsCloseEnough(const point3d& pt1, const point3d& pt2)
	{
		point3d fDiff = pt1 - pt2;

		return fDiff * fDiff <= mathdef::MW_MATH_TOL_SQR;
	}

	/// SetOrientationToOutside method
	///
	/// Sets the orientation of the triangle normal so that it is oriented towards the outside of
	/// the mesh
	/// @param szTriInd - triangle index
	/// @param visited - list of visited triangles
	/// @param conexcomponentID: conex component ID of the mesh to check against, if -1 check
	/// against all triangles
	bool IsOrientationSetToOutside(size_t szTriInd, std::vector<int>& visited, int conexcomponentID)
	{
		/// defines for small numbers
		const ValueType EPSILON_E5 = static_cast<ValueType>(0.00001);
		const ValueType EPSILON_OUTSIDE_MIN = static_cast<ValueType>(-0.00001);
		const ValueType EPSILON_OUTSIDE_MAX = static_cast<ValueType>(1.00001);
		const ValueType EPSILON_BORDER_MIN = static_cast<ValueType>(0.00001);
		const ValueType EPSILON_BORDER_MAX = static_cast<ValueType>(0.99999);

		size_t szTriSize = (this->mTriangles)->size();
		point3d cpoint, ray;
		int ray_dir, intersections_count = 0;
		bool bad_intersections;
		bool upside_OZ = false;
		srand((unsigned)time(MW_NULL) + rand());
		ValueType x, y, z;  // random values between [0,1] with r1+r2+r3=1
		ValueType c1, c2, c3, coef,
			coef2;  // coeficients corresponding to the ray position the triangle, need to be
					// between [0,1] c1+c2+c3=1 in order for the ray to intersect the triangle

		if (szTriInd < 0 || szTriInd > (this->mTriangles)->size() - 1)
			return true;

		Triangle triangle = (*this->mTriangles)[szTriInd];
		point3d trinormal = triangle.GetNormalVector();
		point3d pt1 = mPointsTInd[triangle.GetFirstPointIndex()].GetPoint();
		point3d pt2 = mPointsTInd[triangle.GetSecondPointIndex()].GetPoint();
		point3d pt3 = mPointsTInd[triangle.GetThirdPointIndex()].GetPoint();

		// get the ray direction: we shot the ray on one of the OX, OY or OZ directions
		// that is closer to the triangle normal
		/*
		if( std::fabs(trinormal.x()) < std::fabs(trinormal.y()) )
		{
			if( std::fabs(trinormal.y()) < std::fabs(trinormal.z()) )
				ray_dir = 2;
			else
				ray_dir = 1;
		}
		else
		{
			if( std::fabs(trinormal.x()) < std::fabs(trinormal.z()) )
				ray_dir = 2;
			else
				ray_dir = 0;
		}
		*/
		// prefer the OZ direction
		if (std::fabs(trinormal.z()) > EPSILON_E5)
		{
			ray_dir = 2;
			if (trinormal.z() > static_cast<ValueType>(0.0))
			{
				upside_OZ = true;
			}
			else
			{
				upside_OZ = false;
				trinormal.z(-trinormal.z());
			}
		}
		else
		{
			if (std::fabs(trinormal.x()) < std::fabs(trinormal.y()))
				ray_dir = 1;
			else
				ray_dir = 0;
		}
		// use a loop to get a random point inside the triangle to position the ray in, we need to
		// try points till we get a position for a ray that will not have mesh points or mesh edge
		// intersections
		for (size_t step = 0; step < 1000; ++step)
		{
			intersections_count = 0;
			bad_intersections = false;
			if (step == 0)
			{
				// first time we position the ray in the triangle center
				cpoint = static_cast<ValueType>(1. / 3.) * (pt1 + pt2 + pt3);
			}
			else
			{
				// get a random inside point
				ValueType r1 = static_cast<ValueType>(rand()) / static_cast<ValueType>(RAND_MAX);
				ValueType r2 = (static_cast<ValueType>(1.0) - r1) * static_cast<ValueType>(rand()) /
					static_cast<ValueType>(RAND_MAX);
				ValueType r3 = static_cast<ValueType>(1.0) - r1 - r2;
				cpoint = (r1 * pt1 + r2 * pt2 + r3 * pt3);
			}
			for (size_t id_secondtri = 0; id_secondtri < szTriSize; ++id_secondtri)
			{
				if (bad_intersections)
					break;
				if (id_secondtri == szTriInd)
					continue;
				if (conexcomponentID >= 0)
				{
					if (visited[id_secondtri] != conexcomponentID)
						continue;
				}
				Triangle second_tri = (*this->mTriangles)[id_secondtri];
				point3d v1 = mPointsTInd[second_tri.GetFirstPointIndex()].GetPoint();
				point3d v2 = mPointsTInd[second_tri.GetSecondPointIndex()].GetPoint();
				point3d v3 = mPointsTInd[second_tri.GetThirdPointIndex()].GetPoint();

				// check if the ray is inside the triangle's 2D rectangle
				switch (ray_dir)
				{
				case 0:
					// ray is on OX
					if ((cpoint.y() < v1.y() && cpoint.y() < v2.y() && cpoint.y() < v3.y()) ||
						(cpoint.y() > v1.y() && cpoint.y() > v2.y() && cpoint.y() > v3.y()) ||
						(cpoint.z() < v1.z() && cpoint.z() < v2.z() && cpoint.z() < v3.z()) ||
						(cpoint.z() > v1.z() && cpoint.z() > v2.z() && cpoint.z() > v3.z()))
						continue;
					break;
				case 1:
					// ray is on OY
					if ((cpoint.x() < v1.x() && cpoint.x() < v2.x() && cpoint.x() < v3.x()) ||
						(cpoint.x() > v1.x() && cpoint.x() > v2.x() && cpoint.x() > v3.x()) ||
						(cpoint.z() < v1.z() && cpoint.z() < v2.z() && cpoint.z() < v3.z()) ||
						(cpoint.z() > v1.z() && cpoint.z() > v2.z() && cpoint.z() > v3.z()))
						continue;
					break;
				case 2:
					// ray is on OZ
					if ((cpoint.x() < v1.x() && cpoint.x() < v2.x() && cpoint.x() < v3.x()) ||
						(cpoint.x() > v1.x() && cpoint.x() > v2.x() && cpoint.x() > v3.x()) ||
						(cpoint.y() < v1.y() && cpoint.y() < v2.y() && cpoint.y() < v3.y()) ||
						(cpoint.y() > v1.y() && cpoint.y() > v2.y() && cpoint.y() > v3.y()))
						continue;
					break;
				default: break;
				};

				// compute the ray-triangle intersection based on the ray (axis) direction:
				switch (ray_dir)
				{
				case 0:
					// ray is on OX
					if (mathdef::is_eq(v1.y(), v3.y(), EPSILON_E5))
					{
						if (mathdef::is_eq(v2.y(), v3.y(), EPSILON_E5))
						{
							// v1, v2 and v3 colliniar in OY, not a valid triangle
							continue;
						}
						c2 = (cpoint.y() - v3.y()) / (v2.y() - v3.y());
						if (c2 < EPSILON_OUTSIDE_MIN || c2 > EPSILON_OUTSIDE_MAX)
						{
							// intersection outside triangle
							continue;
						}
						if (c2 < EPSILON_BORDER_MIN || c2 > EPSILON_BORDER_MAX)
						{
							// intersection on a vertex/edge of the triangle
							bad_intersections = true;
							continue;
						}
						if (mathdef::is_eq(v1.z(), v3.z(), EPSILON_E5))
						{
							// v1v3 edge is on OY, contradiction with the triangle normal longest
							// component on OY
							continue;
						}
						c1 = (cpoint.z() - v3.z() - c2 * (v2.z() - v3.z())) / (v1.z() - v3.z());
						if (c1 < EPSILON_OUTSIDE_MIN || c1 > EPSILON_OUTSIDE_MAX)
						{
							// intersection outside triangle
							continue;
						}
						if (c1 < EPSILON_BORDER_MIN || c1 > EPSILON_BORDER_MAX)
						{
							// intersection on a vertex/edge of the triangle
							bad_intersections = true;
							continue;
						}
					}
					else
					{
						coef = (v1.z() - v3.z()) / (v1.y() - v3.y());
						coef2 = v2.z() - v3.z() - coef * (v2.y() - v3.y());
						if (mathdef::is_eq(coef2, static_cast<ValueType>(0.0), EPSILON_E5))
						{
							// v1, v2 and v3 colliniar in OYZ, the triangle cannot have a valid
							// intersection with the OY ray
							continue;
						}
						c2 = (cpoint.z() - v3.z() - coef * (cpoint.y() - v3.y())) / coef2;
						if (c2 < EPSILON_OUTSIDE_MIN || c2 > EPSILON_OUTSIDE_MAX)
						{
							// intersection outside triangle
							continue;
						}
						if (c2 < EPSILON_BORDER_MIN || c2 > EPSILON_BORDER_MAX)
						{
							// intersection on a vertex/edge of the triangle
							bad_intersections = true;
							continue;
						}
						c1 = (cpoint.y() - v3.y() - c2 * (v2.y() - v3.y())) / (v1.y() - v3.y());
						if (c1 < EPSILON_OUTSIDE_MIN || c1 > EPSILON_OUTSIDE_MAX)
						{
							// intersection outside triangle
							continue;
						}
						if (c1 < EPSILON_BORDER_MIN || c1 > EPSILON_BORDER_MAX)
						{
							// intersection on a vertex/edge of the triangle
							bad_intersections = true;
							continue;
						}
					}
					c3 = static_cast<ValueType>(1.0) - c1 - c2;
					if (c3 < EPSILON_OUTSIDE_MIN || c3 > EPSILON_OUTSIDE_MAX)
					{
						// intersection outside triangle
						continue;
					}
					if (c3 < EPSILON_BORDER_MIN || c3 > EPSILON_BORDER_MAX)
					{
						// intersection on a vertex/edge of the triangle
						bad_intersections = true;
						continue;
					}
					x = c1 * v1.x() + c2 * v2.x() + c3 * v3.x();
					if (((trinormal.x() > static_cast<ValueType>(0.0)) &&
						 ((x - cpoint.x()) < static_cast<ValueType>(0.0))) ||
						((trinormal.x() < static_cast<ValueType>(0.0)) &&
						 ((x - cpoint.x()) > static_cast<ValueType>(0.0))))
					{
						// intersection on the other side (on the normal negative side), do not
						// count it
						continue;
					}
					// intersection on the normal positive side, count it
					++intersections_count;
					break;
				case 1:
					// ray is on OY
					if (mathdef::is_eq(v1.x(), v3.x(), EPSILON_E5))
					{
						if (mathdef::is_eq(v2.x(), v3.x(), EPSILON_E5))
						{
							// v1, v2 and v3 colliniar in OX, not a valid triangle
							continue;
						}
						c2 = (cpoint.x() - v3.x()) / (v2.x() - v3.x());
						if (c2 < EPSILON_OUTSIDE_MIN || c2 > EPSILON_OUTSIDE_MAX)
						{
							// intersection outside triangle
							continue;
						}
						if (c2 < EPSILON_BORDER_MIN || c2 > EPSILON_BORDER_MAX)
						{
							// intersection on a vertex/edge of the triangle
							bad_intersections = true;
							continue;
						}
						if (mathdef::is_eq(v1.z(), v3.z(), EPSILON_E5))
						{
							// v1v3 edge is on OY, contradiction with the triangle normal longest
							// component on OY
							continue;
						}
						c1 = (cpoint.z() - v3.z() - c2 * (v2.z() - v3.z())) / (v1.z() - v3.z());
						if (c1 < EPSILON_OUTSIDE_MIN || c1 > EPSILON_OUTSIDE_MAX)
						{
							// intersection outside triangle
							continue;
						}
						if (c1 < EPSILON_BORDER_MIN || c1 > EPSILON_BORDER_MAX)
						{
							// intersection on a vertex/edge of the triangle
							bad_intersections = true;
							continue;
						}
					}
					else
					{
						coef = (v1.z() - v3.z()) / (v1.x() - v3.x());
						coef2 = v2.z() - v3.z() - coef * (v2.x() - v3.x());
						if (mathdef::is_eq(coef2, static_cast<ValueType>(0.0), EPSILON_E5))
						{
							// v1, v2 and v3 colliniar in OXZ, the triangle cannot have a valid
							// intersection with the OY ray
							continue;
						}
						c2 = (cpoint.z() - v3.z() - coef * (cpoint.x() - v3.x())) / coef2;
						if (c2 < EPSILON_OUTSIDE_MIN || c2 > EPSILON_OUTSIDE_MAX)
						{
							// intersection outside triangle
							continue;
						}
						if (c2 < EPSILON_BORDER_MIN || c2 > EPSILON_BORDER_MAX)
						{
							// intersection on a vertex/edge of the triangle
							bad_intersections = true;
							continue;
						}
						c1 = (cpoint.x() - v3.x() - c2 * (v2.x() - v3.x())) / (v1.x() - v3.x());
						if (c1 < EPSILON_OUTSIDE_MIN || c1 > EPSILON_OUTSIDE_MAX)
						{
							// intersection outside triangle
							continue;
						}
						if (c1 < EPSILON_BORDER_MIN || c1 > EPSILON_BORDER_MAX)
						{
							// intersection on a vertex/edge of the triangle
							bad_intersections = true;
							continue;
						}
					}
					c3 = static_cast<ValueType>(1.0) - c1 - c2;
					if (c3 < EPSILON_OUTSIDE_MIN || c3 > EPSILON_OUTSIDE_MAX)
					{
						// intersection outside triangle
						continue;
					}
					if (c3 < EPSILON_BORDER_MIN || c3 > EPSILON_BORDER_MAX)
					{
						// intersection on a vertex/edge of the triangle
						bad_intersections = true;
						continue;
					}
					y = c1 * v1.y() + c2 * v2.y() + c3 * v3.y();
					if (((trinormal.y() > static_cast<ValueType>(0.0)) &&
						 ((y - cpoint.y()) < static_cast<ValueType>(0.0))) ||
						((trinormal.y() < static_cast<ValueType>(0.0)) &&
						 ((y - cpoint.y()) > static_cast<ValueType>(0.0))))
					{
						// intersection on the other side (on the normal negative side), do not
						// count it
						continue;
					}
					// intersection on the normal positive side, count it
					++intersections_count;
					break;
				case 2:
					// ray is on OZ
					if (mathdef::is_eq(v1.x(), v3.x(), EPSILON_E5))
					{
						if (mathdef::is_eq(v2.x(), v3.x(), EPSILON_E5))
						{
							// v1, v2 and v3 colliniar in OX, not a valid triangle
							continue;
						}
						c2 = (cpoint.x() - v3.x()) / (v2.x() - v3.x());
						if (c2 < EPSILON_OUTSIDE_MIN || c2 > EPSILON_OUTSIDE_MAX)
						{
							// intersection outside triangle
							continue;
						}
						if (c2 < EPSILON_BORDER_MIN || c2 > EPSILON_BORDER_MAX)
						{
							// intersection on a vertex/edge of the triangle
							bad_intersections = true;
							continue;
						}
						if (mathdef::is_eq(v1.y(), v3.y(), EPSILON_E5))
						{
							// v1=v3, not a valid triangle
							continue;
						}
						c1 = (cpoint.y() - v3.y() - c2 * (v2.y() - v3.y())) / (v1.y() - v3.y());
						if (c1 < EPSILON_OUTSIDE_MIN || c1 > EPSILON_OUTSIDE_MAX)
						{
							// intersection outside triangle
							continue;
						}
						if (c1 < EPSILON_BORDER_MIN || c1 > EPSILON_BORDER_MAX)
						{
							// intersection on a vertex/edge of the triangle
							bad_intersections = true;
							continue;
						}
					}
					else
					{
						coef = (v1.y() - v3.y()) / (v1.x() - v3.x());
						coef2 = v2.y() - v3.y() - coef * (v2.x() - v3.x());
						if (mathdef::is_eq(coef2, static_cast<ValueType>(0.0), EPSILON_E5))
						{
							// v1, v2 and v3 colliniar in OXY, the triangle cannot have a valid
							// intersection with the OZ ray
							continue;
						}
						c2 = (cpoint.y() - v3.y() - coef * (cpoint.x() - v3.x())) / coef2;
						if (c2 < EPSILON_OUTSIDE_MIN || c2 > EPSILON_OUTSIDE_MAX)
						{
							// intersection outside triangle
							continue;
						}
						if (c2 < EPSILON_BORDER_MIN || c2 > EPSILON_BORDER_MAX)
						{
							// intersection on a vertex/edge of the triangle
							bad_intersections = true;
							continue;
						}
						c1 = (cpoint.x() - v3.x() - c2 * (v2.x() - v3.x())) / (v1.x() - v3.x());
						if (c1 < EPSILON_OUTSIDE_MIN || c1 > EPSILON_OUTSIDE_MAX)
						{
							// intersection outside triangle
							continue;
						}
						if (c1 < EPSILON_BORDER_MIN || c1 > EPSILON_BORDER_MAX)
						{
							// intersection on a vertex/edge of the triangle
							bad_intersections = true;
							continue;
						}
					}
					c3 = static_cast<ValueType>(1.0) - c1 - c2;
					if (c3 < EPSILON_OUTSIDE_MIN || c3 > EPSILON_OUTSIDE_MAX)
					{
						// intersection outside triangle
						continue;
					}
					if (c3 < EPSILON_BORDER_MIN || c3 > EPSILON_BORDER_MAX)
					{
						// intersection on a vertex/edge of the triangle
						bad_intersections = true;
						continue;
					}
					z = c1 * v1.z() + c2 * v2.z() + c3 * v3.z();
					if (((trinormal.z() > static_cast<ValueType>(0.0)) &&
						 ((z - cpoint.z()) < static_cast<ValueType>(0.0))) ||
						((trinormal.z() < static_cast<ValueType>(0.0)) &&
						 ((z - cpoint.z()) > static_cast<ValueType>(0.0))))
					{
						// intersection on the other side (on the normal negative side), do not
						// count it
						continue;
					}
					// intersection on the normal positive side, count it
					++intersections_count;
					break;
				default: break;
				};
			}  // finish for all triangles ray/triangle intersect count
			if (!bad_intersections)
				break;
		}

		if (intersections_count % 2)
		{
			// orientation (triangle normal) is not set to outside
			if ((ray_dir == 2) && !upside_OZ)
			{
				return true;
			}
			else
			{
				// general case
				return false;
			}
		}
		else
		{
			// orientation (triangle normal) is already set to outside
			if ((ray_dir == 2) && !upside_OZ)
			{
				return false;
			}
			else
			{
				// general case
				return true;
			}
		}
	}

	/// AdjustPoints method
	///
	/// Removes duplicate points
	void AdjustPoints()
	{
		const size_t szPtSize = mPointsTInd.size();

		//  0:	Not visited
		//  1:	Compared to some previous point and NOT REMOVED
		//  2:	Compared to some previous point and REMOVED
		//  0:	ALL initialy Not visited
		std::vector<int> visited(szPtSize, 0);

#pragma warning(push)
#pragma warning(disable : 4239)

		{
			// use brackets such that emptyList runs immediately out of scope
			std::vector<point3d> emptyList;
			this->mPoints->swap(emptyList);
		}

#pragma warning(pop)

		this->mPoints->reserve(szPtSize + 2);

		double dAngleLim = mathdef::Cos(m_dAngleLimit * mathdef::MW_D2R);

		size_t newPtIndex = 0;
		for (size_t i = 0; i < szPtSize; ++i)
		{
			const point3dTInd& ptTInd = mPointsTInd[i];
			const point3d& pt = ptTInd.GetPoint();
			size_t szTriIndex = ptTInd.GetTriangleIndex();
			int iPtPos = ptTInd.GetPointIndex();

			if (szTriIndex >= this->mTriangles->size())
				continue;

			const Triangle& triangle = (*this->mTriangles)[szTriIndex];
			const point3d& ptNorm = triangle.GetNormalVector();
			bool hasSharpEdge = false;

			if (visited[i] == 0)
			{
				(this->mPoints)->push_back(pt);
				newPtIndex = this->mPoints->size() - 1;
				(*this->mTriangles)[szTriIndex].SetPointIndex(iPtPos, newPtIndex);

				size_t j = i + 1;

				while (j < szPtSize)
				{
					const point3dTInd& ptTInd2 = mPointsTInd[j];
					const point3d& pt2 = ptTInd2.GetPoint();

					if (!PointsCloseEnough(pt, pt2))
						break;

					size_t szTriIndex2 = ptTInd2.GetTriangleIndex();
					const Triangle& triangle2 = (*this->mTriangles)[szTriIndex2];
					const point3d& ptNorm2 = triangle2.GetNormalVector();

					double fAngle = CalculateAngleCos(ptNorm, ptNorm2, triangle, triangle2);
					if (mathdef::is_gte(fAngle, dAngleLim))
					{
						visited[j] = 2;  //  2:	Compared to some previous point and REMOVED
						int iPtPos2 = ptTInd2.GetPointIndex();
						(*this->mTriangles)[szTriIndex2].SetPointIndex(iPtPos2, newPtIndex);
					}
					else if (visited[j] < 1)
					{
						visited[j] = 1;  //  1:	Compared to some previous point and NOT REMOVED
						hasSharpEdge = true;
					}

					j++;
				}
			}
			if (visited[i] == 1)
			{
				size_t t = i + 1;

				while (t < szPtSize)
				{
					const point3dTInd& ptTInd2 = mPointsTInd[t];
					const point3d& pt2 = ptTInd2.GetPoint();

					if ((!PointsCloseEnough(pt, pt2)) || (visited[i] != 2))
						break;

					if (visited[t] == 2)
					{
						size_t szTriIndex2 = ptTInd2.GetTriangleIndex();
						const Triangle& triangle2 = (*this->mTriangles)[szTriIndex2];
						const point3d& ptNorm2 = triangle2.GetNormalVector();

						double fAngle = CalculateAngleCos(ptNorm, ptNorm2, triangle, triangle2);
						if (mathdef::is_gte(fAngle, dAngleLim))
						{
							if (mathdef::is_gte(fAngle, dAngleLim))
							{
								visited[i] = 2;  //  2:	Compared to some previous point and REMOVED
								int iPtPos2 = ptTInd2.GetPointIndex();
								size_t szNewPtIndex =
									(*this->mTriangles)[szTriIndex2].GetPointIndex(iPtPos2);
								(*this->mTriangles)[szTriIndex].SetPointIndex(iPtPos, szNewPtIndex);
							}
							else
							{
								hasSharpEdge = true;
							}
						}
					}

					t++;
				}

				if (visited[i] < 2)
				{
					this->mPoints->push_back(pt);
					newPtIndex = this->mPoints->size() - 1;
					(*this->mTriangles)[szTriIndex].SetPointIndex(iPtPos, newPtIndex);

					size_t j = i + 1;
					while (j < szPtSize)
					{
						const point3dTInd& ptTInd2 = mPointsTInd[j];
						const point3d& pt2 = ptTInd2.GetPoint();

						if (!PointsCloseEnough(pt, pt2))
							break;

						if (visited[j] < 2)  // ALL 1's were visited already!
						{
							size_t szTriIndex2 = ptTInd2.GetTriangleIndex();
							const Triangle& triangle2 = (*this->mTriangles)[szTriIndex2];
							const point3d& ptNorm2 = triangle2.GetNormalVector();

							double fAngle = CalculateAngleCos(ptNorm, ptNorm2, triangle, triangle2);
							if (mathdef::is_gte(fAngle, dAngleLim))
							{
								visited[j] = 2;  //  2:	Compared to some previous point and REMOVED
								int iPtPos2 = ptTInd2.GetPointIndex();
								(*this->mTriangles)[szTriIndex2].SetPointIndex(iPtPos2, newPtIndex);
							}
							else if (visited[j] < 1)
							{
								visited[j] =
									1;  //  1:	Compared to some previous point and NOT REMOVED
								hasSharpEdge = true;
							}
						}

						j++;
					}
				}
			}
			if (visited[i] == 2)
			{
				size_t j = i + 1;
				while (j < szPtSize)
				{
					const point3dTInd& ptTInd2 = mPointsTInd[j];
					const point3d& pt2 = ptTInd2.GetPoint();

					if (!PointsCloseEnough(pt, pt2))
						break;

					if (visited[j] < 2)
					{
						size_t szTriIndex2 = ptTInd2.GetTriangleIndex();
						const Triangle& triangle2 = (*this->mTriangles)[szTriIndex2];
						const point3d& ptNorm2 = triangle2.GetNormalVector();

						double fAngle = CalculateAngleCos(ptNorm, ptNorm2, triangle, triangle2);
						if (mathdef::is_gte(fAngle, dAngleLim))
						{
							visited[j] = 2;  //  2:	Compared to some previous point and REMOVED
							int iPtPos2 = ptTInd2.GetPointIndex();
							size_t szNewPtIndex =
								(*this->mTriangles)[szTriIndex].GetPointIndex(iPtPos);
							(*this->mTriangles)[szTriIndex2].SetPointIndex(iPtPos2, szNewPtIndex);
						}
						else if (visited[j] < 1)
						{
							visited[j] = 1;  //  1:	Compared to some previous point and NOT REMOVED
							hasSharpEdge = true;
						}
					}

					j++;
				}
			}

			if (hasSharpEdge)
			{
				m_EdgeList.AddEdgePoint(newPtIndex);
			}
		}
	}

	/// Calculates the normal vector of a triangle.
	point3d CalculateNormalVector(const Triangle& triangle)
	{
		const point3d& p1 = this->mPointsTInd[triangle.GetFirstPointIndex()].GetPoint();
		const point3d& p2 = this->mPointsTInd[triangle.GetSecondPointIndex()].GetPoint();
		const point3d& p3 = this->mPointsTInd[triangle.GetThirdPointIndex()].GetPoint();

		const point3d calcNormal = (p1 - p2) % (p1 - p3);
		return (calcNormal * triangle.GetNormalVector() >= 0) ? calcNormal : -calcNormal;
	}

	/// CalculateAngle method
	///
	/// Calculates the angle cos between two vectors
	/// @param pt1 - first vector
	/// @param pt2 - second vector
	/// @param t1 - first triangle
	/// @param t2 - second triangle
	MW_FORCEINLINE double CalculateAngleCos(
		point3d pt1, point3d pt2, const Triangle& t1, const Triangle& t2)
	{
		double divisor = sqrt((pt1 * pt1) * (pt2 * pt2));
		if (divisor > 0)
		{
			return pt1 * pt2 / divisor;
		}

		// Try recalculating the normal vectors
		const point3d n1 = CalculateNormalVector(t1);
		const point3d n2 = CalculateNormalVector(t2);
		divisor = sqrt((n1 * n1) * (n2 * n2));
		if (divisor > 0)
		{
			return n1 * n2 / divisor;
		}

		// Fall back to 0.
		return 0;
	}

	/// CalculateNormals method
	///
	/// Calculates Vertex Normals from Triangle Normals
	void CalculateNormals()
	{
		size_t i = 0;
		size_t szPtSize = this->mPoints->size();
		size_t szTriSize = this->mTriangles->size();

		// Reassign normals vector

#pragma warning(push)
#pragma warning(disable : 4239)

		{
			// use brackets such that emptyList runs immediately out of scope
			typename cadcam::mwContainerMesh<T>::normalArray emptyList;
			this->mNormals->swap(emptyList);
		}

#pragma warning(pop)

		this->mNormals->assign(szPtSize, point3d(0, 0, 0));

		for (i = 0; i < szTriSize; ++i)
		{
			const Triangle& triangle = (*this->mTriangles)[i];
			const point3d& ptNorm = triangle.GetNormalVector();
			size_t szPtIndex1 = triangle.GetFirstPointIndex();
			size_t szPtIndex2 = triangle.GetSecondPointIndex();
			size_t szPtIndex3 = triangle.GetThirdPointIndex();

			if (szPtIndex1 < 0 || szPtIndex1 >= szPtSize || szPtIndex2 < 0 ||
				szPtIndex2 >= szPtSize || szPtIndex3 < 0 || szPtIndex3 >= szPtSize ||
				szPtIndex1 == szPtIndex2 || szPtIndex2 == szPtIndex3 || szPtIndex3 == szPtIndex1)
				continue;

			(*(this->mNormals))[szPtIndex1] += ptNorm;
			(*(this->mNormals))[szPtIndex2] += ptNorm;
			(*(this->mNormals))[szPtIndex3] += ptNorm;
		}

		point3d ptOrigin(0, 0, 0);
		for (i = 0; i < szPtSize; ++i)
		{
			if (this->mNormals->at(i) != ptOrigin)
			{
				this->mNormals->at(i).Normalize();
			}
		}

		for (i = 0; i < szTriSize; ++i)
		{
			Triangle& triangle = (*this->mTriangles)[i];
			// size_t szPt1 = triangle.GetFirstPointIndex();
			// size_t szPt2 = triangle.GetSecondPointIndex();
			// size_t szPt3 = triangle.GetThirdPointIndex();

			const point3d& p1 = (*this->mPoints)[triangle.GetFirstPointIndex()];
			const point3d& p2 = (*this->mPoints)[triangle.GetSecondPointIndex()];
			const point3d& p3 = (*this->mPoints)[triangle.GetThirdPointIndex()];

			point3d& n1 = (*this->mNormals)[triangle.GetFirstPointIndex()];
			point3d& n2 = (*this->mNormals)[triangle.GetSecondPointIndex()];
			point3d& n3 = (*this->mNormals)[triangle.GetThirdPointIndex()];

			point3d n = triangle.GetNormalVector();

			point3d calcNormal = ((p3 - p2) % (p1 - p2));
			if (calcNormal * n < 0)
				n *= -1;
			if (calcNormal * n1 < 0)
				n1 *= -1;
			if (calcNormal * n2 < 0)
				n2 *= -1;
			if (calcNormal * n3 < 0)
				n3 *= -1;

			triangle.SetNormal(n);

			triangle.SetNormalIndices(
				static_cast<int>(triangle.GetFirstPointIndex()),
				static_cast<int>(triangle.GetSecondPointIndex()),
				static_cast<int>(triangle.GetThirdPointIndex()));
		}
	}

	/// GetTriangleVertexNormal method
	///
	/// Get the vertex normal of a triangle
	/// @param szTriangle of type long - index of the triangle in the triangleArray
	/// @param iPtPos of type int - index of the point in the triangle
	/// @return ptRet of type const point3d
	MW_FORCEINLINE point3d GetTriangleVertexNormal(size_t szTriangle, int iPtPos) const
	{
		return mwContainerMesh<T>::GetTriangleVertexNormal(szTriangle, iPtPos);
	}

	/// Is edge sharp method
	///
	/// Requester for determining if the given edge is a sharp one or was smoothed
	/// @param szTriangle of type long - index of the triangle in the triangleArray
	/// @param iPtPosA of type int - index of the A edge point in the triangle
	/// @param iPtPosB of type int - index of the B edge point in the triangle
	/// @return True if the edge is sharp
public:
	MW_FORCEINLINE bool IsEdgeSharp(int szTriangle, int iPtPosA, int iPtPosB) const
	{
		Triangle triangle = (*this->mTriangles)[szTriangle];
		int szPtIndexA = static_cast<int>(triangle.GetPointIndex(iPtPosA));
		int szPtIndexB = static_cast<int>(triangle.GetPointIndex(iPtPosB));

		if (m_EdgeList.Find(szPtIndexA) && m_EdgeList.Find(szPtIndexB))
			return true;
		else
			return false;
	}

public:
	bool SharpEdgeDetector(size_t TriIndex, size_t Side) const
	{
		const TriNeighbors& Neighbor = mTriNeighbor[TriIndex];
		size_t NeighborIndex = Neighbor.GetNeighborIndex(static_cast<int>(Side));
		if (NeighborIndex == NO_NEIGHBOR)
		{
			return true;
		}

		const point3d& n1 = (*this->mTriangles)[TriIndex].GetNormalVector();
		const point3d& n2 = (*this->mTriangles)[NeighborIndex].GetNormalVector();

		ValueType div = sqrt(n1 * n1) * sqrt(n2 * n2);
		if (mathdef::is_neq(div, ValueType(0)))
		{
			// acos is not necessary
			double angle = (n1 * n2) / div;
			return angle < 0.9428 && angle > -0.9428;
		}
		else
		{
			return false;
		}
	}
};
template <typename T>
const unsigned mwTMeshVNorm<T>::NO_NEIGHBOR = static_cast<unsigned>(-1);
}  // namespace cadcam
#endif  //	MW_MWMESHVNORM_HPP_
