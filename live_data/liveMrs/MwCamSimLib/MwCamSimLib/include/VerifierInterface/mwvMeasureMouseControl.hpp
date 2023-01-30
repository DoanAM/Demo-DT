// (C) 2018-2020 by ModuleWorks GmbH
// Owner: CutSim

/// \file
/// Helper interface for mouse control.

#ifndef MW_MWVMEASUREMOUSECONTROL_HPP_
#define MW_MWVMEASUREMOUSECONTROL_HPP_

#include "mwVerifierDllDefinition.hpp"
#include "mwvMeasureCommon.hpp"

#include <mw2dGeometryTypedefs.hpp>
#include <mwAutoPointer.hpp>

namespace VerifierUtil
{
namespace Measure
{
class MW_VERIFIER_API MouseControl
{
public:
	explicit MouseControl(Tool& tool, const misc::mwAutoPointer<MouseControlCallbacks>& callbacks);

	~MouseControl();

	/// Updates the highlight. Has to be called when the mouse moves. Aborts the dragging.
	void Highlight(const cadcam::mwPoint2di& pos, int posTolerance);

	/// Sets or adds a measure-point corresponding to MouseControlCallbacks::IsModifierKeyPressed.
	/// Has to be called when the mouse button has been released and the dragging is not performed.
	/// Aborts the dragging.
	MeasurePointIdx SetMeasurePoint(const cadcam::mwPoint2di& pos, int posTolerance);

	/// @return whether it is possible to drag a highlighted measure-point.
	bool CanDragHighlightedMeasurePoint() const;

	/// @return whether the highlighted measure-point being dragged.
	bool IsDraggingHighlightedMeasurePoint() const;

	MeasurePointIdx GetDraggingMeasurePoint() const;

	/// Starts or continues dragging a highlighted measure-point. Calls
	/// CanDragHighlightedMeasurePoint() before starting.
	/// @return false if can not start or aborted.
	bool DragHighlightedMeasurePoint(const cadcam::mwPoint2di& pos, int posTolerance);

	/// Removes all measure points if the dragging is perfomed.
	void AbortHighlightedMeasurePointDragging();

	/// If the dragging is not performed, does nothing. Has to be called when the mouse button has
	/// been released and the dragging is performed.
	void StopHighlightedMeasurePointDragging();

private:
	bool IsInAlternateMeasureMode();

	bool AreMeasurePointsCloseOnScreen(int threshold) const;

private:
	Tool& m_tool;
	misc::mwAutoPointer<MouseControlCallbacks> m_callbacks;

	bool m_dragged;
	MeasurePointIdx m_draggedMeasurePoint;
	int m_lastDragPosTolerance;

private:
	MouseControl(const MouseControl&);
	void operator=(const MouseControl&);
};

struct MouseControlCallbacks
{
	virtual ~MouseControlCallbacks() {}

	/// @return whether a modifier key is pressed.
	///
	/// When a special modifier key is pressed, you can arbitrarily set the second measure-point
	/// without pulling it from the first. In Windows-System it could be a state of the SHIFT key.
	virtual bool IsModifierKeyPressed() = 0;

	struct CursorType
	{
		enum Value
		{
			move,  ///< IDC_SIZEALL
			pull,  ///< IDC_SIZENS
		};
	};
	virtual void SetCursor(CursorType::Value type) = 0;
};

}  // namespace Measure
}  // namespace VerifierUtil

#endif  //	MW_MWVMEASUREMOUSECONTROL_HPP_
