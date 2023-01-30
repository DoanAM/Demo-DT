// (C) 2018-2021 by ModuleWorks GmbH
// Owner: CutSim

/// \file
/// Unified draw settings.

#ifndef MW_MWVMEASUREDRAWSTYLE_HPP_
#define MW_MWVMEASUREDRAWSTYLE_HPP_

#include "mwVerifierDllDefinition.hpp"

#include <mwColor.hpp>

namespace VerifierUtil
{
namespace Measure
{
struct MW_VERIFIER_API DrawStyle
{
	float scale;  // = 1
	float displayPrecision;  // = 0: dynamic
	bool removeTrailingZeros;  // = true

	bool drawAxis;
	bool drawArcRadius;
	bool drawCurvature;
	bool drawThickness;
	bool drawDepth;
	bool drawClearance;
	bool drawCorner;
	bool drawDistance;

	misc::mwstring labelFont;  // = Arial
	int labelFontSize;  // = 13 points
	int labelFontWeight;  // = 700 (bold)
	int labelOffset;  // = 4 points
	int labelPadding;  // = 1 points
	float labelAlpha;  // = 0.75

	float geometryPointRadius;  // = 3 points
	float measurePointRadius;  // = 6 points
	float measurePointBorder;  // = 3 points

	float vertexWidth;  // = 7 points

	float edgeWidth;  // = 3 PIXELS
	float edgeFadeLength;  // = 50 points
	float edgeMidpointWidth;  // = 5 points

	float axisWidth;  // = 1 point

	float distanceArrowheadSize;  // = 9 points
	int cornerTangentLength;  // = 30 points

	misc::mwstring degreeSymbol;  // = "°"
	misc::mwstring radiusSymbol;  // = "R"
	misc::mwstring thicknessSymbol;  // = ""
	misc::mwstring depthSymbol;  // = ""
	misc::mwstring clearanceSymbol;  // = ""

	misc::mwColor vertexColor;
	misc::mwColor highlightedVertexColor;
	misc::mwColor edgeColor;
	misc::mwColor highlightedEdgeColor;
	misc::mwColor axisColor;
	misc::mwColor highlightedAxisColor;
	misc::mwColor directDistanceColor;
	misc::mwColor directDistanceLabelTextColor;
	misc::mwColor directDistanceLabelBackgroundColor;
	misc::mwColor reliableDistanceColor;
	misc::mwColor reliableDistanceLabelTextColor;
	misc::mwColor reliableDistanceLabelBackgroundColor;
	misc::mwColor unreliableDistanceColor;
	misc::mwColor unreliableDistanceLabelTextColor;
	misc::mwColor unreliableDistanceLabelBackgroundColor;
	misc::mwColor offsetXColor;
	misc::mwColor offsetXLabelTextColor;
	misc::mwColor offsetXLabelBackgroundColor;
	misc::mwColor offsetYColor;
	misc::mwColor offsetYLabelTextColor;
	misc::mwColor offsetYLabelBackgroundColor;
	misc::mwColor offsetZColor;
	misc::mwColor offsetZLabelTextColor;
	misc::mwColor offsetZLabelBackgroundColor;
	misc::mwColor arcRadiusColor;
	misc::mwColor arcLabelTextColor;
	misc::mwColor arcLabelBackgroundColor;
	misc::mwColor cornerAngleColor;
	misc::mwColor cornerAngleLabelTextColor;
	misc::mwColor cornerAngleLabelBackgroundColor;
	misc::mwColor firstCurvatureColor;
	misc::mwColor firstCurvatureLabelTextColor;
	misc::mwColor firstCurvatureLabelBackgroundColor;
	misc::mwColor secondCurvatureColor;
	misc::mwColor secondCurvatureLabelTextColor;
	misc::mwColor secondCurvatureLabelBackgroundColor;
	misc::mwColor highlightedDimensionColor;
	misc::mwColor highlightedLabelTextColor;
	misc::mwColor highlightedLabelBackgroundColor;
	misc::mwColor measurePointFrontColor;
	misc::mwColor measurePointBackColor;
	misc::mwColor highlightedMeasurePointFrontColor;
	misc::mwColor highlightedMeasurePointBackColor;
	misc::mwColor geometryPointFrontColor;
	misc::mwColor geometryPointBackColor;
	misc::mwColor highlightedGeometryPointFrontColor;
	misc::mwColor highlightedGeometryPointBackColor;

	DrawStyle();

	/// @deprecated Use geometryPointRadius instead.
	// MW_DEPRECATED("Deprecated in 2021.04, use geometryPointRadius instead")
	float measurePosRadius;
};

}  // namespace Measure
}  // namespace VerifierUtil

#endif  //	MW_MWVMEASUREDRAWSTYLE_HPP_
