// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPosted3axTPInterpolate class

//#############################################################################

#ifndef MW_MWPOSTED3AXTPINTERPOLATE_HPP_
#define MW_MWPOSTED3AXTPINTERPOLATE_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include "mwTPoint3d.hpp"
#include "mwPostedUtils.hpp"
#include "mw3axMachDef.hpp"
#include "mwMXPParam.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class mwMXPParam;
	//#############################################################################
	class MW_5AXUTIL_API mwPosted3axTPInterpolate  
	{
	public:
		//#############################################################################
		typedef std::list<mwPosted3axMove>                            posted3axList;
		typedef misc::mwAutoPointer<posted3axList>                    posted3axListPtr;
		typedef posted3axList::iterator                               iterator;
		typedef posted3axList::const_iterator                         const_iterator;
		//#############################################################################
		//! Constructor
		mwPosted3axTPInterpolate(
			const mw3axMachDef& machDef,
			const mwMXPParam& mxpParam,
			const cadcam::mwVector3d& partOrigin,
			const double toolLengthCompensationValue,
			mwTransformation3dPtr mwTransformation3dPtr = MW_NULL);
		//#############################################################################
		const mwPosted3axMove PostMove(
			const misc::mwAutoPointer<cadcam::mwCNCMove>& move,
			const mwPostedMove::Types moveType,
			const size_t index,
			const bool addOnPost,
			const bool createShortList = false,
			const bool isCorner = false) const;
		//#############################################################################
		const posted3axListPtr Interpolate(
			const mwPosted3axMove& postedStart,
			const mwPosted3axMove& postedEnd,
			const bool createShortList = false) const;
		//#############################################################################
		const mwTransformation3dPtr& GetTransfor3d() const;
		//#############################################################################
		void SetTransfor3d(const mwTransformation3dPtr& transf);
		//#############################################################################
		mwMXPParam& GetMxpParamRef()
		{
			return m_mxpParam;
		}
		//#############################################################################
		void SetMachDef(const mw3axMachDef& machDef);
		//#############################################################################
	private:
#pragma warning(push)
#pragma warning(disable:4251)
		//#############################################################################
		mwPosted3axTPInterpolate operator = (const mwPosted3axTPInterpolate&);
		//#############################################################################
		mw3axMachDef              m_machDef;
		mwMXPParam                m_mxpParam;
		const cadcam::mwVector3d  m_partOrigin;
		const double              m_toolLengthCompensationValue;
		mwTransformation3dPtr     m_mwTransformation3dPtr;
		//#############################################################################
		const posted3axListPtr CreateListOfPostedMove(
			const mwPosted3axMove& postedStart,
			const mwPosted3axMove& postedEnd,
			const bool createShortList) const;
		//#############################################################################
		const int ComputeStepsMove(
			const mwPosted3axMove& postedStart,
			const mwPosted3axMove& postedEnd) const;
		//#############################################################################
		const mwPosted3axMove GenerateStepUsingInterpolateValue(
			const double k,
			const mwPosted3axMove& postedStart,
			const mwPosted3axMove& postedEnd,
			const bool createShortList) const;
#pragma warning(pop)
		//#############################################################################
	};// end class mwPosted3axTPInterpolate
	//#############################################################################
}//end namespace post
//#############################################################################
#endif	//	MW_MWPOSTED3AXTPINTERPOLATE_HPP_
