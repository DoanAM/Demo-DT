// (C) 2003-2017 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDFIXTURE_HPP_
#define MW_MKDFIXTURE_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mkdDynamicGeometry.hpp"



namespace machsim
{
	class MW_SIMUTIL_API mkdFixture : public mkdDynamicGeometry
	{
	public:
		typedef misc::mwAutoPointer<mkdFixture> Ptr;

		/*! Parameterized constructor
			\param newID the name of this fixture.
			\param dataRef the mesh associated to this object.
			\param STLFileName the stl file associated to the mesh.
			\param unit the unit of measure.
		 */
		mkdFixture( const id& newID,
			polyDataRef& dataRef,
			const misc::mwstring& STLFileName,
            measures::mwUnitsFactory::Units unit );

		//! Visitor
		virtual void AcceptVisitor( mkdKOVisitor &visitor );

		//! Visitor
		virtual void AcceptVisitor( mkdKOConstVisitor &visitor ) const;

		/*! Sets the mesh associated to this fixture.
			\param dataRef the mesh associated to this object.
		 */
		virtual void SetPolygonalGeometry(const polyDataRef& dataRef);

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
#endif	//	MW_MKDFIXTURE_HPP_
