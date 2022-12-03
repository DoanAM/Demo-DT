// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWUNITSFACTORY_HPP_
#define MW_MWUNITSFACTORY_HPP_
#include "mwDllImpExpDef.hpp"

namespace measures
{
	class MW_5AXUTIL_API mwUnitsFactory
	{
	public:
//#############################################################################
		enum Units
		{
			METRIC = 1,
			INCH =2
		};
		/// This flag defines the base unit for the complete calculation and must be provided by constructing the parameters object.\n
		/// **Values**: METRIC for metric, INCH for English (inch) units\n
		/// Metric means that all the values used in this calculation have a unit of 1 mm.\n
		/// Inch means that all the values used in this calculation have a unit of 1 inch.\n
		/// The geometry provided to the toolkit must be defined in the unit set here.\n
		/// The resulting toolpath contains values utilizing the units specified here.
		///
		///	Default: METRIC
		///
		///	Classes that contain such a variable are derived from a common class called mwMeasurable.
		static double GetScaleFactor(Units source,Units dest);
		static Units GetUnits( bool bIsMetric );
	private:
		//! Constructor not allowed since it's a static class
		mwUnitsFactory();
	};
//#############################################################################
}
#endif	//	MW_MWUNITSFACTORY_HPP_
