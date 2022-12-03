// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

/// @file
/// helper (static) functions to help mwToolApproximation


#ifndef MW_MWSOLIDDEFINITIONMESHFACTORY_HPP_
#define MW_MWSOLIDDEFINITIONMESHFACTORY_HPP_
#include "mw2dContour.hpp"
#include "mw2dPolyLine.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwExtrudedSolidDefinition.hpp"
#include "mwGenericRevolvedTool.hpp"
#include "mwMesh.hpp"
#include "mwRevolvedSolidDefinition.hpp"
#include "mwRevolvedTool.hpp"

#include "mwDeprecated.hpp"

namespace cadcam
{
	template < typename T >
	class MW_5AXUTIL_API mwSolidDefinitionMeshFactory
	{
	public:
		typedef mw2dPolyLine<T>								PolyLine2d;
		typedef typename PolyLine2d::Ptr					PolyLine2dPtr;
		typedef cadcam::mwTMesh<T>							Mesh;
		typedef misc::mwAutoPointer<Mesh>					MeshPtr;

		/// @deprecated since 2021.08 please use mwExtrudedSolidDefinition::mwContourExtrusionBase::constructionPlane
		/// Instead of e.g. mwSolidDefinitionMeshFactory::XY2XYZ
		/// please use:
		///		mwExtrudedSolidDefinition::mwContourExtrusionBase::constructionPlane = mw3dPoint(0, 0, 1)
		/// 
		typedef enum
		{
			XY2XYZ,
			XY2XZY,
			XY2YZX
		} _2D_TO_3D_MAP;

		/// Creates a mesh from a mwExtrudedSolidDefinition object
		/// @param extrudedSolid the extruded solid to be "triangulated"
		/// @param offset is the distance to offset outside and it can be negative
		/// @param tolerance is used by polygonization of contour and elimination of parallel segments
		/// @param axisMap the plane in which to position the 2d Base contour of the Extruded solid,
		/// @return the mesh
		MW_DEPRECATED("Deprecated since 2021.08, please use mwSolidDefinitionMeshFactory::Create(mwExtrudedSolidDefinition, T, T)")
		static const MeshPtr Create(
			const mwExtrudedSolidDefinition<T>& extrudedSolid,
			const T offset,
			const T tolerance,
			_2D_TO_3D_MAP axisMap);
		
		/// Creates a mesh from a mwExtrudedSolidDefinition object
		/// @param solid the extruded solid to be "triangulated"
		/// @param offset is distance to offset outside and it can be negative
		/// @param tolerance is used by polygonization of contour and elimination of parallel segments
		/// @return the mesh
		static const MeshPtr Create(
			const mwExtrudedSolidDefinition<T>& solid,
			const T offset,
			const T tolerance);
	private:
		// Offsets a closed contour
		//
		// @param contourToOffset  the input contour to offset, should be closed
		// @param offset the offset value: a positive value will offset to the outside, negative to the inside
		// @return the offset contour
		static typename mw2dContour<T>::Ptr OffsetClosedContour(
			const mw2dContour<T>& contourToOffset,
			const T offset);

		// Converts a mw2dPolyLine<T2> type object to a mw2dPolyLine<T> type object
		//
		// This is needed as a consequence of always using mwExtrudedSolidDefinitions of type double regardless of local type T
		// @param src of type mw2dPolyLine<T2> - the source for the conversion
		// @return PolyLiny2dPtr pointing to mw2dPolyLine<T> type object, the conversion's destination
		template <typename T2>
		static const PolyLine2dPtr ConvertToTType(const mw2dPolyLine<T2>& src)
		{
			PolyLine2dPtr retPolyLine(new PolyLine2d());
			typename mw2dPolyLine<T2>::PointListConstIt it, ite;
			ite = src.GetPointEnd();
			if (src.GetPointCount()>0)
			{
				it = src.GetPointBegin();
				for (; it != ite; it++)
				{
					retPolyLine->AddPoint(mwTPoint2d<T>((T)it->x(), (T)it->y()));
				}
				it = src.GetPointBegin();
				retPolyLine->AddPoint(mwTPoint2d<T>((T)it->x(), (T)it->y()));
			}
			return retPolyLine;
		}

		// Builds the "top" face of the new extruded entity, as a closed polyline 2d
		//
		// @param  baseContour of type PolyLine2dPtr, effectively the bottom face
		// @param extrusionVector of type mwExtrudedSolidDefinition<double>::Vector3d, determines the direction and amount of extrusion
		// @return  PolyLine2dPtr - the resulting top face contour
		static PolyLine2dPtr BuildExtrudedContour(const PolyLine2dPtr& baseContour,
			const typename mwExtrudedSolidDefinition<T>::Vector3d& extrusionVector);

		// Sets the coordinates of a point3d object according to a specified mapping
		//
		// @param pnt a point in 3d space
		// @param x, y, z source values
		// @param axisMap the mapping used
		static void PopulateMeshPoint(
			typename Mesh::point3d& pnt,
			const T& x,
			const T& y,
			const T& z,
			_2D_TO_3D_MAP axisMap);
	};

} // cadcam namespace
#endif	//	MW_MWSOLIDDEFINITIONMESHFACTORY_HPP_
