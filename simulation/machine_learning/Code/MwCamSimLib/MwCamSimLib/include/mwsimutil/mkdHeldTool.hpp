// (C) 2003-2020 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDHELDTOOL_HPP_
#define MW_MKDHELDTOOL_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mwVersionedObject.hpp"
#include "mwAutoPointer.hpp"
#include "mwMesh.hpp"
#include "mkdDynamicGeometry.hpp"
#include "mwEnrichedTool.hpp"

namespace cncsim
{
	class mwIColorInfo;
	class mwIToolDisplayInfo;
}

namespace machsim
{
	class MW_SIMUTIL_API mkdHeldTool : public mkdDynamicGeometry
	{
	public:
		typedef misc::mwAutoPointer<mkdHeldTool>				Ptr;
		typedef misc::mwAutoPointer< const cadcam::mwTool >		toolRef;	

		/*! Parameterized constructor
			\param newID the name of this tool.
			\param realTool the definition of the tool associated to this kinematic object.
			\param discTol the tolerance used to create the associated mesh.
			\param STLFileName the file associated to this object's mesh.
			\param holderapp the visual attribute of the holder.
			\param arborapp the visual attribute of the arbor.
			\param noncuttpartapp the visual attribute of the non cutting part.
			\param cuttpartapp the visual attribute of the cutting part.
			\param unit the new unit of measure.
			\param addMeshReprezentation enables the mesh creation for this tool.
		 */
		mkdHeldTool(const id& newID,
			const toolRef& realTool,
			const double discTol,
			const misc::mwstring& STLFileName,
			mkdGeometry::appearance& holderapp,
			mkdGeometry::appearance& arborapp,
			mkdGeometry::appearance& noncuttpartapp,
			mkdGeometry::appearance& cuttpartapp,
            measures::mwUnitsFactory::Units unit,
			const bool addMeshReprezentation );


		//! Destructor
		~mkdHeldTool();



		//! Returns the definition of the tool associated to this kinematic object.
		const toolRef& GetToolData() const;

		//! Returns the tolerance used to create the associated mesh.
		const double& GetProfileTolerance() const;

		//! Disables mesh creation for this tool.
		void Disable();

		//! Returns if the mesh creation is disabled.
		const bool IsDisabled() const;
	
		//! Returns the visual attribute of the holder.
	    const mkdGeometry::appearance& GetHolderAppearance() const;

		//! Returns the saved visual attribute of the holder.
	    const mkdGeometry::appearance& GetSavedHolderAppearance() const;

		/*! Sets the visual attribute of the holder.
			\param HolderAppearance the visual attribute of the holder.
		 */
		void SetHolderAppearance( const mkdGeometry::appearance& HolderAppearance );

		/*! Sets the saved visual attribute of the holder.
			\param app the saved visual attribute of the holder
		 */
		void SetSavedHolderAppearance( const mkdGeometry::appearance& app );

		//! Revert the visual attribute of the holder to the saved values.
		void RevertToSavedAppearanceHolder();

		//! Revert the holder's color to the saved value.
		void RevertToSavedHolderColor();

		//! Returns the holder's visibility.
		bool GetHolderVisibility() const;

		//! Sets the holder visibility.
		void SetHolderVisibility(bool visible);

		//! Returns the arbor appearance.
		const mkdGeometry::appearance& GetArborAppearance() const ;

		//! Returns the arbor saved appearance.
		const mkdGeometry::appearance& GetSavedArborAppearance() const ;

		/*! Sets the arbor appearance
			\param arborApp the new appearance
		 */
		void SetArborAppearance( const mkdGeometry::appearance& arborApp ) ;

		/*! Sets the arbor saved appearance.
			\param arborApp the new saved appearance.
		 */
		void SetSavedArborAppearance( const mkdGeometry::appearance& arborApp ) ;

		//! Reverts the current appearance of the arbor to the saved value.
		void RevertToSavedArborAppearance() ;

		//! Revert the current color of the arbor to the saved value.
		void RevertToSavedArborColor() ;

		//! Returns the arbor visibility.
		bool GetArborVisibility() const;

		//! Sets the arbor visibility
		void SetArborVisibility(bool visible);

		//! Returns the appearance of the cutting part.
		const mkdGeometry::appearance& GetCuttingPartAppearance() const ;

		//! Returns the saved appearance of the cutting part.
		const mkdGeometry::appearance& GetSavedCuttingPartAppearance() const ;

		/*! Sets the appearance of the cutting part.
			\param cuttingApp the new appearance of the cutting part.
		 */
		void SetCuttingPartAppearance( const mkdGeometry::appearance& cuttingApp ) ;

		/*! Sets the saved appearance of the cutting part.
			\param cuttingApp the new saved appearance for the cutting part.
		 */
		void SetSavedCuttingPartAppearance( const mkdGeometry::appearance& cuttingApp ) ;

		//! Reverts the appearance of the cutting part to the saved value.
		void RevertToSavedCuttingPartAppearance();

		//! Reverts the cutting part color to the saved value.
		void RevertToSavedCuttingPartColor();

		//! Returns the cutting part visibility
		bool GetCuttingPartVisibility() const;

		/*! Sets the cutting part visibility
			\param visible the new visibility
		 */
		void SetCuttingPartVisibility(bool visible);

		//! Returns the appearance of the non cutting part.
		const mkdGeometry::appearance& GetNonCuttingPartAppearance() const;

		//! Returns the saved appearance of the non cutting part.
		const mkdGeometry::appearance& GetSavedNonCuttingPartAppearance() const;

		/*! Sets the appearance of the non cutting part
			\param nonCuttingApp the new appearance for the non cutting part.
		 */
		void SetNonCuttingPartAppearance( const mkdGeometry::appearance& nonCuttingApp );

		/*! Sets the saved appearance for the non cutting part.
			\param nonCuttingApp the new saved appearance for the non cutting part.
		 */
		void SetSavedNonCuttingPartAppearance( const mkdGeometry::appearance& nonCuttingApp );

		//! Revert the non cutting part appearance to the saved value.
		void RevertToSavedNonCuttingPartAppearance();

		//! Revert the color of non cutting part to the saved value.
		void RevertToSavedNonCuttingPartColor() ;

		//! Returns the visibility of the non cutting part.
		bool GetNonCuttingPartVisibility() const;

		/*! Sets the visibility for the non cutting part.
			\param visible the new visibility
		 */
		void SetNonCuttingPartVisibility(bool visible);

		//! Visitor
		virtual void AcceptVisitor( mkdKOVisitor& visitor );

		//! Visitor
		virtual void AcceptVisitor( mkdKOConstVisitor& visitor ) const;

		virtual misc::mwAutoPointer<mkdKinematicObject> Clone ( const bool justKinematicRelevantInfo = false ); 

		/*!
		\param newTool the definition of the tool associated to this kinematic object.
		\param discTol the tolerance used to create the associated mesh.
		\param silentCoreToolUpdateOnly if true no mesh is created.
		\param uniqueIndex used internally for optimizations
		*/
		void SetToolData(const toolRef& newTool,
			const double dDiscTol,
			const bool silentCoreToolUpdateOnly = false, const size_t uniqueIndex = 0);

		//////////// DEPRECATED
		typedef cadcam::mwEnrichedTool::toolPartType			toolPartType;
		typedef cadcam::mwEnrichedTool::ToolPartsMeshes			toolPartsMeshes;

		/*! Parameterized constructor
		\param newID the name of this tool.
		\param realTool the definition of the tool associated to this kinematic object.
		\param discTol the tolerance used to create the associated mesh.
		\param STLFileName the file associated to this object's mesh.
		\param holderapp the visual attribute of the holder.
		\param arborapp the visual attribute of the arbor.
		\param noncuttpartapp the visual attribute of the non cutting part.
		\param cuttpartapp the visual attribute of the cutting part.
		\param unit the new unit of measure.
		\param spindleOffMeshes tool mesh representation when spindle is off.
		\param addMeshReprezentation enables the mesh creation for this tool.
		*/
		mkdHeldTool(const id& newID,
			const toolRef& realTool,
			const double discTol,
			const misc::mwstring& STLFileName,
			mkdGeometry::appearance& holderapp,
			mkdGeometry::appearance& arborapp,
			mkdGeometry::appearance& noncuttpartapp,
			mkdGeometry::appearance& cuttpartapp,
			measures::mwUnitsFactory::Units unit,
			const toolPartsMeshes& spindleOffMeshes,
			const bool addMeshReprezentation);

		//!Toggle tool's "spindle off" mode
		void ToggleSpindleOffMeshes(const bool toggle);

		//!Get the tool's "spindle off" mode meshes
		toolPartsMeshes GetSpindleOffMeshes() const;

		//!Query tool's "spindle off" mode activation status
		const bool AreSpindleOffMeshesEnabled() const;

		/*!
		\param newTool the definition of the tool associated to this kinematic object.
		\param discTol the tolerance used to create the associated mesh.
		\param spindleOffMeshes tool mesh representation when spindle is off.
		\param silentCoreToolUpdateOnly if true no mesh is created.
		*/
		void SetToolData(const toolRef& newTool,
			const double dDiscTol,
			const toolPartsMeshes& spindleOffMeshes,
			const bool silentCoreToolUpdateOnly = false);

		//////////// END DEPRECATED

		/// internal, do not use
		void SetUniqueIndex(const size_t id) const;
		/// internal, do not use
		const size_t GetUniqueIndex() const;

		virtual void SetPolygonalGeometry(const polyDataRef& dataRef);
		virtual void SetPolygonalGeometry(const polyDataRef& dataRef,
			const misc::mwstring& STLFileName );

		virtual polyDataRef& GetPolygonalGeometry();
		virtual const polyDataRef& GetPolygonalGeometry() const;

	protected:
		/*! Scales the object.
			\param units the new unit of measure.
			\param scaleFactor the scaling factor.
		*/
		virtual void Scale(const measures::mwMeasurable::Units units, const double& scaleFactor);


	private:

		void Initialize( const toolRef& realTool, const double discTol, 
			mkdGeometry::appearance& holderapp, 
			mkdGeometry::appearance& arborapp,
			mkdGeometry::appearance& noncuttpartapp,
			mkdGeometry::appearance& cuttpartapp,
			const bool addMeshReprezentation );

		void CreateToolMesh() const;

		void SetToolPartAppearance(const mkdGeometry::appearance& srcToolPart, mkdGeometry::appearance& dstToolPart,
			misc::mwAutoPointer<mkdGeometry::appearance>& savedToolPart, cadcam::mwTool::ToolPartFlags toolPartFlags
		);
		void RevertToSavedToolPartAppearance(const misc::mwAutoPointer<mkdGeometry::appearance>& srcSavedToolPart, 
			mkdGeometry::appearance& dstToolPart, cadcam::mwTool::ToolPartFlags toolPartFlags
		);
		
#pragma warning(push)
#pragma warning(disable:4251)
		toolRef												m_realTool;

		misc::mwAutoPointer<mkdGeometry::appearance>		m_savedHolderAppearance;
		misc::mwAutoPointer<mkdGeometry::appearance>		m_savedArborAppearance;
		misc::mwAutoPointer<mkdGeometry::appearance>		m_savedCuttingPartAppearance;
		misc::mwAutoPointer<mkdGeometry::appearance>		m_savedNonCuttingPartAppearance;

		// deprecated
		toolPartsMeshes										m_spindleOffMeshes;
#pragma warning(pop)

		mkdGeometry::appearance								m_holderAppearance;
		bool												m_isHolderVisible;
		
		mkdGeometry::appearance								m_arborAppearance ;
		bool												m_isArborVisible;

		mkdGeometry::appearance								m_cuttingPartAppearance ;
		bool												m_isCuttingPartVisible;

		mkdGeometry::appearance								m_nonCuttingPartAppearance ;
		bool												m_isNonCuttingPartVisible;
		
		bool												m_disabled;
		double												m_discTol;

		mutable size_t m_uniqueIndex;

		mutable bool                                        m_meshUpToDate;
		bool												m_addMeshRepresentation; 
	};
};
#endif	//	MW_MKDHELDTOOL_HPP_
