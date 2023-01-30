// (C) 2018-2020 by ModuleWorks GmbH
// Owner: CutSim

/// \file
/// Helper interface for touch control.

#ifndef MW_MWVMEASURETOUCHCONTROL_HPP_
#define MW_MWVMEASURETOUCHCONTROL_HPP_

#include "mwVerifierDllDefinition.hpp"
#include "mwvMeasureCommon.hpp"

#include <mw2dGeometryTypedefs.hpp>

namespace VerifierUtil
{
namespace Measure
{
class MW_VERIFIER_API TouchControl
{
public:
	TouchControl(Tool& tool);

	~TouchControl();

	/// Has be called when the touch has ended and dragging has not been performed. Aborts the
	/// dragging.
	MeasurePointIdx SetMeasurePoint(const cadcam::mwPoint2di& pos, int posTolerance);

	/// @return true if succeeded.
	bool StartMeasurePointDragging(const cadcam::mwPoint2di& pos, int posTolerance);

	bool IsDraggingMeasurePoint() const;

	MeasurePointIdx GetDraggingMeasurePoint() const;

	/// @return false if aborted.
	bool DragMeasurePoint(const cadcam::mwPoint2di& pos, int posTolerance);

	/// Removes all measure points if the dragging is perfomed.
	void AbortMeasurePointDragging();

	/// If the dragging is not performed, does nothing. Has be called when the touch has ended and
	/// dragging is performed.
	void StopMeasurePointDragging();

private:
	bool AreMeasurePointsCloseOnScreen(int threshold) const;

private:
	Tool& m_tool;

	bool m_dragged;
	MeasurePointIdx m_draggedMeasurePoint;
	int m_lastDragPosTolerance;

private:
	TouchControl(const TouchControl&);
	void operator=(const TouchControl&);
};

}  // namespace Measure
}  // namespace VerifierUtil

#endif  //	MW_MWVMEASURETOUCHCONTROL_HPP_
