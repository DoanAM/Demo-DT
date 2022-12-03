// (C) 2005-2017 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDTAILSTOCK_HPP_
#define MW_MKDTAILSTOCK_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdDynamicGeometry.hpp"



class mwMachSimVerifier;

namespace machsim
{
	class MW_SIMUTIL_API mkdTailStock : public mkdDynamicGeometry
	{
	public:
		typedef misc::mwAutoPointer<mkdTailStock> Ptr;

		/*! Parameterized constructor
			\param newID the name of the object
			\param dataRef the mesh associated to this object.
			\param STLFileName stl file associated to the mesh.
			\param unit the unit of measure.
		 */
		mkdTailStock
			( const id& newID
			, const polyDataRef& dataRef
			, const misc::mwstring& STLFileName
            , measures::mwUnitsFactory::Units unit );

		//! Visitor
		virtual void AcceptVisitor( mkdKOVisitor &visitor );

		//! Visitor
		virtual void AcceptVisitor( mkdKOConstVisitor &visitor ) const;

		virtual misc::mwAutoPointer<mkdKinematicObject> Clone ( const bool justKinematicRelevantInfo = false ); 
	private:

	};
};
#endif	//	MW_MKDTAILSTOCK_HPP_
