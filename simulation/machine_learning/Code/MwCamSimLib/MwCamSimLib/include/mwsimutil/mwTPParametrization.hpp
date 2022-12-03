// (C) 2003-2010 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTPPARAMETRIZATION_HPP_
#define MW_MWTPPARAMETRIZATION_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwToolPath.hpp"

namespace cadcam
{
class MW_5AXUTIL_API mwTPParametrization
{
public:
	enum mwStatus
	{
		NOT_DEFINED = 1,
		HAS_PARAMETRIZATION = 2,  // 0010
		HAS_ASCENDING = 6,  // 0110
		HAS_UNIQUE_ASCENDING = 14  // 1110
	};

	/// Create a distance based parametrization applied on the input toolpath
	///
	///	@param tp the input toolpath on which the parametrization will be computed and applied
	static void CreateDistanceBased(cadcam::mwToolPath& tp);

	/// Create a index based parametrization applied on the input toolpath
	///
	///	@param tp the input toolpath on which the parametrization will be computed and applied
	static void CreateIndexBased(cadcam::mwToolPath& tp);

	/// Reset to zero the parametrization applied on the input toolpath
	///
	///	@param tp the input toolpath on which the parametrization will be reset and applied
	static void ResetToZero(cadcam::mwToolPath& tp);

	/// Check if the toolpath does have a parametrization,as well as if it is valid ( all values are
	/// unique and ascending )
	///
	///	@return  mwTPStatus structure
	static mwStatus CheckToolPath(const cadcam::mwToolPath& tp);

protected:
	mwTPParametrization() {}
};
}  // namespace cadcam
#endif  //	MW_MWTPPARAMETRIZATION_HPP_
