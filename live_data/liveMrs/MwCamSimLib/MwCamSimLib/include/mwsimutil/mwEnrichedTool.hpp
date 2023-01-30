// (C) 2005-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWENRICHEDTOOL_HPP_
#define MW_MWENRICHEDTOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwMesh.hpp"
#include "mwTool.hpp"
#include "mwUnitsFactory.hpp"

#include <map>


namespace cadcam
{
	class MW_5AXUTIL_API mwEnrichedTool
	{
	public:
		enum toolState
		{
			TOOL_STATE_ON = 0,
			TOOL_STATE_OFF,
			TOOL_STATE_CW,
			TOOL_STATE_CCW
		};

		typedef misc::mwAutoPointer<const mwTool> mwToolPtr;
		typedef std::map<toolState, mwToolPtr> toolStateShapes;

		mwEnrichedTool();

		mwEnrichedTool(
			mwToolPtr coreTool,
			const misc::mwstring& name,
			const misc::mwstring& comment,
			const long& number,
			const double& profileTolerance);

		// Copy Ctor
		mwEnrichedTool(const mwEnrichedTool& toCopy);

		const mwEnrichedTool& operator=(const mwEnrichedTool& it);
		const bool operator==(const mwEnrichedTool& tc) const;
		const bool operator!=(const mwEnrichedTool& tc) const;

		void SetStates(const toolStateShapes& states);
		const toolStateShapes& GetStates() const;
		const mwToolPtr GetCoreTool(const toolState state) const;

		const misc::mwstring& GetName() const;
		void SetName(const misc::mwstring& toSet);

		const misc::mwstring& GetComment() const;
		void SetComment(const misc::mwstring& toSet);

		const long& GetNumber() const;
		void SetNumber(const long& toSet);

		// Used when generating the mesh for display and sometimes for collision checks.
		// Our recommendation is to use a formula like : 0.05 > Flute_Part_Diameter / 100 > 0.001 for
		// metric simulations.
		const double& GetProfileTolerance() const;
		void SetProfileTolerance(const double& toSet);

		void SetUnits(const measures::mwUnitsFactory::Units units);

		bool IsAdditive() const;
		void SetAdditiveFlag(const bool toSet);


		// deprecated
		const misc::mwAutoPointer<const mwTool> GetCoreTool() const;

		enum toolPartType
		{
			CUTTING = 0,
			NON_CUTTING,
			ARBOR,
			HOLDER
		};

		/// Get the tool's "spindle off" mode meshes
		typedef misc::mwAutoPointer<cadcam::mwTMesh<float>> Mesh;
		typedef std::map<toolPartType, Mesh> ToolPartsMeshes;

		/// tool parts comparator predicate
		struct AreEqalToolPartsMeshes
		{
			template <typename Pair>
			bool operator()(Pair const& left, Pair const& right) const
			{
				if (left.first != right.first)
					return false;
				if (left.second == right.second)
					return true;  // equal as pointer
				return (*left.second == *right.second);  // equal as mesh
			}
		};

		mwEnrichedTool(
			misc::mwAutoPointer<const mwTool> coreTool,
			const misc::mwstring& name,
			const misc::mwstring& comment,
			const long& number,
			const double& profileTolerance,
			const ToolPartsMeshes& spindleOffMeshes);


		// deprecated
		const ToolPartsMeshes& GetSpindleOffMeshes() const;

		/// Set the tool's "spindle off" mode meshes
		void SetSpindleOffMeshes(const ToolPartsMeshes& toSet);

	private:
		void Initialize(
			misc::mwAutoPointer<const mwTool> coreTool,
			const misc::mwstring& name,
			const misc::mwstring& comment,
			const long& number,
			const double& profileTolerance);

		misc::mwstring m_name;
		misc::mwstring m_comment;
		long m_number;
		double m_profileTolerance;
		bool m_additive;

#pragma warning(push)
#pragma warning(disable : 4251)
		toolStateShapes m_toolStates;
		// deprecated
		ToolPartsMeshes m_spindleOffMeshes;
#pragma warning(pop)
	};
}  // namespace cadcam
#endif  //	MW_MWENRICHEDTOOL_HPP_