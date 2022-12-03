// (C) 2010-2021 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWGENERICPOSTDEF_HPP_
#define MW_MWGENERICPOSTDEF_HPP_

#include "mwMeasurable.hpp"
#include "mwMxpDllImpExpDef.hpp"
#include "mwMXPParam.hpp"
#include "mw5axControlDef.hpp"
#include "mwPostComponentsDefinitions.hpp"

#pragma warning(push)
#pragma warning(disable: 4251 4275)

class MWMXP_API GenericAxis
{
public:
	enum AxisType
	{
		GENERIC = 0,
		TRANSLATION,
		ROTATION
	};
	enum AxisPos
	{
		HEAD = 0,
		TABLE
	};
	enum AxisOrder
	{
		FIRST = 0,
		SECOND,
		THIRD  
	};

	virtual misc::mwAutoPointer<GenericAxis> Clone() const = 0;

	const cadcam::mwPoint3d& GetDirection() const
	{
		return m_direction;
	}
	void SetDirection(const cadcam::mwPoint3d& direction)
	{
		m_direction = direction;
	}
	const double GetMinLimit() const
	{
		return m_minLimit;
	}
	void SetMinLimit(const double minLimit)
	{
		m_minLimit = minLimit;
	}
	const double GetMaxLimit() const
	{
		return m_maxLimit;
	}
	void SetMaxLimit(const double maxLimit)
	{
		m_maxLimit = maxLimit;
	}
	const AxisPos& GetAxisPos() const
	{
		return m_axisPos;
	}
	void SetAxisPos(const AxisPos& axisPos)
	{
		m_axisPos = axisPos;
	}
	const AxisType& GetAxisType() const
	{
		return m_axisType;
	}
	void SetAxisType(const AxisType& axisType)
	{
		m_axisType = axisType;
	}
	const misc::mwstring& GetAxisName() const
	{
		return m_axisName;
	}
	void SetAxisName(const misc::mwstring& axisName)
	{
		m_axisName = axisName;
	}
	const AxisOrder& GetAxisOrder() const
	{
		return m_axisOrder;
	}
	void SetAxisOrder(const AxisOrder& axisOrder)
	{
		m_axisOrder = axisOrder;
	}
	virtual ~GenericAxis() = 0;
	
protected:

	cadcam::mwPoint3d m_direction;
	double m_minLimit;
	double m_maxLimit;
	misc::mwstring m_axisName;
	AxisPos m_axisPos;
	AxisType m_axisType;
	AxisOrder m_axisOrder;
	
	GenericAxis(
		const cadcam::mwPoint3d& direction,
		const double minLimit,
		const double maxLimit,
		const misc::mwstring& axisName,
		const AxisPos axisPos,
		const AxisOrder axisOrder)
			: m_direction(direction) 
			, m_minLimit(minLimit)
			, m_maxLimit(maxLimit)
			, m_axisName(axisName)
			, m_axisPos(axisPos)
			, m_axisOrder(axisOrder)
	{
		m_axisType = GENERIC;
	}
};

class MWMXP_API RotationAxis : public GenericAxis
{
public:

	RotationAxis(
		const cadcam::mwPoint3d& direction,
		const cadcam::mwPoint3d& basePoint,
		const double minLimit,
		const double maxLimit,
		const misc::mwstring& axisName,
		const AxisPos axisPos,
		const AxisOrder axisOrder)
			: GenericAxis(direction, minLimit, maxLimit, axisName, axisPos, axisOrder)
			, m_basePoint(basePoint)
	{
		m_axisType = ROTATION;
	}
	const cadcam::mwPoint3d& GetBasePoint() const
	{
		return m_basePoint;
	}
	void SetBasePoint(const cadcam::mwPoint3d& basePoint)
	{
		m_basePoint = basePoint;
	}
	virtual misc::mwAutoPointer<GenericAxis> Clone() const
	{
		misc::mwAutoPointer<RotationAxis> tempOBJ= new RotationAxis (GetDirection(),m_basePoint,GetMinLimit(),GetMaxLimit(),GetAxisName(),GetAxisPos(),GetAxisOrder());
		tempOBJ->m_axisType= m_axisType;
		misc::mwAutoPointer<GenericAxis> retGaxis = tempOBJ;			
		return retGaxis;
	} 
protected:
	cadcam::mwPoint3d m_basePoint;
};

class MWMXP_API TranslationAxis : public GenericAxis
{
public:
	TranslationAxis(
		const cadcam::mwPoint3d& direction,
		const double minLimit,
		const double maxLimit,
		const misc::mwstring& axisName,
		const AxisPos axisPos,
		const AxisOrder axisOrder)
			: GenericAxis(direction, minLimit, maxLimit, axisName, axisPos, axisOrder)
	{
		m_axisType = TRANSLATION;
	}
	virtual misc::mwAutoPointer<GenericAxis> Clone() const
	{
		misc::mwAutoPointer<TranslationAxis> tempOBJ= new TranslationAxis (GetDirection(),GetMinLimit(),GetMaxLimit(),GetAxisName(),GetAxisPos(),GetAxisOrder());
		tempOBJ->m_axisType= m_axisType;
		misc::mwAutoPointer<GenericAxis> retGaxis = tempOBJ;			
		return retGaxis;
	} 
protected:
	
};

//! container class for post processor
/*
	contains a post definition for xml files
*/

class MWMXP_API mwGenericPostDef : public measures::mwMeasurable
{
public:
	
	enum DetectionMode
	{
		AUTODETECT_FULL = 0,
		AUTODETECT_SEMIAUTOMATIC = 1,
		MANUAL_MODE = 2,
		UNKNOWN = 3
	};
	
	enum MachineDefinitionType
	{
		UNDEFINED = 0,
		MILLING_MACHINE = 1,
		TURNING_MACHINE = 2,
		CONTOUR_MACHINE = 3,
		LASER_MACHINE = 4,
		KNIFE_GRINDING_MACHINE = 5,
		ROBOTIC = 6,
		CONSTANT_TRANSLATION_MACHINE = 7
	};
	
	typedef misc::mwAutoPointer<GenericAxis>				GenericAxisPtr;
	typedef std::vector<GenericAxisPtr>						GenericAxisPtrVect;
	typedef post::mwSpindles								Spindles;
	typedef misc::mwAutoPointer<cadcam::mwPoint3d>			point3dPtr;
	typedef std::vector<std::pair<misc::mwstring, misc::mwstring>>	stringPairVect;
	typedef misc::mwAutoPointer<stringPairVect>				stringPairVectPtr;

	mwGenericPostDef();

	mwGenericPostDef(const mwGenericPostDef& toCopy);
	
	const mwGenericPostDef& operator = (const mwGenericPostDef &toCopy);

	const bool operator == (const mwGenericPostDef& toCompare) const;
	
	virtual ~mwGenericPostDef();

	misc::mwAutoPointer<mwGenericPostDef>  Clone() const;
	
	void AddAxis(const GenericAxisPtr& axis);
	
	const cadcam::mwPoint3d& GetSpindle() const;
	
	void SetSpindle(const cadcam::mwPoint3d& spindle);
	
	const misc::mwstring& GetID() const;
    
	void SetID(const misc::mwstring& toSet);
	
	const float GetVersion() const; // xml.machine_definition.version
	
	void SetVersion(const float version); // xml.machine_definition.version

	const float GetPostVersion() const; // xml.machine_definition.post_definition.version

	void SetPostVersion(const float version); // xml.machine_definition.post_definition.version
	
	const DetectionMode GetDetectionMode() const;
	
	void SetDetectionMode(const DetectionMode detectionMode);
	
	const GenericAxisPtrVect& GetAxis() const;
	
	void SetAxis(const GenericAxisPtrVect& axis);
	
	void Validate() const;
	
	void SetAxisNames(const std::vector<misc::mwstring>& axisNames);
	
	const std::vector<misc::mwstring> GetAxisNames() const;
	
	void SetFeedRate(const double feedRate);
	
	const double GetFeedRate() const;
	
	void SetRapidRate(const double rapidRate);
	
	const double GetRapidRate() const;
	
	void SetToolChangeTime(const double toolChangeTime);
	
	const double GetToolChangeTime() const;
	
	const bool IsMachineDynamicsPresent() const;
	
	void SetMachineDynamicsPresent(const bool machineDynamicsExist);
	
	const misc::mwstring GetToolName() const;
	
	void SetToolName(const misc::mwstring toolName);
	
	const misc::mwstring GetWorkpieceName() const;
	
	void SetWorkpieceName(const misc::mwstring workpieceName);
	
	const misc::mwstring GetGenericWorkpiece() const;
	
	void SetGenericWorkpiece(const misc::mwstring workpiece);
	
	const Spindles& GetSpindlesDir() const;
	
	void SetSpindlesDir(const Spindles& spindlesDir);

	const post::mwMatrix4dMap& GetMatrixMap() const;

	void SetMatrixMap(const post::mwMatrix4dMap& matrixMap);
	
	void AddSpindleDir(const misc::mwstring& name, const cadcam::mwPoint3d& spindle);
	
	void AddSpindleDir(
		const misc::mwstring& name,
		const cadcam::mwPoint3d& orientation,
		const misc::mwAutoPointer<cadcam::mwPoint3d>& directionPtr);
	
	const bool IsPostDefinitionPresent() const;
	
	void SetPostDefinitionPresent(const bool postDefinitionExist);
	
	const misc::mwstring GetOriginalPostSettingsID() const;
	
	void SetOriginalPostSettingsID(const misc::mwstring& originalId);
	
	const point3dPtr& GetArrowDirectionPtr() const;
	
	void SetArrowDirectionPtr(const point3dPtr& arrowDirectionPtr);
	
	const MachineDefinitionType GetMachineDefinitionType() const;
	
	void SetMachineDefinitionType(const MachineDefinitionType type);
	
	const post::mwMXPParamPtr& GetMxpParamPtr() const;
	
	void SetMxpParamPtr(const post::mwMXPParamPtr& mxpParamPtr);

	const post::mw5axControlDef::mw5axControlDefPtr& Get5AxControlDefPtr() const;

	void Set5AxControlDefPtr(const post::mw5axControlDef::mw5axControlDefPtr& mxpParamPtr);

	void SetAdditionalFixedAxesPtr(const post::AdditionalFixedAxesPtr& additionalFixedAxesPtr);

	const post::AdditionalFixedAxesPtr& GetAdditionalFixedAxesPtr() const;

	const misc::mwstring& GetMachineName() const;
	
	void SetMachineName(const misc::mwstring& machineName);

	void SetMountingPairsPtr(const stringPairVectPtr& mountingPairsPtr);

	const stringPairVectPtr& GetMountingPairsPtr() const;

protected:
	
	void Scale(const Units units, const double& scaleFactor);
	
private:
	
	misc::mwstring					m_id;
	misc::mwstring					m_originalId;
	GenericAxisPtrVect				m_axis;
	cadcam::mwPoint3d				m_spindle;
	float							m_version;
	float							m_postVersion;
	DetectionMode					m_detectionMode;
	double							m_feedRate;
	double							m_rapidRate;
	double							m_toolChangeTime;
	bool							m_machineDynamicsExist;
	misc::mwstring					m_toolName;
	misc::mwstring					m_workpieceName;
	misc::mwstring					m_genericWorkpiece;
	std::vector<misc::mwstring>		m_axisNames;
	Spindles						m_spindlesDir;
	bool							m_postDefinitionExist;
	point3dPtr						m_arrowDirectionPtr;
	MachineDefinitionType			m_type;
	post::mwMXPParamPtr				m_mxpParamPtr;
	post::mw5axControlDef::mw5axControlDefPtr	   m_5axControlDefPtr;
	post::mwMatrix4dMap				m_matrixMap;
	post::AdditionalFixedAxesPtr	m_additionalFixedAxesPtr;
	misc::mwstring					m_machineName;
	stringPairVectPtr				m_mountingPairsPtr;

	void Copy(const mwGenericPostDef& toCopy);
};
#pragma warning(pop)
#endif
