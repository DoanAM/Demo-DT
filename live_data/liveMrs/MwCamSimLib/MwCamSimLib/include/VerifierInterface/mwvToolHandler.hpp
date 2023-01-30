// (C) 2014-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVTOOLHANDLER_HPP_
#define MW_MWVTOOLHANDLER_HPP_
#include "mwvColor.hpp"
#include "mwvMeshHandler.hpp"

#include <mwTool.hpp>

namespace VerifierUtil
{
class MW_VERIFIER_API mwvToolHandler
{
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	cadcam::mwConstToolPtr m_tool;

#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	MATH::Frame<float> m_position;

#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<mwvMeshHandler> m_cuttingPart;

#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<mwvMeshHandler> m_nonCuttingPart;

#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<mwvMeshHandler> m_arborPart;

#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<mwvMeshHandler> m_holderPart;

	mwvColor m_cuttingColor;
	mwvColor m_nonCuttingColor;
	mwvColor m_arborColor;
	mwvColor m_holderColor;

public:
	/// Creates a toolhandler based on the mwTool
	///
	/// Creates a toolhandler based on the mwTool and the start position of the tool.
	/// @param [in] tool the basic tool
	/// @param [in] position the first position
	mwvToolHandler(
		cadcam::mwConstToolPtr tool, const MATH::Frame<float>& position = MATH::Frame<float>());

	/// Sets or replaces the basic tool
	///
	/// Sets or replaces the basic tool taking the colors of the previous tool.
	void SetTool(cadcam::mwConstToolPtr tool);

	cadcam::mwConstToolPtr GetTool() const { return m_tool; }

	void SetPosition(const MATH::Frame<float>& position) { m_position = position; }

	const MATH::Frame<float>& GetPosition() { return m_position; }

	const misc::mwAutoPointer<mwvMeshHandler> GetCutting();
	const misc::mwAutoPointer<mwvMeshHandler> GetNonCutting();
	const misc::mwAutoPointer<mwvMeshHandler> GetArbor();
	const misc::mwAutoPointer<mwvMeshHandler> GetHolder();

	void SetCuttingColor(const mwvColor& color);
	const mwvColor& GetCuttingColor() { return m_cuttingColor; }

	void SetNonCuttingColor(const mwvColor& color);
	const mwvColor& GetNonCuttingColor() { return m_nonCuttingColor; }

	void SetArborColor(const mwvColor& color);
	const mwvColor& GetArborColor() { return m_arborColor; }

	void SetHolderColor(const mwvColor& color);
	const mwvColor& GetHolderColor() { return m_holderColor; }
};
}  // namespace VerifierUtil
#endif  //	MW_MWVTOOLHANDLER_HPP_
