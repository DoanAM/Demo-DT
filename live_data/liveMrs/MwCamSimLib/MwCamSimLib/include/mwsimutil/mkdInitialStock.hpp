// (C) 2007-2017 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDINITIALSTOCK_HPP_
#define MW_MKDINITIALSTOCK_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdPolygonalGeometry.hpp"


namespace machsim
{
	class MW_SIMUTIL_API mkdInitialStock : public mkdPolygonalGeometry
	{
	public:
		typedef misc::mwAutoPointer<mkdInitialStock>	Ptr;

		/*! Parameterized constructor
			\param newID the name of the object.
			\param dataRef the mesh associated to this object.
			\param unit the unit of measure.
		 */
		mkdInitialStock(const id& newID,
			polyDataRef& dataRef,
			const misc::mwstring& STLFileName,
            measures::mwUnitsFactory::Units unit);

		//! Visitor
		virtual void AcceptVisitor( mkdKOVisitor &visitor );

		//! Visitor
		virtual void AcceptVisitor( mkdKOConstVisitor &visitor ) const;

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
#endif	//	MW_MKDINITIALSTOCK_HPP_
