// (C) 2019-2021 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWROBTYPES_HPP_
#define MW_MWROBTYPES_HPP_
#include "mwDllImpExpDef.hpp"
#include <vector>
#include "mwStringOps.hpp"
#include "mwStringConversions.hpp"
#include "mwAutoPointer.hpp"
#include "mwCNCMove.hpp"
//#############################################################################
namespace post
{
class MW_5AXUTIL_API mwRobTypes
{
public:
	using Weights = std::vector<double>;
	using ID = misc::mwstring;
	using AxisIDs = std::vector<misc::mwstring>;
	using AxisData = std::pair<misc::mwstring, double>;
	using AxisLimits = std::vector<AxisData>;
	using AxisWeights = std::vector<AxisData>;
	using AxisValues = std::vector<AxisData>;
	using AvoidanceZones = std::vector<AxisData>;
	using CustomCoordSysInfo = std::pair<misc::mwstring, bool>;

	enum axisType
	{
		MW_POST_TR_AXIS = 0,
		MW_POST_ROT_AXIS = 1,
	};

	enum Types
	{
		APPROACH_MOVE,
		ENTRY_MACRO_MOVE,
		CONNECTION_NOT_CLEAREANCE_ARREA_MOVE,
		CONNECTION_CLEAREANCE_ARREA_MOVE,
		EXIT_MACRO_MOVE,
		RETRACT_MOVE,
		CONTOUR_MOVE,
		REWIND_RETRACT_MOVE,
		REWIND_MOVE,
		REWIND_APPROACH_MOVE,
		DWELL_MOVE,
		TOOL_CHANGE_MOVE,
		KEEP_THIS_LAST_TYPES
	};

	struct TypedMove
	{
		misc::mwAutoPointer<cadcam::mwCNCMove> m_move;
		Types m_type;
		bool m_contour;
		unsigned int m_filterIndex;
		misc::mwAutoPointer<TypedMove> m_duplicatedMove;

		TypedMove()
			: m_move(MW_NULL),
			  m_type(Types::KEEP_THIS_LAST_TYPES),
			  m_contour(false),
			  m_filterIndex(0),
			  m_duplicatedMove(MW_NULL){};
		TypedMove(
			misc::mwAutoPointer<cadcam::mwCNCMove> move,
			Types type,
			bool contour,
			unsigned int filterIndex)
			: m_move(move), m_type(type), m_contour(contour), m_filterIndex(filterIndex){};
	};

	class AxisInfo
	{
	private:
		misc::mwstring m_id;
		axisType m_type;
		double m_value;

	public:
		AxisInfo(const misc::mwstring& id, const axisType& type, const double& value)
			: m_id(id), m_type(type), m_value(value){};

		const misc::mwstring& GetAxisID() const
		{
			return m_id;
		}

		void SetAxisID(const misc::mwstring& value)
		{
			m_id = value;
		}

		const axisType& GetAxisType() const
		{
			return m_type;
		}

		void SetAxisType(const axisType& value)
		{
			m_type = value;
		}

		const double& GetAxisValue() const
		{
			return m_value;
		}

		void SetAxisValue(const double& value)
		{
			m_value = value;
		}

		bool operator==(const AxisInfo& obj2) const
		{
			if (m_id == obj2.m_id && m_value == obj2.m_value && m_type == obj2.m_type)
				return true;
			else
				return false;
		}

		const AxisInfo& operator=(const AxisInfo& toCopy)
		{
			if (&toCopy == this)
				return *this;

			m_id = toCopy.m_id;
			m_type = toCopy.m_type;
			m_value = toCopy.m_value;

			return *this;
		}
	};

	using TypedMoves = std::vector<TypedMove>;
};

}  // end namespace post
#endif	//	MW_MWROBTYPES_HPP_
