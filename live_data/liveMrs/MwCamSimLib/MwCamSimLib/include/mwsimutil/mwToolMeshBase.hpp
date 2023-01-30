// (C) 2006-2015 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describes the
/// mwToolMeshBase class

#ifndef MW_MWTOOLMESHBASE_HPP_
#define MW_MWTOOLMESHBASE_HPP_
#include "mwMesh.hpp"
#include "mwTPoint3d.hpp"
#include "mwAutoPointer.hpp"

namespace cadcam
{
	//!This represents the base class for all the tool mesh builders
	template <typename T>
	class MW_5AXUTIL_API mwToolMeshBase
	{
	public:
		inline mwToolMeshBase(): m_collisionToleranceWasApplied(false) {}
		//!The used points in 3d
		typedef mwTPoint3d<T>	Point;

		//!The mesh of triangles
		typedef mwTMesh<T>		Mesh;

		//!The mesh pointer
		typedef misc::mwAutoPointer<Mesh>   MeshPtr;

		//!For what parts of the tool is the mesh needed?
		enum MeshToolType
		{
			HAS_CUTTING = 1 << 0,
			HAS_NON_CUTTING = 1 << 1,
			HAS_ARBOR = 1 << 2,
			HAS_HOLDER = 1 << 3,

			HAS_TOOL = HAS_CUTTING | HAS_NON_CUTTING | HAS_ARBOR,
			HAS_BOTH = HAS_TOOL | HAS_HOLDER
		};

		//! Virtual destructor
		virtual ~mwToolMeshBase() {};

		//!To create a mesh of triangles
		virtual MeshPtr CreateMesh(bool is_normals_in = false) = 0;
		bool CollisionToleranceWasApplied() const { return m_collisionToleranceWasApplied; }
	protected:
		bool m_collisionToleranceWasApplied;
	};
} // cadcam namespace
#endif	//	MW_MWTOOLMESHBASE_HPP_
