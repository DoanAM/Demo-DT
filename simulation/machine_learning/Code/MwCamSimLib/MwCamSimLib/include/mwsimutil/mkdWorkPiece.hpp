// (C) 2003-2017 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDWORKPIECE_HPP_
#define MW_MKDWORKPIECE_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdDynamicGeometry.hpp"

namespace machsim
{
	class MW_SIMUTIL_API mkdWorkPiece : public mkdDynamicGeometry
	{
	public:
		typedef misc::mwAutoPointer<mkdWorkPiece>	Ptr;


		/*! Parameterized constructor
			\param newID the name of this workpiece.
			\param dataRef the mesh associated to this object.
			\param STLFileName the stl file associated to the mesh.
			\param unit the unit of measure.
		 */
		mkdWorkPiece(const id& newID, 
			polyDataRef& dataRef,
			const misc::mwstring& STLFileName,
            measures::mwUnitsFactory::Units unit);

		//! Visitor
		virtual void AcceptVisitor( mkdKOVisitor &visitor );

		//! Visitor
		virtual void AcceptVisitor( mkdKOConstVisitor &visitor ) const;
    
		virtual void SetPolygonalGeometry(const polyDataRef& dataRef);

		virtual void SetPolygonalGeometry(const polyDataRef& dataRef,
			const misc::mwstring& STLFileName );

		virtual misc::mwAutoPointer<mkdKinematicObject> Clone ( const bool justKinematicRelevantInfo = false ); 		
	
	protected:
		/*! Scales the mesh associated to this object.
			\param unit the new unit of measure.
			\param scaleFactor the mesh scaling factor.
		*/
        void Scale(const Units unit, const double& scaleFactor);
	
	private:
	};
};
#endif	//	MW_MKDWORKPIECE_HPP_
