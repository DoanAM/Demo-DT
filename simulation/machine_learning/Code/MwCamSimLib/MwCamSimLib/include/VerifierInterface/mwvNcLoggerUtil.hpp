// (C) 2011-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVNCLOGGERUTIL_HPP_
#define MW_MWVNCLOGGERUTIL_HPP_

#include "mwVerifierDllDefinition.hpp"
#include "mwVerifierNestedEnums.hpp"
#include "mwvUtilDefines.hpp"

#include <map>
#include <mwDllImpExpDef.hpp>
#include <mwString.hpp>
#include <mwWarningPragmas.hpp>

namespace misc
{
class mwOFStream;
}

namespace cadcam
{
template <typename T>
class mw2dContour;
class mwTool;
}  // namespace cadcam

namespace VerifierUtil
{
class mwSubFilenameGenerator;

/// This class can be used to create verifier-specific NC commands.
///
/// For a reference to the NC format see
/// [the&nbsp;developer&nbsp;guide](doc/Developer_guide/Cutting_Additive_Simulation/NC-File_Specification/_main_.md).
class MW_VERIFIER_API mwvNcLoggerUtil
{
public:
	static void PrintStockCube(
		std::basic_ostream<wchar_t>& fileStrm,
		const cadcam::mwTPoint3d<float>& corner1,
		const cadcam::mwTPoint3d<float>& corner2);

	static void PrintStockEmptyCube(
		std::basic_ostream<wchar_t>& fileStrm,
		const cadcam::mwTPoint3d<float>& corner1,
		const cadcam::mwTPoint3d<float>& corner2);

	static void PrintStockCylinder(
		std::basic_ostream<wchar_t>& fileStrm,
		const float fHeight,
		const float fRadius,
		const cadcam::mwTPoint3d<float>& position,
		const cadcam::mwTPoint3d<float>& axis);

	static void PrintSetStockMesh(
		std::basic_ostream<wchar_t>& fileStrm,
		const misc::mwstring& sInputStlFileName);  // to be deprecated

	template <typename T>
	static void PrintSetStockMesh(
		std::basic_ostream<wchar_t>& fileStrm,
		const misc::mwstring dir,
		const misc::mwAutoPointer<cadcam::mwTMesh<T>> p_mesh);

	static void PrintSetStockRevolved(
		std::basic_ostream<wchar_t>& fileStrm,
		const VerifierUtil::StockSpindleAxis axis,
		const cadcam::mw2dContour<float>& profile);

	MW_WARNING_PUSH
	MW_WARNING_DISABLE_DEPRECATED
	MW_DEPRECATED("Please use StockSpindleAxis instead.")
	static void PrintSetStockRevolved(
		std::basic_ostream<wchar_t>& fileStrm,
		const VerifierUtil::TurningRotaryAxis axis,
		const cadcam::mw2dContour<float>& profile);
	MW_WARNING_POP

	static void PrintSetTargetMesh(
		std::basic_ostream<wchar_t>& fileStrm, const misc::mwstring& sTargetStlFileName);
	static void PrintSetTargetMesh(
		std::basic_ostream<wchar_t>& fileStrm,
		const misc::mwstring& sTargetStlFileName,
		const float gougeOffset,
		const float excessOffset,
		const float red,
		const float green,
		const float blue,
		const float alpha);

	template <typename T>
	static void PrintSetTargetMesh(
		std::basic_ostream<wchar_t>& fileStrm,
		const misc::mwstring dir,
		const misc::mwAutoPointer<cadcam::mwTMesh<T>> p_mesh);

	template <typename T>
	static void PrintSetTargetMesh(
		std::basic_ostream<wchar_t>& fileStrm,
		const misc::mwstring dir,
		const misc::mwAutoPointer<cadcam::mwTMesh<T>> p_mesh,
		const T gougeOffset,
		const T excessOffset,
		const T red,
		const T green,
		const T blue,
		const T alpha);

	static void PrintMove(
		std::basic_ostream<wchar_t>& fileStrm,
		const Frame& start_frame,
		const Frame& end_frame,
		const Frame& old_end_frame,
		const bool rapid,
		bool& forceMove,
		const float moveID = 0.0f);

	static void PrintThreadCut(
		std::basic_ostream<wchar_t>& fileStrm,
		const Frame& start_frame,
		const Frame& end_frame,
		const float startSpindleAngle,
		const float endSpindleAngle,
		const Frame& old_end_frame,
		const float oldSpindleAngle,
		bool& forceMove,
		const float moveID = 0.0f);

	static void PrintThreadCut(
		std::basic_ostream<wchar_t>& fileStrm,
		const Frame& start_frame,
		const Frame& end_frame,
		const Frame& old_end_frame,
		const float pitch,
		const float startOffset,
		const bool rapid,
		bool& forceMove,
		const float moveID = 0.0f);

	static void PrintThreadCut_CircleApproximation(
		std::basic_ostream<wchar_t>& fileStrm,
		const Frame& start_frame,
		const Frame& end_frame,
		const Frame& old_end_frame,
		const float pitch,
		const float startOffset,
		const bool rapid,
		bool& forceMove,
		const float moveID = 0.0f);

	static void PrintCircularCut(
		std::basic_ostream<wchar_t>& fileStrm,
		const Frame& start_frame,
		const Frame& end_frame,
		const Frame& old_end_frame,
		const cadcam::mwTPoint3d<float>& circleCenter,
		const cadcam::mwTPoint3d<float>& circlePlaneNormal,
		const bool rapid,
		bool& forceMove,
		const float moveID = 0.0f);

	static void PrintCircularSweepCut(
		std::basic_ostream<wchar_t>& fileStrm,
		const Frame& start_frame,
		const float sweepAngle,
		const float heightChange,
		const float radiusChange,
		const Frame& old_end_frame,
		const cadcam::mwTPoint3d<float>& circleCenter,
		const cadcam::mwTPoint3d<float>& circlePlaneNormal,
		const bool rapid,
		bool& forceMove,
		const float moveID = 0.0f);

	static void PrintCombine(std::basic_ostream<wchar_t>& fileStrm, const misc::mwstring& stlFile);
	static void PrintSubtract(std::basic_ostream<wchar_t>& fileStrm, const misc::mwstring& stlFile);
	static void PrintIntersect(
		std::basic_ostream<wchar_t>& fileStrm, const misc::mwstring& stlFile);

	template <typename T>
	static void PrintMove(
		std::basic_ostream<wchar_t>& fileStrm,
		const cadcam::mw3dPoint<T>& endTip,
		const cadcam::mw3dPoint<T>& endAxis,
		const T endRoll,
		const bool rapid,
		const bool isMove,
		const float moveID = 0.0f);

	static void PrintTurningRotaryAxis(
		std::basic_ostream<wchar_t>& fileStrm, const VerifierUtil::StockSpindleAxis newAxis);

	static void PrintTurningRotaryAxis(
		std::basic_ostream<wchar_t>& fileStrm,
		const VerifierUtil::StockSpindleAxis newAxis,
		const float3d& position);

	MW_WARNING_PUSH
	MW_WARNING_DISABLE_DEPRECATED
	MW_DEPRECATED("Please use StockSpindleAxis instead!")
	static void PrintTurningRotaryAxis(
		std::basic_ostream<wchar_t>& fileStrm, const VerifierUtil::TurningRotaryAxis newAxis);

	MW_DEPRECATED("Please use StockSpindleAxis instead!")
	static void PrintTurningRotaryAxis(
		std::basic_ostream<wchar_t>& fileStrm,
		const VerifierUtil::TurningRotaryAxis newAxis,
		const float3d& position);
	MW_WARNING_POP

	static void PrintTurningSpindleMode(
		std::basic_ostream<wchar_t>& fileStrm, const VerifierUtil::StockSpindleMode spindleMode);

	MW_WARNING_PUSH
	MW_WARNING_DISABLE_DEPRECATED
	MW_DEPRECATED("Please use StockSpindleMode instead!")
	static void PrintTurningSpindleMode(
		std::basic_ostream<wchar_t>& fileStrm, const VerifierUtil::TurningSpindleMode spindleMode);
	MW_WARNING_POP

	template <typename T>
	static misc::mwstring SaveOrFindMesh(
		const misc::mwstring& filename, const cadcam::mwTMesh<T>& mesh);

	enum ToolBehavior
	{
		CUTTING,
		ADDING,
		PAINTING,
	};

	/// Note: only mwRevolvedTool, mwExtrudedTool, mwGenericTool, mwWireTool and their derived
	/// classes are supported. That means mwSawingTool and mwOpticDiamondTool are currently not
	/// supported.
	///
	/// ToolBehavior is currently only supported for mwRevolvedTool, mwExtrudedTool and
	/// mwGenericTool and their derived classes. That means out of the supported tools it is not
	/// supported for mwWireTool, which will use the CUTTING behavior even if another behavior is
	/// given.
	static void PrintTool(
		std::basic_ostream<wchar_t>& stream,
		const cadcam::mwTool& tool,
		ToolBehavior toolBehavior = CUTTING);
	static void PrintTool(
		std::basic_ostream<wchar_t>& stream,
		const cadcam::mwTool& tool,
		mwSubFilenameGenerator& generator,
		ToolBehavior toolBehavior = CUTTING);
};

/// This class should be used to define where additional files, like tool meshes, should be placed.
class MW_VERIFIER_API mwSubFilenameGenerator
{
public:
	mwSubFilenameGenerator(const misc::mwstring& baseFilename, const bool inTestMode);
	misc::mwstring Generate(const misc::mwstring& subname, const misc::mwstring& extension);

	const std::vector<cadcam::mwdMesh::Ptr> GetMeshes() { return m_meshes; }
	void AddMesh(const cadcam::mwdMesh::Ptr& mesh) { m_meshes.push_back(mesh); }
	bool InTestMode() { return m_inTestMode; }

private:
	misc::mwstring m_baseFilename;
	std::map<misc::mwstring, int> m_subnameCounts;
	bool m_inTestMode;
	std::vector<cadcam::mwdMesh::Ptr> m_meshes;
};

}  // namespace VerifierUtil
#endif  //	MW_MWVNCLOGGERUTIL_HPP_
