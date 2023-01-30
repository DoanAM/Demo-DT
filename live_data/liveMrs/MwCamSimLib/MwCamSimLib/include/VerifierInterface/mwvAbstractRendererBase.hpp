// (C) 2013-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVABSTRACTRENDERERBASE_HPP_
#define MW_MWVABSTRACTRENDERERBASE_HPP_
#include "mwVerifierDllDefinition.hpp"
#include "mwvAbstractRendererPrimitives.hpp"

#include <mwVirtualPureDef.hpp>

namespace VerifierUtil
{
// forward declarations
class mwvAbstractRendererBase;
class mwvAbstractRenderer;
class mwvIndexedAbstractRenderer;

/// @hidden
/// Part of the visitor pattern, used internally
class mwvAbstractRendererVisitor
{
public:
	virtual void Visit(mwvAbstractRendererBase&) = 0;
	virtual void Visit(mwvAbstractRenderer&) = 0;
	virtual void Visit(mwvIndexedAbstractRenderer&) = 0;
};

/// Interface for custom renderers to provide the stock geometry to an integration.
/// @note See also
/// [Visualizing&nbsp;the&nbsp;Workpiece&nbsp;and&nbsp;Tools](doc/Developer_guide/Cutting_Additive_Simulation/Visualizing_the_workpiece_and_tools.md).
///
/// This is only a base for the specialized interfaces
/// - mwvAbstractRenderer
/// - mwvIndexedAbstractRenderer
///
/// The concepts are the same, the specializations only differ in the formatting of the geometry
/// data.
///
/// - The interface is used via callbacks from mwMachSimVerifier::Render().
/// - The data is transferred in groups of lines or triangles.
/// - A group contains either lines or triangles. The content type for a group will not change until
///   deletion.
/// - Updates (e.g. mwvIndexedAbstractRenderer::DrawTriangles()) replace the previous data received
///   for a group.
/// - Groups can change their visibility (see SetGroupVisibility()). Groups are "visible" by
///   default.
/// - Groups can be deleted (see DeleteGroup())
///
/// @warning Don't derive from this class directly, it is only the base for mwvAbstractRenderer and
///          mwvIndexedAbstractRenderer. For performance reasons we strongly recommend to use
///          mwvIndexedAbstractRenderer.
///
class MW_VERIFIER_API mwvAbstractRendererBase
{
public:
	typedef mwvAbstractRendererPrimitives::Vector3d Vector3d;
	typedef mwvAbstractRendererPrimitives::RenderGroupID RenderGroupID;

	inline mwvAbstractRendererBase() : m_verifierInstanceId(-1){};
	virtual ~mwvAbstractRendererBase();

	/// Changes the visibility of a group, that is if it's content has to be displayed or not.
	/// Used for example with dynamic refine/zoom: The original geometry groups are kept
	/// and hidden, while a new refined stock is displayed. After that, the original stock will be
	/// drawn again by just re-enabling the hidden groups. This increases runtime-performance at the
	/// cost of memory usage. Groups are visible by default.
	virtual void SetGroupVisibility(const RenderGroupID groupId, const bool visible)
		MW_VIRTUAL_PURE_DEFINITION(void, groupId, visible);

	/// Called, if a group no longer contains data and the former contents can be discarded.
	/// Consecutive render-calls can use formerly deleted groupIds again, thus recreating the group.
	virtual void DeleteGroup(const RenderGroupID groupId) = 0;

	/// Returns the id of verifier, for which current callbacks apply.
	/// - It's purpose is, to use a single abstract renderer instance with multiple verifiers.
	/// - If only one verifier-instance is used, this value can be ignored.
	/// - This VerifierInstanceId is not needed to distinguish groupIds. They are unique, also for
	///	  different verifier instances. But the VerifierInstanceId can be used to implement custom
	///	  behavior when rendering different stocks.
	/// - It's default-value is -1.
	inline int GetVerifierInstanceId() const { return m_verifierInstanceId; }

	/// Set id of verifier, see also GetVerifierInstanceId
	///
	/// - This method is not called from the verifier itself. Integrations have to take care of it.
	/// - SetVerifierInstanceId should be called just before mwMachSimVerifier::Render() is called.
	/// - The method is virtual to allow derived renderers to react on a change of the
	/// verifierInstanceId.
	inline virtual void SetVerifierInstanceId(const int id) { m_verifierInstanceId = id; };

	/// @hidden
	/// Part of the visitor pattern, used internally and does not have to be changed/overridden.
	inline virtual void AcceptVirtual(mwvAbstractRendererVisitor& visitor)
	{
		visitor.Visit(*this);
	};

private:
	/// @hidden
	int m_verifierInstanceId;
};


}  // namespace VerifierUtil
#endif  //	MW_MWVABSTRACTRENDERERBASE_HPP_
