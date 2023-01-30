// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMESH_HPP_
#define MW_MWMESH_HPP_
#include "mw3dObject.hpp"
#include "mwContainerMesh.hpp"
#include "mwDefines.hpp"
#include "mwOverrideFinal.hpp"

#include <algorithm>

namespace cadcam
{
template <typename T>
class mw3dBoundingBox;

#pragma CACHING_INTERNAL_BEGIN
/// class representing a Mesh structure.
///
/// The mesh is stored as a container of 3d points and a container of triangles.
/// Each triangle stores the indices of the vertices thus point data is shared.
/// Since adjacency information is not stored there are no limitations regarding
/// any topological properties.
/// @tparam T type used for coordinates of points and normals
template <typename T>
class MW_5AXUTIL_API mwTMesh: public mwContainerMesh<T>, public mw3dObject<T>
{
public:
	typedef T ValueType;  ///< Scalar type used for point, normal coordinates etc
	typedef typename misc::mwAutoPointer<mwTMesh<T>> Ptr;  ///< Auto pointer to the mesh
	typedef typename mwContainerMesh<T>::Triangle mwTTriangle;
	typedef typename mwContainerMesh<T>::TriangleVector mwTTriangleVector;
	typedef typename mwContainerMesh<T>::pointArray pointArray;
	typedef typename mwContainerMesh<T>::normalArray normalArray;
	typedef typename mwContainerMesh<T>::constNormalIt constNormalIt;
	typedef typename mwContainerMesh<T>::NormalIt NormalIt;
	typedef typename mwContainerMesh<T>::TriangleArray TriangleArray;
	typedef typename mwContainerMesh<T>::TriangleIt TriangleIt;
	typedef mwTTriangle mwTriangle;
	typedef mwTTriangleVector mwTriangleVector;
	typedef typename mwContainerMesh<T>::TFaceNormal TFaceNormal;  ///< Type used for normals
	/// mwTMesh units system
	typedef measures::mwMeasurable::Units Units;
	typedef typename mwContainerMesh<T>::TriangleVector TriangleVector;
	typedef typename mwContainerMesh<T>::constPointIt
		constPointIt;  ///< Const iterator type for mesh points
	typedef typename mwContainerMesh<T>::PointIt PointIt;  ///< Iterator type for mesh points
	typedef typename mwContainerMesh<T>::TVertex TVertex;  ///< Type used to store vertex positions
	typedef typename mwContainerMesh<T>::point3d point3d;
	typedef typename mwContainerMesh<T>::constTriangleIt
		constTriangleIt;  /// Const iterator type for triangles
	typedef mw3dBoundingBox<T> BoundingBox;


	/// Default constructor
	///
	/// @param unit represent the mesh units system
	mwTMesh(const Units& unit);

	/// Fast constructor
	///
	/// It does not eliminate possible duplicate points from pointArray.
	/// It's a trade-off between memory and speed.
	/// @param points point array for vertex positions
	/// @param triangles triangle array
	/// @param unit represent the mesh units system
	mwTMesh(const pointArray& points, const TriangleArray& triangles, const Units& unit);
	mwTMesh(
		const pointArray& points,
		const normalArray& normals,
		const TriangleArray& triangles,
		const Units& unit);
#ifndef MW_USE_VS2008_COMPATIBILITY
	mwTMesh(pointArray&& points, TriangleArray&& triangles, const Units& unit);
	mwTMesh(
		pointArray&& points, normalArray&& normals, TriangleArray&& triangles, const Units& unit);
#endif

	/// @copydoc mwTMesh(const pointArray&, const TriangleArray&, const Units&)
	mwTMesh(
		misc::mwAutoPointer<pointArray> points,
		misc::mwAutoPointer<TriangleArray> triangles,
		const Units& unit);
	mwTMesh(
		misc::mwAutoPointer<pointArray> points,
		misc::mwAutoPointer<normalArray> normals,
		misc::mwAutoPointer<TriangleArray> triangles,
		const Units& unit);

	/// Destructor
	~mwTMesh();

	/// Copy constructor
	///
	/// @param toCopy mesh to copy from
	mwTMesh(const mwTMesh<T>& toCopy);


#ifndef MW_USE_VS2008_COMPATIBILITY
	/// Move constructor
	mwTMesh(mwTMesh<T>&& other) noexcept;

	/// Move assignment operator
	mwTMesh<T>& operator=(mwTMesh<T>&& tc) noexcept;

	/// Move assignment operator
	mwTMesh<T>& operator=(mwContainerMesh<T>&& tc) noexcept;
#endif

	/// Assignment operator
	///
	/// @param tc mesh to assign
	/// @return the mesh
	const mwTMesh<T>& operator=(const mwTMesh<T>& tc);

	/// Copy constructor from mwContainerMesh
	///
	/// @param toCopy mesh to copy
	explicit mwTMesh(const mwContainerMesh<T, mwTPoint3d<T>, mwTPoint3d<T>>& toCopy);

	/// Assignment operator for mwContainerMesh<T>
	///
	/// @param tc mesh to assign
	/// @return the mesh
	const mwTMesh<T>& operator=(const mwContainerMesh<T>& tc);

	/// Accept method for visitor pattern
	///
	/// @param visitor visitor to accept
	void AcceptVisitor(mw3dObjectVisitor<T>& visitor) MW_OVERRIDE;

	/// Accept method for visitor pattern (const version)
	///
	/// @param visitor visitor to accept
	void AcceptVisitor(const mw3dObjectVisitor<T>& visitor) const MW_OVERRIDE;

	/// Get bounding box
	///
	/// @return the bounding box of the mesh
	const mw3dBoundingBox<T>& GetBoundingBox() const MW_OVERRIDE;

	/// Set bounding box
	///
	/// @param newBox bounding box to set
	void SetBoundingBox(const mw3dBoundingBox<T>& newBox);

	/// Uniformly scale the mesh
	///
	/// @param units not used
	/// @param scaleFactor scaling factor
	void Scale(const measures::mwUnitsFactory::Units units, const double& scaleFactor) MW_OVERRIDE;

	/// Add triangles from the given mesh to current mesh
	///
	/// This method combines two meshes into one.
	/// It examines the toAdd mesh and inserts the it's points into the
	/// point array preserving the sorted order and avoiding duplicates.
	/// The triangles are simply appended to the mTriangles triangle array.
	/// @param toAdd mesh to add
	void AddMesh(const mwContainerMesh<T>& toAdd) MW_OVERRIDE;

	/// Add triangles from the given mesh to current mesh skipping the check for duplicates
	///
	/// This method combines two meshes into one.
	/// It doesn't examines the toAdd mesh but just appends the points from it to the mPoints point
	/// array. The triangles are simply appended to the mTriangles triangle array.
	/// @param toAdd mesh to add
	void AddMeshFastButDontCareDuplicates(const mwContainerMesh<T>& toAdd) MW_OVERRIDE;

	/// Set triangles
	///
	/// Sets triangles from the given array of triangles to the current mesh.
	/// This method initializes the mesh with a set of triangles.
	/// The set of triangles is created using the mwTTriangleVector class.
	/// Please refer to the mwTTriangleVector its documentation.
	/// @param triVectToSet triangles to set
	void SetTriangles(const TriangleVector& triVectToSet) MW_OVERRIDE;

	/// Get a const begin iterator for the mesh points
	///
	/// @return the iterator to the first element in the mPoints array
	constPointIt GetPointsBegin() const MW_OVERRIDE { return this->mPoints->begin(); }

	/// Get a const end iterator for the mesh points
	///
	/// @return the iterator to the end of the mPoints array
	constPointIt GetPointsEnd() const MW_OVERRIDE { return this->mPoints->end(); }

	/// Get a begin iterator for the mesh points
	///
	/// @return the iterator to the first element in the mPoints array
	PointIt GetPointsBegin() MW_OVERRIDE
	{
		m_bBoxDirty = true;
		return this->mPoints->begin();
	}

	/// Get an end iterator for the mesh points
	///
	/// @return the iterator to the end of the mPoints array
	PointIt GetPointsEnd() MW_OVERRIDE
	{
		m_bBoxDirty = true;
		return this->mPoints->end();
	}

	/// Set point position
	///
	/// Changes the position of a vertex. If you want to update the normals of
	/// corresponding triangles set the recalculateNormals flag. Recalculating normals
	/// has a runtime complexity linear to the number of triangles.
	/// @param szPointIndex index of the point in the pointArray
	/// @param pt new point position
	/// @param recalculateNormals if set to true the normal of the triangle is recalculated
	void SetPoint(const size_t szPointIndex, const TVertex pt, const bool recalculateNormals)
		MW_OVERRIDE;

	/// Set point position
	///
	/// Changes the position of a vertex. If you want to update the normals of
	/// corresponding triangles set the recalculateNormals flag. Recalculating normals
	/// has a runtime complexity linear to the number of triangles.
	/// @param szPointIndex index of the point in the pointArray
	/// @param pt new point position
	/// @param recalculateNormals if set to true the normal of the triangle is recalculated
	void SetVertexPosition(
		const size_t szPointIndex, const point3d& pt, const bool recalculateNormals) MW_OVERRIDE;

	/// Reset to an empty mesh
	///
	/// Clears the array of Vertices and the array of Triangles.
	void ResetMesh() MW_OVERRIDE
	{
		mwContainerMesh<T>::ResetMesh();
		m_bBoxDirty = true;
	}

	/// Set points and triangles of the mesh
	///
	/// Previous mesh data is discarded. This method does not check
	/// the validity of the given parameters.
	/// @param points points to set
	/// @param triangles triangles to set
	void SetTriangles(
		const misc::mwAutoPointer<pointArray>& points,
		const misc::mwAutoPointer<TriangleArray>& triangles) MW_OVERRIDE;

	/// Get the point array
	///
	/// Get the points of this mesh
	/// @return the point array
	const pointArray& GetPoints() const MW_OVERRIDE;

	/// Get the point array
	///
	/// Get the points of this mesh
	/// @return the point array
	pointArray& GetPoints() MW_OVERRIDE;

	/// Get the triangle array
	///
	/// Get the triangles of this mesh
	/// @note A triangle contains only indices to the points in the point array of this mesh!
	/// @return the triangles array
	const TriangleArray& GetTriangles() const MW_OVERRIDE;

	/// Get the triangle array
	///
	/// Get the triangles of this mesh
	/// @note A triangle contains only indices to the points in the point array of this mesh!
	/// @return the triangles array
	TriangleArray& GetTriangles() MW_OVERRIDE;

	/// Add triangles from the given meshes to current mesh
	///
	/// This method combines two meshes into one.
	/// It examines all meshes and inserts their points into the
	/// point array preserving the sorted order and avoiding duplicates.
	/// The triangles are simply appended to the mTriangles triangle array.
	/// @param first - iterator to the first mesh to add
	/// @param last - past the end iterator from the container of meshes
	/// @tparam InputIterator iterator type. Must fulfill the input iterator
	/// concept and it's dereferenced type must have the interface of mwContainerMesh<T>
	template <class InputIterator>
	inline void AddMeshes(const InputIterator& first, const InputIterator& last);

	/// Swap the underlying containers. Much cheaper than copying.
	void Swap(mwTMesh<T>& other)
	{
		static_cast<mwContainerMesh<T>&>(*this).Swap(other);
		std::swap(m_bbox, other.m_bbox);
		std::swap(m_bBoxDirty, other.m_bBoxDirty);
	}

private:
	/// Basic structure to hold point input elements
	///
	/// Group together the point input iterator and its related map index
	struct PointInputStruct
	{
		PointInputStruct(unsigned index, constPointIt it): m_mapIndex(index), m_inputIt(it) {}

		unsigned m_mapIndex;
		constPointIt m_inputIt;
	};

	struct PointInputCompareStruct
	{
		PointInputCompareStruct(const mwTMesh<T>& mesh): m_mesh(mesh) {}

		/// Custom compare function used for point input vector sorting
		///
		/// Implements topological sorting between two map points.
		/// The points used for comparison are referred by each entry's iterator.
		bool operator()(const PointInputStruct& p1, const PointInputStruct& p2)
		{
			return m_mesh.ComparePoints(*p1.m_inputIt, *p2.m_inputIt, m_mesh.mPointCoordPrec);
		}

		const mwTMesh<T>& m_mesh;

	private:
		PointInputCompareStruct& operator=(const PointInputCompareStruct&);
	};

	typedef struct PointInputStruct PointMap;
	typedef std::vector<PointMap> PointMapVector;
	typedef typename std::vector<PointMap>::iterator PointMapIt;
	typedef struct PointInputCompareStruct PointMapCompare;
	typedef std::vector<unsigned> IndexVector;

	/// Decrement map indexes greater than a given value
	///
	/// It needs to be called every time a point map entry is erased in order to
	/// keep map indexes synchronized. Assuming the same erase operation is being done
	/// on the associated index map vector.
	/// @param pointInput - the point input map vector
	/// @param mapIndex - the map index upper limit
	inline void DecrementMapIndexesGT(PointMapVector& pointInput, const unsigned& mapIndex);

	/// Sort a point input map vector
	///
	/// The vector is sorted using a custom compare function which implements
	/// the topological sorting logic between two points.
	/// This function should be used for an initial presorting.
	/// @param pointInput - the point input map vector
	inline void PresortPointMapVector(PointMapVector& pointInput);

	/// Quickly sort the lower part of a point input map vector
	///
	/// This function assumes the points map vector is already sorted and should be used
	/// only when the lower portion of the map has been changed.
	/// @param pointInput - the point input map vector
	/// @param upperIndex - the upper limit of elements to be sorted
	inline void FastSortPointMapVector(PointMapVector& pointInput, const unsigned& upperIndex);

	/// Sort the minimum part of a point map vector in decreasing order of elements.
	///
	/// This function assumes the points map vector is already sorted and should be used
	/// only to fine tune the sorting of minimum values.
	/// @param pointInput - the point input map vector
	/// @param minVector - the vector holding minimum point positions
	inline void SortMinimumPointMapVector(PointMapVector& pointInput, const IndexVector& minVector);

	mutable mw3dBoundingBox<T> m_bbox;
	mutable bool m_bBoxDirty;
};

typedef mwTMesh<double> mwMesh;

template <typename T>
template <class InputIterator>
inline void mwTMesh<T>::AddMeshes(const InputIterator& first, const InputIterator& last)
{
	if (first == last)
	{
		return;
	}


	unsigned totalPoints = (unsigned)this->GetNumberOfPoints();
	unsigned totalTriangles = (unsigned)this->GetNumberOfTriangles();
	unsigned totalNormals = (unsigned)this->GetNumberOfVertexNormals();

	std::vector<PointMap> pointInput;
	std::vector<constPointIt> pointInputEnd;
	std::vector<constTriangleIt> triangleInput;
	std::vector<constTriangleIt> triangleInputEnd;
	std::vector<constNormalIt> vertexNormalInput;
	std::vector<constNormalIt> vertexNormalEnd;
	std::vector<IndexVector> pointIndexMaps;
	pointArray oldPoints;
	TriangleArray oldTriangles;
	normalArray oldVertexNormals;

	if (totalPoints > 0)
	{
		oldPoints.swap(*this->mPoints);
		oldTriangles.swap(*this->mTriangles);
		oldVertexNormals.swap(*this->mNormals);

		pointInput.push_back(PointMap(0, oldPoints.begin()));
		pointInputEnd.push_back(oldPoints.end());

		triangleInput.push_back(oldTriangles.begin());
		triangleInputEnd.push_back(oldTriangles.end());

		vertexNormalInput.push_back(oldVertexNormals.begin());
		vertexNormalEnd.push_back(oldVertexNormals.end());

		pointIndexMaps.push_back(IndexVector());
		pointIndexMaps.back().reserve(oldPoints.size());
	}

	for (InputIterator mesh = first; mesh != last; ++mesh)
	{
		if (this->GetUnits() != (*mesh)->GetUnits())
		{
			throw misc::mwException(
				3512, misc::mwstring(_T("Could not merge two meshes with different units type")));
		}

		if (mathdef::is_neq(this->GetPointCoordPrec(), (*mesh)->GetPointCoordPrec()))
		{
			throw misc::mwException(
				3515,
				misc::mwstring(
					_T("Could not merge two meshes with different point coordinates precision")));
		}

		if ((*mesh)->mPoints->size() > 0)
		{
			totalPoints += (unsigned)(*mesh)->mPoints->size();
			totalTriangles += (unsigned)(*mesh)->mTriangles->size();
			totalNormals += (unsigned)(*mesh)->mNormals->size();

			pointInput.push_back(
				PointMap((unsigned)pointIndexMaps.size(), (*mesh)->mPoints->begin()));
			pointInputEnd.push_back((*mesh)->mPoints->end());

			triangleInput.push_back((*mesh)->mTriangles->begin());
			triangleInputEnd.push_back((*mesh)->mTriangles->end());

			vertexNormalInput.push_back((*mesh)->mNormals->begin());
			vertexNormalEnd.push_back((*mesh)->mNormals->end());

			pointIndexMaps.push_back(IndexVector());
			pointIndexMaps.back().reserve((*mesh)->mPoints->size());
		}
	}

	this->mPoints->reserve(totalPoints + 1);
	this->mTriangles->reserve(totalTriangles + 1);
	this->mNormals->reserve(totalNormals + 1);

	PresortPointMapVector(pointInput);

	while (pointInput.size() > 1)
	{
		const unsigned pointInputCount = (unsigned)pointInput.size();
		IndexVector minPtInput;
		minPtInput.reserve(pointInputCount);
		minPtInput.push_back(0);

		// the first element is always the minimum point
		for (unsigned i = 1; i < pointInputCount; ++i)
		{
			if (!this->ComparePoints(
					*pointInput[0].m_inputIt, *pointInput[i].m_inputIt, this->mPointCoordPrec))
			{
				// points are equal
				minPtInput.push_back(i);
			}
			else
			{
				// stop at the first non-equal point found (vector is sorted)
				break;
			}
		}

		// entries in minimum vector should be ordered in decreasing order of their map index
		// to ensure the insertion order of mesh triangles
		//(because the vector is processed in reverse order - see bellow)
		if (minPtInput.size() > 1)
		{
			SortMinimumPointMapVector(pointInput, minPtInput);
		}

		const TVertex& pt = *pointInput[0].m_inputIt;

		// advance the point input from each mesh that contains the current point
		// and store the index it has in the new vector
		unsigned upperIndex = (unsigned)minPtInput.size();

		for (IndexVector::reverse_iterator it = minPtInput.rbegin(); it != minPtInput.rend(); ++it)
		{
			const unsigned index = *it;
			const unsigned mapIndex = pointInput[index].m_mapIndex;
			pointIndexMaps[mapIndex].push_back((unsigned)this->mPoints->size());
			if (++pointInput[index].m_inputIt == pointInputEnd[mapIndex])
			{
				const unsigned lastTriangle = (unsigned)this->mTriangles->size();
				// insert the triangles into the current mesh
				this->mTriangles->insert(
					this->mTriangles->end(), triangleInput[mapIndex], triangleInputEnd[mapIndex]);

				// remap the points for the triangles
				this->RemapTrianglePointIndices(
					this->mTriangles->begin() + lastTriangle,
					this->mTriangles->end(),
					pointIndexMaps[mapIndex]);

				if (vertexNormalInput[mapIndex] != vertexNormalEnd[mapIndex])
				{
					const unsigned lastVertexNormal = (unsigned)this->mNormals->size();
					// Add vertex normals into the current mesh
					this->mNormals->insert(
						this->mNormals->end(),
						vertexNormalInput[mapIndex],
						vertexNormalEnd[mapIndex]);

					for (TriangleIt triangleIt = this->mTriangles->begin() + lastTriangle;
						 triangleIt != this->mTriangles->end();
						 ++triangleIt)
					{
						int n1, n2, n3;
						triangleIt->GetNormalIndices(n1, n2, n3);
						triangleIt->SetNormalIndices(
							n1 > -1 ? n1 + lastVertexNormal : n1,
							n2 > -1 ? n2 + lastVertexNormal : n2,
							n3 > -1 ? n3 + lastVertexNormal : n3);
					}
				}

				// remove input information
				pointInput.erase(pointInput.begin() + index);
				pointInputEnd.erase(pointInputEnd.begin() + mapIndex);
				triangleInput.erase(triangleInput.begin() + mapIndex);
				triangleInputEnd.erase(triangleInputEnd.begin() + mapIndex);
				vertexNormalInput.erase(vertexNormalInput.begin() + mapIndex);
				vertexNormalEnd.erase(vertexNormalEnd.begin() + mapIndex);
				pointIndexMaps.erase(pointIndexMaps.begin() + mapIndex);

				DecrementMapIndexesGT(pointInput, mapIndex);
				upperIndex--;
			}
		}

		// refresh the sorting order (lower part has been changed)
		if (upperIndex > 0)
		{
			FastSortPointMapVector(pointInput, upperIndex);
		}

		this->mPoints->push_back(pt);
	}

	// one last mesh left
	if (pointInput.size() > 0)
	{
		// add the rest of the points and their indices
		for (constPointIt pt = pointInput[0].m_inputIt; pt != pointInputEnd[0]; ++pt)
		{
			pointIndexMaps[0].push_back((unsigned)this->mPoints->size());
			this->mPoints->push_back(*pt);
		}

		const unsigned lastTriangle = (unsigned)this->mTriangles->size();
		// add the triangles
		this->mTriangles->insert(this->mTriangles->end(), triangleInput[0], triangleInputEnd[0]);
		// remap points for the triangles
		this->RemapTrianglePointIndices(
			this->mTriangles->begin() + lastTriangle, this->mTriangles->end(), pointIndexMaps[0]);

		if (vertexNormalInput[0] != vertexNormalEnd[0])
		{
			const unsigned lastVertexNormal = (unsigned)this->mNormals->size();
			// Add vertex normals into the current mesh
			this->mNormals->insert(this->mNormals->end(), vertexNormalInput[0], vertexNormalEnd[0]);
			for (TriangleIt triangleIt = this->mTriangles->begin() + lastTriangle;
				 triangleIt != this->mTriangles->end();
				 ++triangleIt)
			{
				int n1, n2, n3;
				triangleIt->GetNormalIndices(n1, n2, n3);
				triangleIt->SetNormalIndices(
					n1 > -1 ? n1 + lastVertexNormal : n1,
					n2 > -1 ? n2 + lastVertexNormal : n2,
					n3 > -1 ? n3 + lastVertexNormal : n3);
			}
		}
	}

	pointArray tmp(*this->mPoints);
	this->mPoints->swap(tmp);
	m_bBoxDirty = true;
}

template <typename T>
inline void mwTMesh<T>::DecrementMapIndexesGT(PointMapVector& pointInput, const unsigned& mapIndex)
{
	for (PointMapIt it = pointInput.begin(); it != pointInput.end(); it++)
	{
		if (it->m_mapIndex > mapIndex)
		{
			it->m_mapIndex--;
		}
	}
}

template <typename T>
inline void mwTMesh<T>::PresortPointMapVector(PointMapVector& pointInput)
{
	const PointMapCompare compare(*this);

	std::sort(pointInput.begin(), pointInput.end(), compare);
}

template <typename T>
inline void mwTMesh<T>::FastSortPointMapVector(
	PointMapVector& pointInput, const unsigned& upperIndex)
{
	const PointMapCompare compare(*this);

	for (unsigned i = upperIndex; i > 0; i--)
	{
		// implement a fast sort approach by using a binary search to find
		// the required position of unsorted elements inside the already sorted array
		const PointMapIt posIt = pointInput.begin() + i;
		const PointMap val = *(posIt - 1);

		const PointMapIt lowerIt = std::lower_bound(posIt, pointInput.end(), val, compare);

		// no lower bound: here is its right position
		if (lowerIt == posIt)
		{
			continue;
		}

		// shift elements to left to make room for the newly sorted element
		for (PointMapIt it = posIt; it != lowerIt; it++)
		{
			*(it - 1) = *it;
		}

		*(lowerIt - 1) = val;
	}
}

template <typename T>
inline void mwTMesh<T>::SortMinimumPointMapVector(
	PointMapVector& pointInput, const IndexVector& minVector)
{
	struct
	{
		inline bool operator()(const PointMap& p1, const PointMap& p2)
		{
			return p1.m_mapIndex < p2.m_mapIndex;
		}
	} mapIndexComparer;

	std::sort(pointInput.begin(), pointInput.begin() + minVector.size(), mapIndexComparer);
}

template <typename T>
inline misc::mwLogger& operator<<(misc::mwLogger& os, const mwTMesh<T>& toDump)
{
	os << _T("class cadcam::mwTMesh\n");
	// public properties from cadcam::mwTMesh class.
	os << _T("GetBoundingBox                  = ") << toDump.GetBoundingBox() << _T("\n");
	os << _T("GetNumberOfTriangles            = ") << toDump.GetNumberOfTriangles() << _T("\n");
	os << _T("GetNumberOfPoints               = ") << toDump.GetNumberOfPoints() << _T("\n");
	return os;
}

#pragma CACHING_INTERNAL_END
}  // namespace cadcam
#endif  //	MW_MWMESH_HPP_
