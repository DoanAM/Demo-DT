// (C) 2014-2021 by ModuleWorks GmbH
// Owner: CutSim

/// @file
/// @warning EXPERIMENTAL, NOT A STABLE INTERFACE YET

#ifndef MW_MWVTOOLMANAGER_HPP_
#define MW_MWVTOOLMANAGER_HPP_

#include "mwMachSimVerifier.hpp"
#include "mwvUtilDefines.hpp"

#include <map>
#include <vector>

namespace VerifierUtil
{
class MW_VERIFIER_API mwvToolManager
{
public:
	/// Initializes the manager with a list of verifiers
	///
	/// Every instance has its own current tool and is drawn at the same time.
	///
	/// This class is automatically updated through a callback, whenever any of the given verifiers
	/// performs a cut. Due to internal locking is safe to draw while the verifier simulates in a
	/// different thread.
	///
	/// @param [in] verifierList every verifier you want the manager to handle
	mwvToolManager(const std::vector<mwMachSimVerifier*>& verifierList);
	~mwvToolManager();

	/// Updates the current tools of all verifier instances.
	void Update();

	/// Updates the current tool
	///
	/// Updates the current tool of the given verifier instance.
	/// @param [in] pVerifier the verifier you want to update
	void Update(mwMachSimVerifier* const pVerifier);

	/// Draws the current tools
	///
	/// Draws the current tools of all verifier instances considering the given tool parts.
	/// @param [in] toolPartSelector the selected tool parts
	void Draw(
		const cadcam::mwToolPartSelector& toolPartSelector = cadcam::mwToolPartSelector()) const;

	/// Draws the given toolHandler
	///
	/// Draws the given toolHandler considering the given tool parts.
	/// @param [in] pVerifier the verifier of the tool you want to draw
	/// @param [in] toolPartSelector the selected tool parts
	void Draw(
		mwMachSimVerifier* const pVerifier,
		const cadcam::mwToolPartSelector& toolPartSelector = cadcam::mwToolPartSelector()) const;

	/// Set new tool colors
	///
	/// Set new tool colors to all verifier instances.
	/// @param [in] EdgeCol       cutting color
	/// @param [in] NCEdgeCol     nonCutting color
	/// @param [in] ArborCol      arbor color
	/// @param [in] ToolHolderCol holder color
	/// @param [in] alpha         the alpha of all colors
	void SetToolColor(
		const float3d& EdgeCol,
		const float3d& NCEdgeCol,
		const float3d& ArborCol,
		const float3d& ToolHolderCol,
		float alpha);

	/// Set new tool colors
	///
	/// Set new tool colors to the given verifier instance.
	/// @param [in] pVerifier the verifier you want to set the tool color for
	/// @param [in] EdgeCol       cutting color
	/// @param [in] NCEdgeCol     nonCutting color
	/// @param [in] ArborCol      arbor color
	/// @param [in] ToolHolderCol holder color
	/// @param [in] alpha         the alpha of all colors
	void SetToolColor(
		mwMachSimVerifier* const pVerifier,
		const float3d& EdgeCol,
		const float3d& NCEdgeCol,
		const float3d& ArborCol,
		const float3d& ToolHolderCol,
		float alpha);

private:
	struct Impl;
	Impl* m_impl;
};
}  // namespace VerifierUtil
#endif  //	MW_MWVTOOLMANAGER_HPP_
