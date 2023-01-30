// (C) 2007-2019 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwMachDefUtils class

//#############################################################################

#ifndef MW_MWMACHDEFUTILS_HPP_
#define MW_MWMACHDEFUTILS_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include "mwMachDef.hpp"
#include "mw3axMachDef.hpp"
#include "mw4axMachDef.hpp"
#include "mw5axMachDef.hpp"
#include "mw6axMachDef.hpp"
#include "mw6axCSMachDef.hpp"
#include "mwPostException.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	//! this class stores methods for mwMachDef (machine definition)
	class MW_5AXUTIL_API mwMachDefUtils 
	{
	public:
		//#############################################################################
		//! Static function used to compare two machine definition
		/*!
			\return true if both machine are equal
		*/
		static bool is_eq(const mwMachDefPtr& m1, const mwMachDefPtr& m2);
		//#############################################################################
		//! Static function to extract 4axis machine type
		static mw4axMachDef::MachType Get4axMachType(const mwMachDefPtr& machDefPtr);
		//#############################################################################
		//! Static function to extract 5axis machine type
		static mw5axMachDef::MachType Get5axMachType(const mwMachDefPtr& machDefPtr);
		//#############################################################################
		//! Static function to extract 6axis first rotary mounting position (HEAD or TABLE)
		static mw6axMachDef::AxisType Get6ax1stAxisType(const mwMachDefPtr& machDefPtr);
		//#############################################################################
		//! Static function to extract 6axis second rotary mounting position (HEAD or TABLE)
		static mw6axMachDef::AxisType Get6ax2ndAxisType(const mwMachDefPtr& machDefPtr);
		//#############################################################################
		//! Static function to extract 6axis third rotary mounting position (HEAD or TABLE)
		static mw6axMachDef::AxisType Get6ax3rdAxisType(const mwMachDefPtr& machDefPtr);
		//#############################################################################
		//! Static function to extract 6axis contour first rotary mounting position (HEAD or TABLE)
		static mw6axCSMachDef::AxisType Get6axCS1stAxisType(const mwMachDefPtr& machDefPtr);
		//#############################################################################
		//! Static function to extract 6axis contour second rotary mounting position (HEAD or TABLE)
		static mw6axCSMachDef::AxisType Get6axCS2ndAxisType(const mwMachDefPtr& machDefPtr);
		//#############################################################################
		//! Static function to extract 6axis contour third rotary mounting position (HEAD or TABLE)
		static mw6axCSMachDef::AxisType Get6axCS3rdAxisType(const mwMachDefPtr& machDefPtr);
		//#############################################################################
		//! Return number of axis (3,4,5,5+1 or 6ais contour)
		static size_t GetNumbersOfAxes(const mwMachDefPtr& machDefPtr);
		//#############################################################################
		//! Return number of axis (3,4,5,5+1 or 6ais contour)
		static size_t GetNumbersOfAxes(const mwMachDef& machDef);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 3axis machine definition, throw exception if instance is wrong
		static const mw3axMachDefPtr SafeCast3ax(const mwMachDefPtr& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 3axis machine definition, throw exception if instance is wrong
		static mw3axMachDefPtr SafeCast3ax(mwMachDefPtr& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 3axis machine definition, throw exception if instance is wrong
		static const mw3axMachDef SafeCast3ax(const mwMachDef& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 3axis machine definition, throw exception if instance is wrong
		static mw3axMachDef& SafeCast3ax(mwMachDef& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 4axis machine definition, throw exception if instance is wrong
		static const mw4axMachDefPtr SafeCast4ax(const mwMachDefPtr& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 4axis machine definition, throw exception if instance is wrong
		static mw4axMachDefPtr SafeCast4ax(mwMachDefPtr& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 4axis machine definition, throw exception if instance is wrong
		static const mw4axMachDef SafeCast4ax(const mwMachDef& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 4axis machine definition, throw exception if instance is wrong
		static mw4axMachDef& SafeCast4ax(mwMachDef& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 5axis machine definition, throw exception if instance is wrong
		static const mw5axMachDefPtr SafeCast5ax(const mwMachDefPtr& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 5axis machine definition, throw exception if instance is wrong
		static mw5axMachDefPtr SafeCast5ax(mwMachDefPtr& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 5axis machine definition, throw exception if instance is wrong
		static const mw5axMachDef SafeCast5ax(const mwMachDef& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 5axis machine definition, throw exception if instance is wrong
		static mw5axMachDef& SafeCast5ax(mwMachDef& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 5+1axis machine definition, throw exception if instance is wrong
		static const mw6axMachDefPtr SafeCast6ax(const mwMachDefPtr& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 5+1axis machine definition, throw exception if instance is wrong
		static mw6axMachDefPtr SafeCast6ax(mwMachDefPtr& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 5+1axis machine definition, throw exception if instance is wrong
		static const mw6axMachDef SafeCast6ax(const mwMachDef& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 5+1axis machine definition, throw exception if instance is wrong
		static mw6axMachDef& SafeCast6ax(mwMachDef& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 6axis machine definition, throw exception if instance is wrong
		static const mw6axCSMachDefPtr SafeCast6axCS(const mwMachDefPtr& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 6axis machine definition, throw exception if instance is wrong
		static mw6axCSMachDefPtr SafeCast6axCS(mwMachDefPtr& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 6axis machine definition, throw exception if instance is wrong
		static const mw6axCSMachDef SafeCast6axCS(const mwMachDef& mw);
		//#############################################################################
		//! Safe cast of base class machine definition pointer to 6axis machine definition, throw exception if instance is wrong
		static mw6axCSMachDef& SafeCast6axCS(mwMachDef& mw);
		//#############################################################################
		//! Creates a machine definition base on parameters pvovided
		/*!
			\param nr defines number of axis
			\param units defines units used
			\param spindleDirection defines spindle
			\param TransAxisMinLimit defines minimum translations limit
			\param TransAxisMaxLimit defines maximum translations limit
			\param translationX defines X translation direction
			\param translationY defines Y translation direction
			\param translationZ defines Z translation direction
			\param workpieceTransform defines a 4x4 transformation matrix for workpiece
			\param holderTransform defines a 4x4 transformation matrix for holder
			\param rotAxisDirection0 defines first rotary direction
			\param rotAxisDirection1 defines second rotary direction
			\param rotAxisDirection2 defines third rotary direction
			\param rotAxisBasePoint0 defines first rotary base point
			\param rotAxisBasePoint1 defines second rotary base point
			\param rotAxisBasePoint2 defines third rotary base point
			\param vRotAxisMinLimit0 defines first rotary axis minimum limit
			\param vRotAxisMinLimit1 defines second rotary axis minimum limit
			\param vRotAxisMinLimit2 defines third rotary axis minimum limit
			\param vRotAxisMaxLimit0 defines first rotary axis maximum limit
			\param vRotAxisMaxLimit1 defines second rotary axis maximum limit
			\param vRotAxisMaxLimit2 defines third rotary axis maximum limit
			\param _1stType define first rotary axis mounting position (HEAD or TABLE)
			\param _2ndType define second rotary axis mounting position (HEAD or TABLE)
			\param _3rdType define third rotary axis mounting position (HEAD or TABLE)
			\param machine5axKinematicType define 5axis machine kinematic type
			\param machine4axKinematicType define 4axis machine kinematic type
			\param sawDirection defines contour (saw) cutting direction
			\param type defines machine type
			\param doValidations activate machine validation on constructor		
		*/
		static mwMachDefPtr BuildMachDef(
			const mwMachDef::NumbersOfAxes nr,
			const measures::mwUnitsFactory::Units units,
			const cadcam::mwVector3d& spindleDirection,
			const cadcam::mwPoint3d& TransAxisMinLimit = -mwMachDef::LimitTranslation(),
			const cadcam::mwPoint3d& TransAxisMaxLimit = mwMachDef::LimitTranslation(),
			const cadcam::mwVector3d& translationX = cadcam::mwVector3d(1., 0., 0.),
			const cadcam::mwVector3d& translationY = cadcam::mwVector3d(0., 1., 0.),
			const cadcam::mwVector3d& translationZ = cadcam::mwVector3d(0., 0., 1.),
			const mwMachDef::mwMatrix4dPtr& workpieceTransform = MW_NULL,
			const mwMachDef::mwMatrix4dPtr& holderTransform = MW_NULL,
			const cadcam::mwVector3d& rotAxisDirection0 = cadcam::mwVector3d(),
			const cadcam::mwVector3d& rotAxisDirection1 = cadcam::mwVector3d(),
			const cadcam::mwVector3d& rotAxisDirection2 = cadcam::mwVector3d(),
			const cadcam::mwPoint3d& rotAxisBasePoint0 = cadcam::mwPoint3d(),
			const cadcam::mwPoint3d& rotAxisBasePoint1 = cadcam::mwPoint3d(),
			const cadcam::mwPoint3d& rotAxisBasePoint2 = cadcam::mwPoint3d(),
			const double vRotAxisMinLimit0 = mathdef::MW_MIN_DOUBLE,
			const double vRotAxisMinLimit1 = mathdef::MW_MIN_DOUBLE,
			const double vRotAxisMinLimit2 = mathdef::MW_MIN_DOUBLE,
			const double vRotAxisMaxLimit0 = mathdef::MW_MAX_DOUBLE,
			const double vRotAxisMaxLimit1 = mathdef::MW_MAX_DOUBLE,
			const double vRotAxisMaxLimit2 = mathdef::MW_MAX_DOUBLE,
			const mw6axMachDef::AxisType _1stType = static_cast<mw6axMachDef::AxisType>(-1),	
			const mw6axMachDef::AxisType _2ndType = static_cast<mw6axMachDef::AxisType>(-1),	
			const mw6axMachDef::AxisType _3rdType = static_cast<mw6axMachDef::AxisType>(-1),	
			const mw5axMachDef::MachType machine5axKinematicType = static_cast<mw5axMachDef::MachType>(-1),
			const mw4axMachDef::MachType machine4axKinematicType = static_cast<mw4axMachDef::MachType>(-1),
			const cadcam::mwVector3d& sawDirection = cadcam::mwVector3d(),
			const mwMachDef::MachineDefinitionType type = mwMachDef::MILLING_MACHINE,
			const bool doValidations = true,
			const mwMachDef::mwMatrix4dPtr& workpieceTransformUpdated = MW_NULL,
			const mwMachDef::mwMatrix4dPtr& holderTransformUpdated = MW_NULL);
		//#############################################################################
	private:
		//#############################################################################
		//! Disables default constructor
		mwMachDefUtils();
		//#############################################################################
		//a checking class for safe conversion
		class mwCastingRevolvedChecker : public mwMachineVisitor
		{
		public:
			enum AxisTypes
			{
				mwCasting_3AXIS = 0,
				mwCasting_4AXIS = 1,
				mwCasting_5AXIS = 2,
				mwCasting_6AXIS = 3,
				mwCasting_6AXIS_CS = 4
			};
			mwCastingRevolvedChecker(AxisTypes axisTypes) 
				: m_AxisTypes(axisTypes)
			{

			}
			void Visit(const mwMachDef& /*visitor*/) const
			{
				throw mwPostException(mwPostException::ABSTARCT_FUNCTION_CALLED);
			}
			void Visit(const mw3axMachDef& /*visitor*/) const
			{
				if(m_AxisTypes != mwCasting_3AXIS)
					throw mwPostException(mwPostException::WRONG_METHOD_CALLED);
				//else do conversion
			}
			void Visit(const mw4axMachDef& /*visitor*/) const
			{
				if(m_AxisTypes != mwCasting_4AXIS)
					throw mwPostException(mwPostException::WRONG_METHOD_CALLED);
				//else do conversion
			}
			void Visit(const mw5axMachDef& /*visitor*/) const
			{
				if(m_AxisTypes != mwCasting_5AXIS)
					throw mwPostException(mwPostException::WRONG_METHOD_CALLED);
				//else do conversion
			}
			void Visit(const mw6axMachDef& /*visitor*/) const
			{
				if(m_AxisTypes != mwCasting_6AXIS)
					throw mwPostException(mwPostException::WRONG_METHOD_CALLED);
				//else do conversion
			}
			void Visit(const mw6axCSMachDef& /*visitor*/) const
			{
				if(m_AxisTypes != mwCasting_6AXIS_CS)
					throw mwPostException(mwPostException::WRONG_METHOD_CALLED);
				//else do conversion
			}
			//#############################################################################
		private:
			AxisTypes m_AxisTypes;
			//#############################################################################
		};// end class mwCastingRevolvedChecker
		//#############################################################################
	};//end class mwMachDefUtils
	//#############################################################################
}// end namespace post
//#############################################################################
#endif	//	MW_MWMACHDEFUTILS_HPP_
