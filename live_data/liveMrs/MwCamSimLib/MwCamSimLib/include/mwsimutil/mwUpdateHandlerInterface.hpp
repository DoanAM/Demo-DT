// (C) 2009-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWUPDATEHANDLERINTERFACE_HPP_
#define MW_MWUPDATEHANDLERINTERFACE_HPP_
#include "mwAutoPointer.hpp"

namespace cadcam
{
class mwToolpathLayered;
}

namespace interact
{
class MW_5AXUTIL_API mwUpdateHandlerInterface
{
public:
	typedef misc::mwAutoPointer<mwUpdateHandlerInterface> Ptr;

	enum WarningId
	{
		WID_RAMP_SHAPE_CHANGED_BECAUSE_OF_COLLISION = (1 << 0), /// User-requested ramp type didn't fit, system had to fall-back to other ramp type
		WID_POCKET_WAS_REMOVED_BECAUSE_RAMP_NOT_POSSIBLE = (1 << 1), /// When only certain ramp types are selected and tool is non-center-cutting, we need to remove pockets if ramp can't be built
		WID_HELICAL_RAMP_MAX_DIAMETER_WAS_ADJUSTED_TO_95_PERCENT = (1 << 2), /// Max helical ramp diameter was adjusted to 95%
		WID_SPIRALIZER_LEAVES_UNCUTS = (1 << 3), /// Spiralized toolpath would likely leave uncut material for current combination of geometries and params
		WID_UNDERCUTS_TOO_LONG_GAPS_ALONG_CUT = (1 << 4), /// There was too large gap along the cut in Constant-Z Undercuts
		WID_GOUGE_CHECK_CHANGED_TOOLPATH = (1 << 5), /// Gouge checking changed the toolpath
		WID_AR_VERTICAL_ARC_NOT_FIT = (1 << 6), /// Unable to fit vertical arc in Adaptive Roughing
		WID_ENGRAVE_TOOL_DOES_NOT_REACH_MAX_DEPTH = (1 << 7), /// Wireframe Engraving failed to reach maximum depth with specified geometries/params
		WID_UNREMOVABLE_STOCK_PILLAR = (1 << 8), /// Stock pillar has such a shape that we can't remove it with regular helical pillar removal pattern 
		WID_LEAD_MOVE_CAN_NOT_START_FROM_SAFE_AREA = (1 << 9), // Lead move should start from safe area
		WID_PROFILE_PASS_HAS_NO_SAFE_AREA = (1 << 10) // Roughing area collapsed and we should filter out profile pass as well
	};

	mwUpdateHandlerInterface(){};

	struct ProgressDescription
	{
		typedef unsigned int objectID;
		typedef unsigned int operationID;

		ProgressDescription()
			: m_ObjectID(0)
			, m_TotalObjects(0)
			, m_CurrentObject(0)
			, m_OperationID(0)
			, m_Percentage(0)
		{
		}

		objectID		m_ObjectID;			// The type of the objects in work
		size_t			m_TotalObjects;		// The total number of objects in work
		size_t			m_CurrentObject;	// The current object in work
		operationID		m_OperationID;		// The type of the operation
		int				m_Percentage;		// Specifies how much of the operation was accomplished (in percent)
	};

	struct OverallProgressDescription
	{
		typedef unsigned int overallOperationID;

		OverallProgressDescription()
			: m_Percentage(0)
			, m_OverallOperationID(0)
		{
		}

		double m_Percentage;							//specifies how much of the overall process was accomplished
		overallOperationID m_OverallOperationID;		// The type of the overall operation
	};

	virtual void SetProgress(const ProgressDescription& rProgress, const bool bIsCollControl) const = 0;
	virtual void SetProgressOverall(const OverallProgressDescription& rOverAllProgress) const = 0;
	virtual void SetProgressOverall(double percentage) const = 0;
	virtual const bool IsCanceled() const = 0;
	virtual void PushWarning(const WarningId) const
	{
	}
	virtual void PushCurrentToolpath(const std::vector<cadcam::mwToolpathLayered>&) const
	{
	}
	virtual ~mwUpdateHandlerInterface()
	{
	}
};

class MW_5AXUTIL_API mwUpdateHandlerGeneric : public mwUpdateHandlerInterface
{
public:
	typedef misc::mwAutoPointer<mwUpdateHandlerGeneric> Ptr;

	mwUpdateHandlerGeneric()
	{
	}
	virtual void SetProgress(const ProgressDescription&, const bool /*bIsCollControl*/) const
	{
	}
	virtual void SetProgressOverall(const OverallProgressDescription&) const
	{
	}
	virtual void SetProgressOverall(double /*percentage*/) const
	{
	}
	virtual const bool IsCanceled() const
	{
		return false;
	}
	virtual ~mwUpdateHandlerGeneric() {};
};
}  // namespace interact
#endif	//	MW_MWUPDATEHANDLERINTERFACE_HPP_
