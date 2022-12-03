// (C) 2011-2017 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDWIREEDMHEAD_HPP_
#define MW_MKDWIREEDMHEAD_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdPolygonalGeometry.hpp"


namespace machsim
{
	class MW_SIMUTIL_API mkdWireEDMHead : public mkdPolygonalGeometry
	{
	public:
		typedef misc::mwAutoPointer<mkdWireEDMHead>		Ptr;

		/*! Parameterized constructor
			\param newID the name of the object
			\param dataRef the mesh associated to this object.
			\param STLFileName the associated file to the mesh data.
			\param associatedHeadID the associated head to this object.
			\param unit the unit of measure.
		 */
		mkdWireEDMHead(const id& newID, 
			polyDataRef& dataRef,
			const misc::mwstring& STLFileName, 
			const id &associatedHeadID,
			measures::mwUnitsFactory::Units unit );

	
		//! Visitor
		virtual void AcceptVisitor( mkdKOVisitor &visitor );

		//! Visitor
		virtual void AcceptVisitor( mkdKOConstVisitor &visitor ) const;

		//! Returns the associated head.
		const id& GetAssociatedHeadID() const;
        //! Set the associated head.
	    void SetAssociatedHeadID(const id& newAssociatedHeadID ); 

		virtual misc::mwAutoPointer<mkdKinematicObject> Clone ( const bool justKinematicRelevantInfo = false ); 

	protected:
		/*! Scales the mesh associated with this object.
			\param unit the new unit of measure.
			\param scaleFactor mesh scaling factor.
		 */
		void Scale(const Units unit, const double& scaleFactor ) ;


	private:
		id		m_associatedHeadID;
	};
};
#endif	//	MW_MKDWIREEDMHEAD_HPP_
