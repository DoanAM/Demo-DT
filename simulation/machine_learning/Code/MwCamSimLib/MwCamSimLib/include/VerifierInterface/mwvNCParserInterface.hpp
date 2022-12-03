// (C) 2017-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVNCPARSERINTERFACE_HPP_
#define MW_MWVNCPARSERINTERFACE_HPP_
#include "mwVerifierDllDefinition.hpp"
#include "mwVerifierMoves.hpp"
#include "mwVerifierNestedClasses.hpp"
#include "mwvInitStockGeometry.hpp"

#include <mwFileName.hpp>
#include <mwTPoint3d.hpp>
#include <mwVirtualPureDef.hpp>
#include <mwWarningPragmas.hpp>

namespace VerifierUtil
{
class MW_VERIFIER_API mwvNCParserInstructionCallback
{
public:
	/// Signals a tool change. Use @ref mwvNCParserInterface::GetToolWithId() to receive the
	/// corresponding tool definition, and assign it to the verifier by calling @ref
	/// mwMachSimVerifier::SetTool().
	virtual void ChangeTool(const int toolId, const bool adding /*, const bool painting*/) = 0;

	/// Signals a change of the spindle (either the spindle mode or the spindle axis). Send it to
	/// the verifier by calling @ref mwMachSimVerifier::SetStockSpindleMode() resp. @ref
	/// mwMachSimVerifier::SetStockSpindleAxis().
	virtual void SetSpindleMode(const StockSpindleMode spindleMode, const StockSpindleAxis axis)
		MW_VIRTUAL_PURE_DEFINITION(void, spindleMode, axis);

	/// Signals a change in the rapid mode. Send it to the verifier by calling @ref
	/// mwMachSimVerifier::SetRapidMode().
	virtual void SetRapidMode(const bool rapid) = 0;

	/// Signals a new cut. Send it to the verifier by calling either @ref
	/// mwMachSimVerifier::SimulateMove() or @ref mwMachSimVerifier::BufferMove().
	virtual void Cut(const mwMove& toolMove) = 0;

	MW_WARNING_PUSH
	MW_WARNING_DISABLE_DEPRECATED
	// both SetSpindleMode functions will be called, so please implement just the other one
	MW_DEPRECATED("Please use StockSpindleMode instead.")
	virtual void SetSpindleMode(
		const TurningSpindleMode /*spindleMode*/, const TurningRotaryAxis /*axis*/){};
	MW_WARNING_POP
};

/// This class can be used to parse the verifier-specific NC format. This class implements a
/// callback-based design: you implement a custom @ref mwvNCParserInstructionCallback, and every
/// call to @ref NextInstruction(mwvNCParserInstructionCallback&) calls it with the next command.
///
/// Here is a small sample NC file:
/// @code
/// STOCK 0 0 0  2.5 3.5 1;
/// WTOOL 0.00800000 1.08000000;
/// MOVE X 1.25 Y 1.75 Z 1.05 TX 0 TY 0 TZ -1 ROLL 0;
/// CUT  X 1.25 Y 2.00 Z 1.05 TX 0 TY 0.76 TZ -0.64;
/// @endcode
class MW_VERIFIER_API mwvNCParserInterface
{
public:
	mwvNCParserInterface(const misc::mwFileName& filename);
	~mwvNCParserInterface();

	/// An NC file can only contain one stock. This function lets you retrieve it's definition.
	/// Currently it can't be passed directly to mwMachSimVerifier, you have to translate it to the
	/// correct call; for example @ref mwMachSimVerifier::SetStockCube().
	const misc::mwAutoPointer<mwvInitStockGeometry>& GetStock();

	/// Returns the list of all target meshes that were defined in the NC file. This can be passed
	/// to @ref mwMachSimVerifier::SetTargets().
	std::vector<misc::mwAutoPointer<cadcam::mwTMesh<float>>> GetTargetMeshes();

	/// Sends the next command to the given callback. Not all NC commands are currently implemented
	/// in the callback, so some NC commands may be silently skipped.
	///
	/// @returns false if no more commands are left.
	bool NextInstruction(mwvNCParserInstructionCallback& callback);

	/// Calling this makes sure that @ref NextInstruction() starts at the first instruction again.
	void Rewind();

	/// Returns the number of _cuts_ in the NC file. The number of calls to @ref NextInstruction()
	/// may be higher than this number, since that one also includes other commands, like
	/// SetSpindleMode().
	int GetInstructionCount();

	/// Use this function to get the tool definition that corresponds to the ID you received in
	/// mwvNCParserInstructionCallback::ChangeTool().
	cadcam::mwConstToolPtr GetToolWithId(const int toolId);

private:
	struct Impl;
	Impl* impl;
};
}  // namespace VerifierUtil
#endif  //	MW_MWVNCPARSERINTERFACE_HPP_
