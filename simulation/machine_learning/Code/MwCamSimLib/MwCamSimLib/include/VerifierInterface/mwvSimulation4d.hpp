// (C) 2017-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVSIMULATION4D_HPP_
#define MW_MWVSIMULATION4D_HPP_
#include "mwvIndexedAbstractRenderer.hpp"

#include <mw3dBoundingBox.hpp>
#include <mwBinInputStream.hpp>
#include <mwBinOutputStream.hpp>
#include <mwIProgressHandler.hpp>

namespace VerifierUtil
{
/// Captures the geometry output of @ref mwMachSimVerifier::Render() and allows for replay later,
/// using the @ref mwvIndexedAbstractRenderer API.
/// See also
/// [4D&nbsp;Simulation](doc/Developer_guide/Cutting_Additive_Simulation/4D_Simulation.md).
class MW_VERIFIER_API mwvSimulation4d : public mwvIndexedAbstractRenderer
{
public:
	/// @hidden
	virtual ~mwvSimulation4d();

	/// @name Render Frame (Play)
	///
	/// The @p frameIndex denotes the frame to which the next @ref Render() call will incrementally
	/// update the target renderer.
	/// @{
	virtual void SetCurrentRenderFrame(size_t frameIndex) = 0;
	virtual size_t GetCurrentRenderFrame() const = 0;
	/// @}

	/// @name Capture Frame (Record)
	///
	/// Controls the frame in which the incoming geometry is stored. Only the latest version
	/// of each subvolume is kept. For the highest resolution, the capture frame should be
	/// incremented after each @ref mwMachSimVerifier::Render() call.
	///	@note Can trigger the creation of Keyframes.
	/// @{
	virtual void AdvanceCurrentCaptureFrame() = 0;
	virtual void AdvanceCurrentCaptureFrameIffNewDataCaptured() = 0;
	virtual size_t GetCurrentCaptureFrameIndex() const = 0;
	virtual size_t GetNumberOfCapturedFrames() const = 0;

	/// @name Keyframes
	///
	///	Keyframes are used to speed up the re-creation of render frames: All latest updates for all
	/// subvolumes need to be tracked back. With Keyframes, the back tracking can be limited to just
	/// the data between two Keyframes. These options control how keyframes are created during
	/// capture.
	///
	/// @{
	virtual void SetAutoKeyFramingEnabled(bool enabled) = 0;
	virtual bool IsAutoKeyFramingEnabled() const = 0;
	virtual void SetKeyFrameStride(size_t stride) = 0;
	virtual size_t GetKeyFrameStride() const = 0;
	/// @}
	/// @}

	/// @name Modifying the captured data
	///
	///	@{
	/// Clears the whole cache and resets the internal capture and render frame indices to 0.
	virtual void ResetCache() = 0;
	virtual void DeleteFramesAfter(size_t frameIndex) = 0;

	/// Consolidates all frames before the given index into a single keyframe. All previous frames
	/// will be cleared, such that they still exist but do not contain any geometry updates.
	virtual void ConsolidateAndClearFramesBefore(size_t frameIndex) = 0;
	///@}

	/// @name Rendering
	///
	///	@{
	/// Incrementally updates the @p targetRenderer to re-create the set render frame (@ref
	/// SetCurrentRenderFrame()) Assumes that it is being called with the same @ref
	/// mwvIndexedAbstractRenderer @p targetRenderer all the time.
	/// @note If the @p	targetRenderer should be changed, call @ref ForceRedraw() before.
	virtual void Render(mwvIndexedAbstractRenderer& targetRenderer) = 0;

	/// This will send all the geometry updates for the current render frame with the next @ref
	/// Render() call (instead of just incremental changes).
	virtual void ForceRedraw() = 0;

	/// Get the bounding box of all captured/loaded frames. Useful to resize render views before
	/// any triangle is visible (especially useful for replaying additive simulations).
	virtual cadcam::mw3dBoundingBox<float> GetBoundingBox() const = 0;
	/// @}

	/// @name Persistence/Serialization
	/// @{
	virtual void SaveTo(misc::mwBinOutputStream& str) const = 0;
	virtual void SaveTo(const misc::mwstring& fileName) const = 0;
	virtual void LoadFrom(misc::mwBinInputStream& str) = 0;
	virtual void LoadFrom(const misc::mwstring& fileName) = 0;

	/// @note The progress handler is only called during @ref SaveTo / @ref LoadFrom.
	virtual void SetProgressHandler(mwIDisplayableProgressHandler* progressHandler) = 0;
	/// @}

	/// Factory method to create instances of @ref mwvSimulation4d.
	static ::misc::mwAutoPointer<mwvSimulation4d> Create();

protected:
	/// @hidden
	mwvSimulation4d();
};
}  // namespace VerifierUtil
#endif  //	MW_MWVSIMULATION4D_HPP_
