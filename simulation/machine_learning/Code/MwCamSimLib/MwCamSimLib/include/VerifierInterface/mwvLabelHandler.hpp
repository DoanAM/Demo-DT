// (C) 2013-2021 by ModuleWorks GmbH
// Owner: CutSim

/// @file
/// @warning EXPERIMENTAL, NOT A STABLE INTERFACE YET

#ifndef MW_MWVLABELHANDLER_HPP_
#define MW_MWVLABELHANDLER_HPP_
#include "mwMachSimVerifier.hpp"
#include "mwMachSimVerifierColorScheme.hpp"
#include "mwVerifierDllDefinition.hpp"
#include "mwvDrawLabelsHandler.hpp"
#include "mwvResettable.hpp"
#include "mwvUtilDefines.hpp"

#include <list>
#include <mwAutoPointer.hpp>
#include <mwString.hpp>
#include <utility>
#include <vector>

namespace VerifierUtil
{
class mwvGougeReportHandler;
}
namespace VerifierUtil
{
class mwvMeasurementDistanceHandler;
}
namespace VerifierUtil
{
class mwvMeasurementPointHandler;
}
namespace VerifierUtil
{
struct mwvGougeReport;
}
namespace VerifierUtil
{
struct mwvLabel;
}
namespace VerifierUtil
{
struct mwvMeasurementDistance;
}
namespace VerifierUtil
{
struct mwvMeasurementPoint;
}

namespace VerifierUtil
{
/// Handles the drawing of point, distance, gouge and excess labels.
class MW_VERIFIER_API mwvLabelHandler : public VerifierUtil::mwvResettable
{
public:
	enum LabelType
	{
		Point,
		Distance,
		Gouge,
		Excess
	};

private:
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	std::list<std::pair<LabelType, int>> m_labelIndices;

#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	std::vector<mwMachSimVerifier::GougeReport> m_gougeList;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	std::vector<mwMachSimVerifier::GougeReport> m_excessList;
	bool m_bShowGougeLabels;
	bool m_bShowExcessLabels;

	mwvDrawLabelsHandler m_drawLabelsHandler;

#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	std::pair<LabelType, int> m_currentDrawnLabel;

	int m_currentMovedLabel;
	LabelType m_currentMovedLabelType;

	bool m_automaticVerifierUpdate;

	bool m_removeFirstClick;
	float m_textHeightFactor;  // controls distance between lines of text

protected:
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<mwvMeasurementPointHandler> m_apMeasurementPointHandler;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<mwvMeasurementDistanceHandler> m_apMeasurementDistanceHandler;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<mwvGougeReportHandler> m_apGougeHandler;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<mwvGougeReportHandler> m_apExcessHandler;

public:
	mwvLabelHandler(mwMachSimVerifier* const pVerifier);
	virtual ~mwvLabelHandler();

	/// Resets the point and distance labels
	///
	/// All point and distance labels are deleted. Gouge and Excess labels are kept.
	void Reset();

	/// Draws all labels
	///
	/// All point, distance, gouge and excess labels are drawn in the order of their creation.
	///	If a label is moved, it is drawn on top of all labels. The first pin of a distance label is
	///   also drawn.
	void Draw();

	/// Updates the gouge and excess labels
	///
	/// Updates the gouge and excess labels using the verifier.
	void Update();

	/// Select or remove a point or distance
	///
	/// Select or remove a point or distance on the surface. This depends on
	/// mwMachSimVerifier::SelectionMode, see GetSelectionMode().
	/// @param [in] x the x part of the selected point in window coordinates
	/// @param [in] y the y part of the selected point in window coordinates
	/// @param [out] vertex the found surface point on the geometry
	/// @param [out] idx the index of the added/removed label
	/// @return 1 for added, 0 for removed a label, -1 if nothing happened
	int Select(int x, int y, float3d& vertex, int& idx);

	/// Resets the current move
	///
	/// Resets the current moved label. This should be called in a MouseDown-Event.
	void ResetMove();

	bool IsMove() const;

	/// Moves the selected label
	///
	/// Moves the selected label the offset between the two passed points. This should be called in
	/// a MouseMove-Event.
	/// @param [in] x the x part of the current position in window coordinates
	/// @param [in] y the y part of the current position in window coordinates
	/// @param [in] xPrev the x part of the last position in window coordinates
	/// @param [in] yPrev the y part of the last position in window coordinates
	/// @param [in] tolerance Selection tolerance.
	void Move(int x, int y, int xPrev, int yPrev, int tolerance = 0);

	/// Removes all selected points and the labels associated with them.
	void ClearSelectedPoints();

	/// Removes all selected distances and the labels associated with them.
	void ClearSelectedDistances();

	/// Enables removal of first click distance
	///
	/// Enables removal of first click distance clamp on reset. See Reset() and
	/// ClearSelectedDistances().
	/// @param [in] removeFirstClick TRUE first click distance will be removed
	void SetRemoveFirstClickOnReset(bool removeFirstClick);

	/// Gets the current removal mode of first click distance
	///
	/// Gets the current removal mode of first click distance clamp on reset. See Reset() and
	/// ClearSelectedDistances().
	/// @return the current removal mode
	bool GetRemoveFirstClickOnReset();

	/// Enables automatic verifier update on draw
	///
	/// Enables automatic verifier update of gouge and excess labels on draw. See Draw().
	/// @param [in] automaticUpdate TRUE verifier is updated automatically
	void SetAutomaticVerifierUpdate(bool automaticUpdate);

	/// Gets current update mode of verifier
	///
	/// Gets a value indicating the current automatic update mode of the verifier.
	/// @return the current update mode
	bool GetAutomaticVerifierUpdate();

	/// Removes the first click for distances
	void ResetFirstClickForDistances();

	/// Enables gouge labels display
	///
	/// Enables the graphic display of the gouge labels
	/// @param [in] showGougePoints TRUE gouge labels should be drawn
	void SetShowGougeLabels(bool showGougePoints);

	/// Gets the current gouge labels display
	///
	/// Gets a value indicating the current gouge labels display
	/// @return the current gouge display
	bool GetShowGougeLabels();

	/// Enable gouge labels display
	///
	/// Enable the graphic display of the gouge labels
	/// @param [in] showGougePoints TRUE gouge labels should be drawn
	void SetShowExcessLabels(bool showGougePoints);

	/// Gets the current excess labels display
	///
	/// Gets a value indicating the current excess labels display
	/// @return the current excess display
	bool GetShowExcessLabels();

private:
	/// Draws a gouge label
	///
	/// Draws the gouge label at index 'idx' in list m_apGougeHandler->m_selectedGouges.
	/// @param [in] idx the index of the label
	void DrawGougePoint(int idx);

	/// Draws a excess label
	///
	/// Draws the excess label at index 'idx' in list m_apExcessHandler->m_selectedGouges.
	/// @param [in] idx the index of the label
	void DrawExcessPoint(int idx);

	/// Draws a point label
	///
	/// Draws the point label at index 'idx' in list m_apMeasurementPointHandler->m_selectedPoints.
	/// @param [in] idx the index of the label
	void DrawSelectedPoint(int idx);

	/// Draws a distance label
	///
	/// Draws the distance label at index 'idx' in list
	/// m_apMeasurementDistanceHandler->m_selectedDistances.
	/// @param [in] idx the index of the label
	void DrawSelectedDistance(int idx);

	/// Sets the current drawn label
	///
	/// The current drawn label is set here before DrawLabel() is called.
	/// @param [in] label the pair of values with the type of the label and the index in the
	///                  corresponding list
	void SetCurrentDrawnLabel(std::pair<LabelType, int> label);

	/// Gets a gouge label by report
	///
	/// Gets or creates a gouge label for the passed gouge report
	/// @return the found or created gouge label
	mwvGougeReport& GetGougeLabel(mwMachSimVerifier::GougeReport report);

	/// Gets an excess label by report
	///
	/// Gets or creates a excess label for the passed excess report
	/// @return the found or created excess label
	mwvGougeReport& GetExcessLabel(mwMachSimVerifier::GougeReport report);

	/// Moves a label with the passed offset
	///
	/// Moves a label with the passed offset if the label contains the scene position
	/// @param [in] label the label that might be moved
	/// @param [in] ScenePos the openGL coordinates of the selected position
	/// @param [in] xOffset the x coordinate of the offset to move
	/// @param [in] yOffset the y coordinate of the offset to move
	/// @return TRUE if the label was moved
	bool MoveLabel(mwvLabel& label, const int2d& ScenePos, int xOffset, int yOffset, int tolerance);

protected:
	/// Gets the current drawn label
	///
	/// Gets the current drawn label with type and the index of the label in the corresponding list.
	/// This is intended to identify the type and the exact label at any point in time during the
	/// draw. See Select() for the indices of the labels right after creation.
	/// @return the pair of values with the type of the label and the index
	std::pair<LabelType, int> GetCurrentDrawnLabel();

	/// Draws the whole label
	///
	/// Draws the whole label with a box, the description text, a pin to the targeted position and a
	/// shadow. The look is specified via a label appearance reference.
	/// @param [in] point the targeted position of the label
	/// @param [in] direction the vector from the targeted position to the label
	/// @param [in] offset the offset from the original label position
	/// @param [in] la the appearance of the label defined by various parameters
	/// @param [in] cLine the description text of the label
	/// @param [out] minWin the top left corner of the offset label
	/// @param [out] maxWin the bottom right corner of the offset label
	virtual void DrawLabel(
		float3d point,
		const float3d& direction,
		const float3d& offset,
		const LabelAppearance& la,
		const misc::mwstring& cLine,
		float3d& minWin,
		float3d& maxWin);

	/// Draws the pin of the label
	///
	/// Draws the pin from the label corner vLBw to the position pt (both in window coordinates).
	/// The look is specified via a label appearance reference.
	/// @param [in] point the targeted position of the label
	/// @param [in] vLBw the left bottom position of the label
	/// @param [in] la the appearance of the label defined by various parameters
	virtual void DrawPin(const float3d& point, const float3d& vLBw, const LabelAppearance& la);

	/// Draws the shadow of the box
	///
	/// The shadow of the box is drawn here. The position is defined by the corner points in window
	/// coordinates. The look is specified via a label appearance reference.
	/// @param [in] vLBw the left bottom position of the box
	/// @param [in] vRTw the right top position of the box
	/// @param [in] vRBw the right bottom position of the box
	/// @param [in] la the appearance of the label defined by various parameters
	virtual void DrawShadow(
		const float3d& vLBw, const float3d& vRTw, const float3d& vRBw, const LabelAppearance& la);

	/// Draws the text inside the label
	///
	/// The box of the label is drawn here. The position is defined by the left bottom corner in
	/// window coordinates. The look is specified via a label appearance reference.
	/// @param [in] vLBw the left bottom position of the box
	/// @param [in] iNoLines the number of lines in the text
	/// @param [in] cLine the text with all lines in one string
	/// @param [in] la the appearance of the label defined by various parameters
	virtual void DrawLabelText(
		const float3d& vLBw, int iNoLines, const misc::mwstring& cLine, const LabelAppearance& la);

	/// Draws the box of the label
	///
	/// The box of the label is drawn here. The position is defined by the corner points in window
	/// coordinates. The look is specified via a label appearance reference.
	/// @param [in] vLBw the left bottom position of the box
	/// @param [in] vLTw the left top position of the box
	/// @param [in] vRTw the right top position of the box
	/// @param [in] vRBw the right bottom position of the box
	/// @param [in] la the appearance of the label defined by various parameters
	virtual void DrawLabelBox(
		const float3d& vLTw,
		const float3d& vRTw,
		const float3d& vRBw,
		const float3d& vLBw,
		const LabelAppearance& la);

	/// Draws the full text box of the label
	///
	/// Draws the full text box of the label with the description text and a shadow.
	/// The look is specified via a label appearance reference.
	/// @param [in] leftBottomPoint the left bottom position of the box
	/// @param [in] height the height of the box
	/// @param [in] width the width of the box
	/// @param [in] labelAppearance the appearance of the label defined by various parameters
	/// @param [in] lineCount the number of lines of the text
	/// @param [in] text the description text of the label
	/// @param [out] minWin the the bottom left coordinates of the window
	/// @param [out] maxWin the the top right coordinates of the window
	void DrawLabelTextBox(
		const float3d& leftBottomPoint,
		int height,
		int width,
		const LabelAppearance& labelAppearance,
		int lineCount,
		const misc::mwstring& text,
		float3d& minWin,
		float3d& maxWin);

	/// Draws the clamp of a selected distance
	///
	/// Draws the clamp of a selected distance. If only one out of the two points is selected,
	/// pointA and pointB are the same. The look is specified via a label appearance reference.
	/// @param [in] pointA the first selected position of the distance
	/// @param [in] pointB the second selected position of the distance
	/// @param [in] offset the offset from the original label position
	/// @param [in] la the appearance of the label defined by various parameters
	/// @param [in] cLine the description text of the label
	/// @param [out] minWin the the bottom left coordinates of the window
	/// @param [out] maxWin the the top right coordinates of the window
	virtual void DrawClamp(
		float3d pointA,
		float3d pointB,
		const float3d& direction,
		const float3d& offset,
		const LabelAppearance& la,
		const misc::mwstring& cLine,
		float3d& minWin,
		float3d& maxWin);

	/// Get gouge label text
	///
	/// Return the label description text of the passed gouge report. See GetLineDelimiter().
	/// @param [in] gouge a gouge report to be described by the text
	/// @return the text that is displayed in the gouge label
	virtual misc::mwstring GetGougeText(const mwMachSimVerifier::GougeReport& gouge);

	/// Get excess label text
	///
	/// Return the label description text of the passed gouge report. See GetLineDelimiter().
	/// @param [in] excess a gouge report to be described by the text
	/// @return the text that is displayed in the excess label
	virtual misc::mwstring GetExcessText(const mwMachSimVerifier::GougeReport& excess);

	/// Get point label text
	///
	/// Return the label description text of the passed measured point. See GetLineDelimiter().
	/// @param [in] point a measured point to be described by the text
	/// @return the text that is displayed in the point label
	virtual misc::mwstring GetPointText(const mwvMeasurementPoint& point);

	/// Get distance label text
	///
	/// Return the label description text of the passed measured distance. See GetLineDelimiter().
	/// @param [in] distance a measured distance to be described by the text
	/// @return the text that is displayed in the distance label
	virtual misc::mwstring GetDistanceText(const mwvMeasurementDistance& distance);

	void ApplyTextMask(const mwLabelTextMask& mask);

	const LabelAppearance& GetPointLabelAppearance() const;

	void SetPointLabelAppearance(const LabelAppearance& labelAppearance);

	const LabelAppearance& GetDistanceLabelAppearance() const;

	void SetDistanceLabelAppearance(const LabelAppearance& labelAppearance);

	const LabelAppearance& GetGougeLabelAppearance() const;

	void SetGougeLabelAppearance(const LabelAppearance& labelAppearance);

	const LabelAppearance& GetExcessLabelAppearance() const;

	void SetExcessLabelAppearance(const LabelAppearance& labelAppearance);

	/// Sets an overall label appearance
	///
	/// Sets the same label appearance for all labels.
	/// @param [in] la the appearance of the label defined by various parameters
	void SetLabelAppearance(const LabelAppearance& la);

	/// Sets an overall text color
	///
	/// Sets the same text color for all labels.
	/// @param [in] value the new text color
	void SetLabelTextColor(const float3d& value);

	/// Sets an overall back color
	///
	/// Sets the same back color for all labels.
	/// @param [in] value the new back color
	void SetLabelBackColor(const float3d& value);

	/// Sets an overall border color
	///
	/// Sets the same border color for all labels.
	/// @param [in] value the new border color
	void SetLabelBorderColor(const float3d& value);

	/// Sets an overall transparency
	///
	/// Sets the same transparency for all labels.
	/// @param [in] value the new transparency value
	void SetLabelTransparency(float value);

	/// Keeps the label box in the window
	///
	/// Keeps the label box coordinates in the window frame. 'vLBw' and 'vRTw' are also
	/// in-parameters.
	/// @param [out] leftBottom the left bottom position of the box
	/// @param [out] leftTop the left top position of the box
	/// @param [out] rightTop the right top position of the box
	/// @param [out] rightBottom the right bottom position of the box
	void KeepInViewPort(
		float3d& leftBottom,
		float3d& leftTop,
		float3d& rightTop,
		float3d& rightBottom,
		const LabelAppearance& labelAppearance);

	/// Gets the number of lines and columns
	///
	/// Gets the number of lines and columns in the passed text.
	/// @param [in] text the text you want to count lines and columns in
	/// @param [out] lineCount the number of lines in the text
	/// @param [out] columnCount the number of columns in the text
	void GetNumberOfLinesAndCollumns(const misc::mwstring& text, int& lineCount, int& columnCount);

	const float3d& GetNearestPosition(const float3d& pos, const float3d& posA, const float3d& posB);

	/// Concatenates two strings
	///
	/// Concatenates two strings in the passed order
	/// * @param [in] first the string that will be placed before the other
	/// * @param [in] second the string that will be placed after the other
	/// return the result string
	misc::mwstring Concat(misc::mwstring first, const misc::mwstring& second);

	/// Gets the line delimiter
	///
	/// Return the line delimiter for the label description text format. Insert it into your
	/// description string to create a line break.
	/// @return the line delimiter character as a string
	virtual misc::mwstring GetLineDelimiter();
};
}  // namespace VerifierUtil
#endif  //	MW_MWVLABELHANDLER_HPP_
