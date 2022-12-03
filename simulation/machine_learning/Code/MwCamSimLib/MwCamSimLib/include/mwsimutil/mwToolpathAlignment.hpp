// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwToolpathAlignment class

//#############################################################################

#ifndef MW_MWTOOLPATHALIGNMENT_HPP_
#define MW_MWTOOLPATHALIGNMENT_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include "mwMatrix.hpp"
#include "mwAutoPointer.hpp"
#include "mwTPoint3d.hpp"
//#############################################################################
namespace cadcam
{
	class mwToolPath;
}
//#############################################################################
namespace post
{
	//#############################################################################
	class mwMachDef;
	class mw3axMachDef;
	class mw4axMachDef;
	//#############################################################################
	class MW_5AXUTIL_API mwToolpathAlignment
	{
	public:
		//#############################################################################
		typedef cadcam::mwMatrix<double, 4, 4> mwMatrix4d;
		typedef misc::mwAutoPointer<mwMatrix4d>  mwMatrix4dPtr;
		typedef cadcam::mwMatrix<double, 3, 3> mwMatrix3d;
		typedef misc::mwAutoPointer<mwMatrix3d>  mwMatrix3dPtr;
		//#############################################################################
		struct Direction
		{
			enum Type
			{
				TP_UNDEFINED = -1,
				TP_3AXIS = 0,
				TP_4AXIS = 1
			};
			cadcam::mwVector3d m_vector;
			Type m_type;
		};
		//#############################################################################
		static bool IsToolpathAligned(
			const cadcam::mwToolPath& toolp,
			const mw3axMachDef& machDef,
			const double tolerance = mathdef::MW_MATH_TOL,
			const mwMatrix4dPtr& originalAllignMatrix = MW_NULL);
		//#############################################################################
		static bool IsToolpathAligned(
			const cadcam::mwToolPath& toolp,
			const mw4axMachDef& machDef,
			const double tolerance = mathdef::MW_MATH_TOL,
			const mwMatrix4dPtr& originalAllignMatrix = MW_NULL);
		//#############################################################################
		static bool IsToolpathAligned(
			const Direction& dir,
			const mw4axMachDef& machDef,
			const double tolerance = mathdef::MW_MATH_TOL,
			const mwMatrix4dPtr& originalAllignMatrix = MW_NULL);
		//#############################################################################
		static const mwMatrix4dPtr GetAllignMatrix(
			const cadcam::mwToolPath& toolp,
			const mw3axMachDef& machDef);
		//#############################################################################
		static const mwMatrix4dPtr GetAllignMatrix(
			const cadcam::mwVector3d& orientation,
			const mw3axMachDef& machDef);
		//#############################################################################
		static const mwMatrix4dPtr GetAllignMatrix(
			const cadcam::mwToolPath& toolp,
			const mw4axMachDef& machDef,
			const double tolerance = mathdef::MW_MATH_TOL);
		//#############################################################################
		static const mwMatrix4dPtr GetAllignMatrix(
			const Direction& dir,
			const mw4axMachDef& machDef);
		//#############################################################################
		static const Direction GetDirection(const cadcam::mwToolPath& toolp,
			const double tolerance = mathdef::MW_MATH_TOL);
		//#############################################################################
		static const mwMatrix4dPtr GenerateMatrix(
			const cadcam::mwVector3d& u,
			const cadcam::mwVector3d& v);
		//#############################################################################
		static const bool CheckMoveOrientation(
			const mw4axMachDef& machDef,
			const double tolerance,
			const cadcam::mwVector3d& orientation);
		//#############################################################################
		static bool AddjustAlignedMatrix(
			const cadcam::mwToolPath& toolp,
			const mwMachDef& machDef,
			mwMatrix4dPtr& allignMatrix,
			const double tolerance = mathdef::MW_MATH_TOL);
		//#############################################################################
	private:
		static void TransformDirection(
			cadcam::mwVector3d& direction,
			const mwMachDef& machDef, 
			const mwMatrix4dPtr& originalAllignMatrix);
		mwToolpathAlignment(){};
		//#############################################################################
		static void UpdateAlignedMatrix(
			mwMatrix4dPtr& originalAllignMatrix,
			const mwMatrix4dPtr& newAllignMatrix);
		//#############################################################################
	};//end class mwToolpathAlignment
	//#############################################################################
}//end namespace post
//#############################################################################
#endif	//	MW_MWTOOLPATHALIGNMENT_HPP_
