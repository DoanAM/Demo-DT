// (C) 2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVASYNCRENDERER_HPP_
#define MW_MWVASYNCRENDERER_HPP_

#include <mwDefines.hpp>

#ifndef MW_USE_VS2008_COMPATIBILITY

#include "mwVerifierDllDefinition.hpp"

#include <mwAutoPointer.hpp>

class mwMachSimVerifier;

namespace VerifierUtil
{
/// Provides an implementation of a thread-safe renderer, i.e. it can be used
/// to draw the stock from the UI thread while the triangulation calculations are triggered from a
/// different thread. The AsyncRenderer will not create threads itself but the integration has to
/// call @ref Draw() and @ref UpdateFrom() from different threads in order to benefit from the
/// asynchronicity.
class MW_VERIFIER_API AsyncRenderer
{
public:
	/// @hidden
	virtual ~AsyncRenderer() = default;

	/// @name Drawing
	///	@anchor Drawing
	/// @{
	/// Methods used to draw the stock model. Can be called concurrently with @ref UpdateFrom().
	/// Must be called with the same active OpenGL context that was used during creation.
	/// @note Use either @ref Draw() OR the more granular methods PrepareDraw(), DrawTriangles(),
	/// DrawLines().


	/// Convenience method which calls PrepareDraw(), DrawTriangles() and
	/// DrawLines() with some additional GL state changes that work well with the
	/// @ref mwvSectionPlaneRenderer
	virtual void Draw() = 0;

	/// Applies pending geometry changes to the draw buffer and sorts groups by distance to current
	/// OpenGL viewpoint if non-opaque colors are used in the geometries.
	virtual void PrepareDraw() = 0;
	/// Draws all triangle groups. Only binds and draws buffers, does not change other GL states.
	virtual void DrawTriangles() = 0;
	/// Draws all line groups. Only binds and draws buffers, does not change other GL states.
	virtual void DrawLines() = 0;
	///@}

	/// @name Triangulation
	/// @{
	/// Calls @ref mwMachSimVerifier::Render() to update the stock model. Most probably you want to
	/// call this from a different thread than the @ref Drawing methods.
	/// @returns true if there were changes in the rendered stock model.
	virtual bool UpdateFrom(mwMachSimVerifier& verifier) = 0;
	/// @}

	/// Creates a default implementation of an AsyncRenderer using OpenGL. Creation and deletion of
	/// the AsyncRenderer must happen within the same OpenGL context.
	static misc::mwAutoPointer<AsyncRenderer> Create();
};
}  // namespace VerifierUtil
#endif
#endif  //	MW_MWVASYNCRENDERER_HPP_
