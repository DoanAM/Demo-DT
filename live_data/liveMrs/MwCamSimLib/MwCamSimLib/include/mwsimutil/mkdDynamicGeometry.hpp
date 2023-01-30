// (C) 2003-2017 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MKDDYNAMICGEOMETRY_HPP_
#define MW_MKDDYNAMICGEOMETRY_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mwVersionedObject.hpp"
#include "mkdPolygonalGeometry.hpp"


namespace machsim
{
	class MW_SIMUTIL_API mkdDynamicGeometry : public mkdPolygonalGeometry, public misc::mwVersionedObject
	{
	public:
		typedef misc::mwAutoPointer<mkdDynamicGeometry>	Ptr;

		inline explicit mkdDynamicGeometry( const id &newID,
			const misc::mwstring& STLFileName , 
            measures::mwUnitsFactory::Units unit )
			:mkdPolygonalGeometry( newID, STLFileName, unit )
		{
		};

		inline explicit mkdDynamicGeometry( const id &newID,
			polyDataRef &dataRef,
			const misc::mwstring& STLFileName , 
			measures::mwUnitsFactory::Units unit )
			:mkdPolygonalGeometry( newID, dataRef, STLFileName, unit )
		{
		};

		//!Scale
		/*!Implements measures unit transformation from metric to inch and backwards
		Scale function is implemented in 

		\param units specify the measures unit
		\param scaleFactor is the number to modify the values with
		*/
		void Scale( const measures::mwMeasurable::Units units, const double& scaleFactor ) 
		{
            mkdPolygonalGeometry::Scale( units, scaleFactor ) ;
		};

		virtual misc::mwAutoPointer<mkdKinematicObject> Clone ( const bool justKinematicRelevantInfo = false ) = 0 ;
		virtual ~mkdDynamicGeometry() {};
	protected:
	private:
	};
};
#endif	//	MW_MKDDYNAMICGEOMETRY_HPP_
