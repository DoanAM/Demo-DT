// (C) 2004-2021 by ModuleWorks GmbH
// Owner: MachSim

#ifndef __mwToolMeshCreator_hpp__
#define __mwToolMeshCreator_hpp__

#include "mwTool.hpp"
#include "mwToolMeshBase.hpp"
#include "mwAutoPointer.hpp"


#if defined(__GNUC__) && __GNUC__ >= 4
#pragma GCC visibility push(default)
#endif


namespace cadcam
{
	//!This class represents the creator of mesh.
	template <typename T> 
	class mwToolMeshCreator: public mwToolBranchVisitor
	{
	public:
		typedef typename cadcam::mwToolMeshBase<T>		MeshBase;
		typedef typename MeshBase::MeshPtr				MeshPtr;
		typedef typename MeshBase::MeshToolType			MeshToolType;

	public:
		//!Creates a mesh of triangles for a tool
		/*!
			\param profileTolerance the profile tolerance of the tool
		    \param collDetTol the collision tolerance of the tool
			\param myType For what parts of the tool is the mesh needed?
			\param infiniteExtenderHeight 
		 */
		mwToolMeshCreator(
			const T& profileTolerance,
			const T& collDetTol = 0,
			const MeshToolType myType = MeshBase::HAS_BOTH,
			const T infiniteExtenderHeight = 0.0,
			const bool holderOnSide = false);

		//!To create a mesh of triangles
		MeshPtr CreateMesh( bool is_normals_in = false );

		//!Was collision tolerance applied
		bool CollisionToleranceWasApplied() const;
		
		//! Visit const mwTool
		virtual void Visit(const mwTool& visitor);
		//! Visit const mwRevolvedTool
		virtual void Visit(const mwRevolvedTool& visitor);
		//! Visit const mwExtrudedTool
		virtual void Visit(const mwExtrudedTool& visitor);
		//! Visit const mwWireTool
		virtual void Visit(const mwWireTool& visitor);
		//! Visit const mwSawingTool
		virtual void Visit(const mwSawingTool& visitor);
		//! Visit const mwGenericTool
		virtual void Visit(const mwGenericTool& visitor);
		//! Visit const mwChiselingTool
		virtual void Visit(const mwChiselingTool& visitor);
		//! Visit const mwOpticDiamondTool
		virtual void Visit(const mwOpticDiamondTool& visitor);
		//! Visit const mwSpeedShapeTool
		virtual void Visit(const mwSpeedShapeTool& visitor);

	private:
		//! the profile tolerance of the tool
		T m_profileTolerance;
		//! the collision tolerance of the tool
		T m_collDetTol;
		//! For what parts of the tool is the mesh needed?
		MeshToolType m_meshType;

		// infinite extender height for sawing tools
		T m_infiniteExtenderHeight;
		bool m_holderOnSide;
#pragma warning(suppress:4251)
		misc::mwAutoPointer<MeshBase> m_meshBuilder;
	};

	template < typename T >
	bool cadcam::mwToolMeshCreator<T>::CollisionToleranceWasApplied() const
	{
		if (m_meshBuilder.IsNotNull())
			return m_meshBuilder->CollisionToleranceWasApplied();
		else
			return true;
	}

}


#if defined(__GNUC__) && __GNUC__ >= 4
#pragma GCC visibility pop
#endif


#endif //__mwToolMeshCreator_hpp__
