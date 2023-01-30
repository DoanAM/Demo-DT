// (C) 2004-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTMESHSERVICE_HPP_
#define MW_MWTMESHSERVICE_HPP_
#include "mwMatrix.hpp"
#include "mwMesh.hpp"


namespace cadcam
{
/// Apply different transformations to a mwTMesh
template <typename T, typename TVertex = mwTPoint3d<T>, typename TFaceNormal = mwTPoint3d<T>>
class MW_5AXUTIL_API mwTMeshService
{
public:
	typedef mwContainerMesh<T, TVertex, TFaceNormal> Mesh;
	typedef typename Mesh::Ptr MeshPtr;
	typedef typename Mesh::Triangle triangle3d;
	typedef typename Mesh::point3d point3d;
	typedef typename Mesh::vector3d vector3d;
	typedef mwMatrix<T, 3, 3> mwMatrix3d;
	typedef mwMatrix<T, 4, 4> mwMatrix4d;

private:
	template <typename T1>
	class FunctTransformNormal
	{
	private:
		/// The offset
		mwMatrix4d m_Matrix;

	public:
		/// Constructor initializes the offset
		FunctTransformNormal(const mwMatrix4d& matrix): m_Matrix(matrix)
		{
			// Removed translation part from the matrix (the normals need to be transformed only
			// by the rotational part).
			m_Matrix[0][3] = 0.0;
			m_Matrix[1][3] = 0.0;
			m_Matrix[2][3] = 0.0;

			m_Matrix[3][0] = 0.0;
			m_Matrix[3][1] = 0.0;
			m_Matrix[3][2] = 0.0;
			m_Matrix[3][3] = 1.0;

			m_Matrix = Transpose(!m_Matrix);
		}

		/// The function call for the element to be offset
		void operator()(triangle3d& triangle) const
		{
			if (triangle.GetNormalVector() != point3d(0, 0, 0))
			{
				point3d normal = triangle.GetNormalVector();
				normal.Transform(m_Matrix);
				triangle.SetNormalVector(normal);
			}
		}
	};

	template <
		typename T2,
		typename TVertex2 = mwTPoint3d<T2>,
		typename TFaceNormal2 = mwTPoint3d<T2>>
	class FunctIsNormalDegenerated
	{
	public:
		typedef mwContainerMesh<T2, TVertex2, TFaceNormal2> Mesh;
		typedef typename Mesh::Triangle Triangle;
		/// Constructor
		FunctIsNormalDegenerated(Mesh& mesh): m_Mesh(mesh) {}

		/// The function call for the triangle to be checked
		bool operator()(const Triangle& triangle) const
		{
			return mathdef::is_eq(~triangle.GetNormalVector(), (T)0);
		}

	private:
		/// The mesh
		Mesh& m_Mesh;
	};

	template <typename T2>
	class FunctTransformNormal3d
	{
	private:
		/// The offset
		mwMatrix3d m_Matrix;

	public:
		/// Constructor initializes the offset
		FunctTransformNormal3d(mwMatrix3d matrix): m_Matrix(matrix)
		{
			m_Matrix = Transpose(!m_Matrix);
		}

		/// The function call for the element to be offset
		void operator()(triangle3d& triangle) const
		{
			if (triangle.GetNormalVector() != point3d(0, 0, 0))
			{
				point3d normal = triangle.GetNormalVector();
				normal.Transform(m_Matrix);
				triangle.SetNormal(normal);
			}
		}
	};

public:
	/// Scale a mesh by multiplying each point of the containing triangles
	/// with a scale factor
	/// 
	/// @param mesh mesh to scale
	/// @param scaleFactor the scale factor
	static void Scale(Mesh& mesh, const T& scaleFactor)
	{
		if (scaleFactor <= mathdef::MW_MATH_TOL)
			throw misc::mwException(0, _T("Scale factor should be strictly greater than zero"));

		if (mathdef::is_eq(scaleFactor, static_cast<T>(1)))
			return;

		for (typename Mesh::PointIt pos = mesh.GetPointsBegin(); pos != mesh.GetPointsEnd(); ++pos)
			(*pos) *= scaleFactor;
	}


	/// Move a mesh by translating each point of the containing triangles
	/// with a vector
	/// 
	/// @param mesh mesh to move
	/// @param vMove the vector that will be used for translating each point
	static void Move(Mesh& mesh, const TVertex& vMove)
	{
		if (mathdef::is_eq(~vMove, static_cast<T>(0)))
			return;

		for (typename Mesh::PointIt pos = mesh.GetPointsBegin(); pos != mesh.GetPointsEnd(); ++pos)
			(*pos) += vMove;
	}


	/// Transform a mesh
	///
	/// by transforming each point and each normal
	/// of the containing triangles with a <3,3> matrix
	/// @param mesh mesh to transform
	/// @param transf the transformation matrix to use
	static void Transform(Mesh& mesh, const mwMatrix3d& transf)
	{
		mwMatrix4d hMatrix;
		for (int row = 0; row < 3; ++row)
		{
			for (int col = 0; col < 3; ++col)
			{
				hMatrix[row][col] = transf[row][col];
			}
		}
		Transform(mesh, hMatrix);
	}


	/// Transform a mesh
	///
	/// by transforming each point and each normal
	/// of the containing triangles with a <4,4> matrix
	/// @param mesh mesh to transform
	/// @param transf the transformation matrix to use
	static void Transform(Mesh& mesh, const mwMatrix4d& transf)
	{
		mwMatrix4d duplicate(transf);  // VC6 compiler bug, it must see mwMatrix4d in this function,
		// don't understand why. If the name is missing is reporting errors in other functions from
		// this class....i'm lost does not make any sense.
		size_t count = 0;
		for (typename Mesh::PointIt pos = mesh.GetPointsBegin(); pos != mesh.GetPointsEnd();
			 ++pos, ++count)
			pos->Transform(duplicate);

		// Removed translation part from the matrix (the normals need to be transformed only
		// by the rotational part).
		duplicate[0][3] = 0.0;
		duplicate[1][3] = 0.0;
		duplicate[2][3] = 0.0;

		duplicate[3][0] = 0.0;
		duplicate[3][1] = 0.0;
		duplicate[3][2] = 0.0;
		duplicate[3][3] = 1.0;

		duplicate = Transpose(!duplicate);

		for (typename Mesh::NormalIt normal = mesh.GetVertexNormalsBegin();
			 normal != mesh.GetVertexNormalsEnd();
			 ++normal)
			normal->Transform(duplicate);


		typename Mesh::TriangleArray& triArray = mesh.GetTriangles();
		std::for_each(triArray.begin(), triArray.end(), FunctTransformNormal<T>(transf));
	}


	/// Transform with rotation and translation
	///
	/// Transforms a mesh, by transforming each point and each normal
	/// of the containing triangles with a <3,3> matrix and a translation.
	/// The translation is performed first.
	/// We need this simplified form of translation because the translation
	/// that uses a <4,4> matrix takes too much time with unnecessary computations.
	/// @param mesh mesh to transform
	/// @param rotation rotation matrix to use
	/// @param translation translation vector to use
	static void Transform(Mesh& mesh, const mwMatrix3d& rotation, const point3d& translation)
	{
		mwMatrix3d duplicate(
			rotation);  // VC6 compiler bug, it must see mwMatrix4d in this function,
		// don't understand why. If the name is missing is reporting errors in other functions from
		// this class....i'm lost does not make any sense.
		for (typename Mesh::PointIt pos = mesh.GetPointsBegin(); pos != mesh.GetPointsEnd(); ++pos)
			pos->Transform3d(duplicate, translation);

		duplicate = Transpose(!duplicate);
		for (typename Mesh::NormalIt normal = mesh.GetVertexNormalsBegin();
			 normal != mesh.GetVertexNormalsEnd();
			 ++normal)
			normal->Transform(duplicate);

		typename Mesh::TriangleArray& triArray = mesh.GetTriangles();
		std::for_each(triArray.begin(), triArray.end(), FunctTransformNormal3d<T>(rotation));
	}


	/// Calculate the bounding box of a mesh
	///
	/// @param mesh reference to the input mesh
	/// @return the bounding box
	static const mw3dBoundingBox<T> CalculateBoundingBox(const Mesh& mesh)
	{
		mw3dBoundingBox<T> bbox;
		size_t szTriSize = mesh.GetNumberOfTriangles();
		if (szTriSize <= 0)
		{
			return bbox;
		}
		T minx = mathdef::mw_maxvalue(T());
		T maxx = -mathdef::mw_maxvalue(T());
		T miny = mathdef::mw_maxvalue(T());
		T maxy = -mathdef::mw_maxvalue(T());
		T minz = mathdef::mw_maxvalue(T());
		T maxz = -mathdef::mw_maxvalue(T());

		for (size_t i = 0; i < szTriSize; ++i)
		{
			const point3d& pt1 = mesh.GetTriangleFirstVertexPosition(i);
			const point3d& pt2 = mesh.GetTriangleSecondVertexPosition(i);
			const point3d& pt3 = mesh.GetTriangleThirdVertexPosition(i);
			T x1 = static_cast<T>(pt1.x());
			T x2 = static_cast<T>(pt2.x());
			T x3 = static_cast<T>(pt3.x());
			T y1 = static_cast<T>(pt1.y());
			T y2 = static_cast<T>(pt2.y());
			T y3 = static_cast<T>(pt3.y());
			T z1 = static_cast<T>(pt1.z());
			T z2 = static_cast<T>(pt2.z());
			T z3 = static_cast<T>(pt3.z());
			minx = (minx < x1) ? minx : x1;
			minx = (minx < x2) ? minx : x2;
			minx = (minx < x3) ? minx : x3;
			miny = (miny < y1) ? miny : y1;
			miny = (miny < y2) ? miny : y2;
			miny = (miny < y3) ? miny : y3;
			minz = (minz < z1) ? minz : z1;
			minz = (minz < z2) ? minz : z2;
			minz = (minz < z3) ? minz : z3;
			maxx = (maxx > x1) ? maxx : x1;
			maxx = (maxx > x2) ? maxx : x2;
			maxx = (maxx > x3) ? maxx : x3;
			maxy = (maxy > y1) ? maxy : y1;
			maxy = (maxy > y2) ? maxy : y2;
			maxy = (maxy > y3) ? maxy : y3;
			maxz = (maxz > z1) ? maxz : z1;
			maxz = (maxz > z2) ? maxz : z2;
			maxz = (maxz > z3) ? maxz : z3;
		}
		bbox.SetCorners(mwTPoint3d<T>(minx, miny, minz), mwTPoint3d<T>(maxx, maxy, maxz));
		return bbox;
	}


	/// Removes type 1 degenerated triangles from the mesh
	///
	/// @param mesh input mesh
	/// @param max_nondegen size for resulting triangle vector
	/// @returns cleaned mesh
	static const MeshPtr RemoveType1DegeneratedTriangles(Mesh& mesh, const size_t max_nondegen)
	{
		typename Mesh::TriangleArray& triangleVector = mesh.GetTriangles();
		misc::mwAutoPointer<typename Mesh::TriangleArray> copyTris =
			new typename Mesh::TriangleArray(max_nondegen);
		misc::mwAutoPointer<typename Mesh::pointArray> copyPoints(&mesh.GetPoints());
		copyPoints.Release();
		FunctIsNormalDegenerated<T, TVertex, TFaceNormal> condition(mesh);
		copyTris->erase(
			std::remove_copy_if(
				triangleVector.begin(), triangleVector.end(), copyTris->begin(), condition),
			copyTris->end());

		return new Mesh(copyPoints, copyTris, mesh.GetUnits());
	}


private:
	/// Constructor not allowed since it's a static class
	mwTMeshService();
};
}  // namespace cadcam
#endif  //	MW_MWTMESHSERVICE_HPP_
